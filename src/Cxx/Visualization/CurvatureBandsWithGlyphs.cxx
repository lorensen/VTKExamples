#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkBandedPolyDataContourFilter.h>
#include <vtkCamera.h>
#include <vtkCleanPolyData.h>
#include <vtkClipPolyData.h>
#include <vtkColorSeries.h>
#include <vtkCurvatures.h>
#include <vtkElevationFilter.h>
#include <vtkGlyph3D.h>
#include <vtkImplicitBoolean.h>
#include <vtkLookupTable.h>
#include <vtkMaskPoints.h>
#include <vtkNamedColors.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricRandomHills.h>
#include <vtkParametricTorus.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkReverseSense.h>
#include <vtkScalarBarActor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSuperquadricSource.h>
#include <vtkTriangleFilter.h>
#include <vtkVariantArray.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

enum SURFACE_TYPE
{
  TORUS = 0,
  PARAMETRIC_HILLS,
  PARAMETRIC_TORUS
};

namespace
{
//! Some STL Utilities.
class STLHelpers
{
public:
  //---------------------------------------------------------------------------
  STLHelpers() {}

  //---------------------------------------------------------------------------
  virtual ~STLHelpers() {}

  //-----------------------------------------------------------------------------
  // Convert a string to lowercase.
  std::string ToLowercase(const std::string& str)
  {
    std::string s;
    std::transform(str.begin(), str.end(), std::back_inserter(s),
      (int (*)(int))std::tolower);
    return s;
  }

  //-----------------------------------------------------------------------------
  // Replace all occurrences of old_value in a string with new_value.
  std::string ReplaceAll(std::string& str, const std::string& old_value,
    const std::string& new_value)
  {
    size_t start_pos = 0;
    while ((start_pos = str.find(old_value, start_pos)) != std::string::npos)
    {
      str.replace(start_pos, old_value.length(), new_value);
      // It could be that 'new_value' is a substring of 'old_value'.
      start_pos += new_value.length();
    }
    return str;
  }

  //-----------------------------------------------------------------------------
  // An implementation of the C++11 next(iter,n) found in the header <iterator>.
  // ForwardIt must meet the requirements of ForwardIterator.
  // Return the nth successor of iterator it.
  template <typename ForwardIt>
  ForwardIt Next(ForwardIt iter,
    typename std::iterator_traits<ForwardIt>::difference_type n = 1)
  {
    std::advance(iter, n);
    return iter;
  }

  //-----------------------------------------------------------------------------
  // Return true if the iterator points to the last element.
  template <typename Iter, typename Cont>
  bool IsLast(Iter iter, const Cont& cont)
  {
    return (iter != cont.end()) && (Next(iter) == cont.end());
  }
};

//-----------------------------------------------------------------------------
// Function declarations.

//! Divide a range into bands
/*!
@param dR - [min, max] the range that is to be covered by the bands.
@param numberOfBands - the number of bands, a positive integer.
@param nearestInteger - if True then [floor(min), ceil(max)] is used.
@return A List consisting of [min, midpoint, max] for each band.
*/
std::vector<std::vector<double>> MakeBands(
  double const dR[2], int const& numberOfBands, bool const& nearestInteger);

//! Divide a range into custom bands
/*!
You need to specify each band as a list [r1, r2] where r1 < r2 and
append these to a list (called x in the implementation).
The list should ultimately look
like this: x = [[r1, r2], [r2, r3], [r3, r4]...]

@param dR - [min, max] the range that is to be covered by the bands.
@param numberOfBands - the number of bands, a positive integer.
@return A List consisting of [min, midpoint, max] for each band.
*/
std::vector<std::vector<double>> MakeCustomBands(
  double const dR[2], int const& numberOfBands);

//! Divide a range into integral bands
/*!
Divide a range into bands
@param dR - [min, max] the range that is to be covered by the bands.
@return A List consisting of [min, midpoint, max] for each band.
*/
std::vector<std::vector<double>> MakeIntegralBands(double const dR[2]);

//! Print the bands.
/*!
@param bands - the bands.
*/
void PrintBands(std::vector<std::vector<double>> const& bands);

//! Generate elevations over the surface.
/*!
@param src - the vtkPolyData source.
@param elev - the vtkPolyData source with elevations.
*/
void MakeElevations(vtkPolyData* src, vtkPolyData* elev);

//! Make a torus as the source.
/*!
@param src - The vtkPolyData source with normal and scalar data.
*/
void MakeTorus(vtkPolyData* src);

//! Make a parametric torus as the source.
/*!
@param src - The vtkPolyData source with normal and scalar data.
*/
void MakeParametricTorus(vtkPolyData* src);

//! Make a parametric hills surface as the source.
/*!
@param src - The vtkPolyData source with normal and scalar data.
*/
void MakeParametricHills(vtkPolyData* src);

//! Calculate curvatures.
/*!
Clip a vtkPolyData source.
A cube is made whose size corresponds the the bounds of the source.
Then each side is shrunk by the appropriate dx, dy or dz. After
this operation the source is clipped by the cube.
@param src - the vtkPolyData source
@param dx - the amount to clip in the x-direction
@param dy - the amount to clip in the y-direction
@param dz - the amount to clip in the z-direction
@param clipped - clipped vtkPolyData.
*/
void Clipper(vtkPolyData* src, double const& dx, double const& dy,
  double const& dz, vtkPolyData* clipped);

//! Calculate curvatures.
/*!
The source must be triangulated.
@param src - the source.
@param curv - vtkPolyData with normals and scalar data representing curvatures.
*/
void CalculateCurvatures(vtkPolyData* src, vtkPolyData* curv);

/*!
@param lut - An indexed lookup table.
*/
void MakeLUT(vtkLookupTable* lut);

//! Create a lookup table with the colors reversed.
/*!
@param lut - An indexed lookup table.
@param lutr - The reversed indexed lookup table.
*/
void ReverseLUT(vtkLookupTable* lut, vtkLookupTable* lutr);

//! Count the number of scalars in each band.
/*!
@param bands - the bands.
@param src - the vtkPolyData source.
@return The frequencies of the scalars in each band.
*/
std::vector<int> Frequencies(
  std::vector<std::vector<double>> const& bands, vtkPolyData* src);

//! Print the frequency table.
/*!
@param freq - the frequencies.
*/
void PrintFrequencies(std::vector<int>& freq);

//!  Glyph the normals on the surface.
/*!
@param src - the vtkPolyData source.
@param reverseNormals - if True the normals on the surface are reversed.
@param glyph - The glyphs.
*/
void MakeGlyphs(
  vtkPolyData* src, bool const& reverseNormals, vtkGlyph3D* glyph);

//! Assemble the surface for display.
/*!
@param st - the surface to display.
@param iren - the interactor.
*/
void Display(SURFACE_TYPE st, vtkRenderWindowInteractor* iren);
//-----------------------------------------------------------------------------

}

//-----------------------------------------------------------------------------
//! Make and display the surface.
int main(int, char* [])
{
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  // Select the surface you want displayed.
  // Display(TORUS, iren);
  // Display(PARAMETRIC_TORUS, iren);
  Display(PARAMETRIC_HILLS, iren);
  iren->Render();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace
{
//-----------------------------------------------------------------------------
std::vector<std::vector<double>> MakeBands(
  double const dR[2], int const& numberOfBands, bool const& nearestInteger)
{
  std::vector<std::vector<double>> bands;
  if ((dR[1] < dR[0]) || (numberOfBands <= 0))
  {
    return bands;
  }
  double x[2];
  for (int i = 0; i < 2; ++i)
  {
    x[i] = dR[i];
  }
  if (nearestInteger)
  {
    x[0] = std::floor(x[0]);
    x[1] = std::ceil(x[1]);
  }
  double dx = (x[1] - x[0]) / static_cast<double>(numberOfBands);
  std::vector<double> b;
  b.push_back(x[0]);
  b.push_back(x[0] + dx / 2.0);
  b.push_back(x[0] + dx);
  for (int i = 0; i < numberOfBands; ++i)
  {
    bands.push_back(b);
    for (std::vector<double>::iterator p = b.begin(); p != b.end(); ++p)
    {
      *p = *p + dx;
    }
  }
  return bands;
}

//-----------------------------------------------------------------------------
std::vector<std::vector<double>> MakeCustomBands(
  double const dR[2], int const& numberOfBands)
{
  std::vector<std::vector<double>> bands;
  if ((dR[1] < dR[0]) || (numberOfBands <= 0))
  {
    return bands;
  }
  // We can do this much better in c++11!
  double myBands[][2] = {{-0.7, -0.05}, {-0.05, 0}, {0, 0.13}, {0.13, 1.07},
    {1.07, 35.4}, {35.4, 37.1}};
  std::vector<std::vector<double>> x;
  for (int i = 0; i < 6; ++i)
  {
    std::vector<double> tmp(2);
    tmp[0] = myBands[i][0];
    tmp[1] = myBands[i][1];
    x.push_back(tmp);
  }
  // Set the minimum to match the range minimum.
  x[0][0] = dR[0];
  size_t sz = (static_cast<size_t>(numberOfBands) < x.size())
                ? static_cast<size_t>(numberOfBands)
                : x.size();
  // Adjust the last band.
  if (x[sz - 1][0] > dR[1])
  {
    x[sz - 1][0] = dR[0];
  }
  x[sz - 1][1] = dR[1];
  for (size_t i = 0; i < sz; ++i)
  {
    std::vector<double> b(3);
    b[0] = x[i][0];
    b[1] = x[i][0] + (x[i][1] - x[i][0]) / 2.0;
    b[2] = x[i][1];
    bands.push_back(b);
  }
  return bands;
}

//-----------------------------------------------------------------------------
std::vector<std::vector<double>> MakeIntegralBands(double const dR[2])
{
  std::vector<std::vector<double>> bands;
  if (dR[1] < dR[0])
  {
    return bands;
  }
  double x[2];
  for (int i = 0; i < 2; ++i)
  {
    x[i] = dR[i];
  }
  x[0] = std::floor(x[0]);
  x[1] = std::ceil(x[1]);
  int numberOfBands = static_cast<int>(std::abs(x[1]) + std::abs(x[0]));
  return MakeBands(x, numberOfBands, false);
}

//-----------------------------------------------------------------------------
void PrintBands(std::vector<std::vector<double>> const& bands)
{
  STLHelpers stlHelpers = STLHelpers();
  for (std::vector<std::vector<double>>::const_iterator p = bands.begin();
       p != bands.end(); ++p)
  {
    if (p == bands.begin())
    {
      std::cout << "[";
    }
    for (std::vector<double>::const_iterator q = p->begin(); q != p->end(); ++q)
    {
      if (q == p->begin())
      {
        std::cout << "[";
      }
      if (!stlHelpers.IsLast(q, *p))
      {
        std::cout << *q << ", ";
      }
      else
      {
        std::cout << *q << "]";
      }
    }
    if (!stlHelpers.IsLast(p, bands))
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << "]";
    }
  }
  std::cout << std::endl;
}

//-----------------------------------------------------------------------------
void MakeElevations(vtkPolyData* src, vtkPolyData* elev)
{
  double bounds[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  src->GetBounds(bounds);
  vtkSmartPointer<vtkElevationFilter> elevFilter =
    vtkSmartPointer<vtkElevationFilter>::New();
  elevFilter->SetInputData(src);
  elevFilter->SetLowPoint(0, bounds[2], 0);
  elevFilter->SetHighPoint(0, bounds[3], 0);
  elevFilter->SetScalarRange(bounds[2], bounds[3]);
  elevFilter->Update();
  elev->DeepCopy(elevFilter->GetPolyDataOutput());
}

//-----------------------------------------------------------------------------
void MakeTorus(vtkPolyData* src)
{
  vtkSmartPointer<vtkSuperquadricSource> source =
    vtkSmartPointer<vtkSuperquadricSource>::New();
  source->SetCenter(0.0, 0.0, 0.0);
  source->SetCenter(1.0, 1.0, 1.0);
  source->SetPhiResolution(64);
  source->SetThetaResolution(64);
  source->SetThetaRoundness(1);
  source->SetThickness(0.5);
  source->SetSize(10);
  source->SetToroidal(1);
  source->Update();

  // The quadric is made of strips, so pass it through a triangle filter as
  // the curvature filter only operates on polys
  vtkSmartPointer<vtkTriangleFilter> tri =
    vtkSmartPointer<vtkTriangleFilter>::New();
  tri->SetInputConnection(source->GetOutputPort());

  // The quadric has nasty discontinuities from the way the edges are generated
  // so let's pass it though a CleanPolyDataFilter and merge any points which
  // are coincident, or very close
  vtkSmartPointer<vtkCleanPolyData> cleaner =
    vtkSmartPointer<vtkCleanPolyData>::New();
  cleaner->SetInputConnection(tri->GetOutputPort());
  cleaner->SetTolerance(0.005);
  cleaner->Update();

  vtkSmartPointer<vtkPolyData> elev =
    vtkSmartPointer<vtkPolyData>::New();
  MakeElevations(cleaner->GetOutput(), elev);
  CalculateCurvatures(elev, src);
}

//-----------------------------------------------------------------------------
void MakeParametricTorus(vtkPolyData* src)
{
  vtkSmartPointer<vtkParametricTorus> fn =
    vtkSmartPointer<vtkParametricTorus>::New();
  fn->SetRingRadius(5);
  fn->SetCrossSectionRadius(2);

  vtkSmartPointer<vtkParametricFunctionSource> source =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetParametricFunction(fn);
  source->SetUResolution(50);
  source->SetVResolution(50);
  source->SetScalarModeToZ();
  source->Update();
  // Name the arrays (not needed in VTK 6.2+ for vtkParametricFunctionSource)
  source->GetOutput()->GetPointData()->GetNormals()->SetName("Normals");
  // We have calculated the elevation, just rename the scalars.
  source->GetOutput()->GetPointData()->GetScalars()->SetName("Elevation");
  CalculateCurvatures(source->GetOutput(), src);
}

//-----------------------------------------------------------------------------
void MakeParametricHills(vtkPolyData* src)
{
  vtkSmartPointer<vtkParametricRandomHills> fn =
    vtkSmartPointer<vtkParametricRandomHills>::New();
  fn->AllowRandomGenerationOn();
  fn->SetRandomSeed(1);
  fn->SetNumberOfHills(30);
  // Make the normals face out of the surface.
  // Not needed with VTK 8.0 or later.
  if (strcmp(fn->GetClassName(), "vtkParametricRandomHills") == 0)
  {
    fn->ClockwiseOrderingOff();
  }

  vtkSmartPointer<vtkParametricFunctionSource> source =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  source->SetParametricFunction(fn);
  source->SetUResolution(50);
  source->SetVResolution(50);
  source->SetScalarModeToZ();
  source->Update();
  // Name the arrays (not needed in VTK 6.2+ for vtkParametricFunctionSource)
  source->GetOutput()->GetPointData()->GetNormals()->SetName("Normals");
  // We have calculated the elevation, just rename the scalars.
  source->GetOutput()->GetPointData()->GetScalars()->SetName("Elevation");
  CalculateCurvatures(source->GetOutput(), src);
}

//-----------------------------------------------------------------------------
void Clipper(vtkPolyData* src, double const& dx, double const& dy,
  double const& dz, vtkPolyData* clipped)
{
  double bounds[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  src->GetBounds(bounds);

  vtkSmartPointer<vtkPlane> plane1 =
    vtkSmartPointer<vtkPlane>::New();
  plane1->SetOrigin(bounds[0] + dx, 0, 0);
  plane1->SetNormal(1, 0, 0);

  vtkSmartPointer<vtkPlane> plane2 =
    vtkSmartPointer<vtkPlane>::New();
  plane2->SetOrigin(bounds[1] - dx, 0, 0);
  plane2->SetNormal(-1, 0, 0);

  vtkSmartPointer<vtkPlane> plane3 =
    vtkSmartPointer<vtkPlane>::New();
  plane3->SetOrigin(0, bounds[2] + dy, 0);
  plane3->SetNormal(0, 1, 0);

  vtkSmartPointer<vtkPlane> plane4 =
    vtkSmartPointer<vtkPlane>::New();
  plane4->SetOrigin(0, bounds[3] - dy, 0);
  plane4->SetNormal(0, -1, 0);

  vtkSmartPointer<vtkPlane> plane5 =
    vtkSmartPointer<vtkPlane>::New();
  plane5->SetOrigin(0, 0, bounds[4] + dz);
  plane5->SetNormal(0, 0, 1);

  vtkSmartPointer<vtkPlane> plane6 =
    vtkSmartPointer<vtkPlane>::New();
  plane6->SetOrigin(0, 0, bounds[5] - dz);
  plane6->SetNormal(0, 0, -1);

  vtkSmartPointer<vtkImplicitBoolean> clipFunction =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  clipFunction->SetOperationTypeToUnion();
  clipFunction->AddFunction(plane1);
  clipFunction->AddFunction(plane2);
  clipFunction->AddFunction(plane3);
  clipFunction->AddFunction(plane4);
  clipFunction->AddFunction(plane5);
  clipFunction->AddFunction(plane6);

  // Create clipper for the random hills
  vtkSmartPointer<vtkClipPolyData> clipper =
    vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetClipFunction(clipFunction);
  clipper->SetInputData(src);
  clipper->GenerateClipScalarsOff();
  clipper->GenerateClippedOutputOff();
  // clipper->GenerateClippedOutputOn();
  clipper->Update();
  clipped->DeepCopy(clipper->GetOutput());
}

//-----------------------------------------------------------------------------
void CalculateCurvatures(vtkPolyData* src, vtkPolyData* curv)
{
  // Calculate the curvature.
  vtkSmartPointer<vtkCurvatures> curvature =
    vtkSmartPointer<vtkCurvatures>::New();
  curvature->SetCurvatureTypeToGaussian();
  curvature->SetInputData(src);
  curvature->Update();
  curv->DeepCopy(curvature->GetOutput());
}

//-----------------------------------------------------------------------------
void MakeLUT(vtkLookupTable* lut)
{
  // Make the lookup table.
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  // Select a color scheme.
  int colorSeriesEnum;
  // colorSeriesEnum = colorSeries->BREWER_DIVERGING_BROWN_BLUE_GREEN_9;
  // colorSeriesEnum = colorSeries->BREWER_DIVERGING_SPECTRAL_10;
  // colorSeriesEnum = colorSeries->BREWER_DIVERGING_SPECTRAL_3;
  // colorSeriesEnum = colorSeries->BREWER_DIVERGING_PURPLE_ORANGE_9;
  // colorSeriesEnum = colorSeries->BREWER_SEQUENTIAL_BLUE_PURPLE_9;
  // colorSeriesEnum = colorSeries->BREWER_SEQUENTIAL_BLUE_GREEN_9;
  colorSeriesEnum = colorSeries->BREWER_QUALITATIVE_SET3;
  // colorSeriesEnum = colorSeries->CITRUS;
  colorSeries->SetColorScheme(colorSeriesEnum);
  colorSeries->BuildLookupTable(lut);
  lut->SetNanColor(0, 0, 0, 1);
}

//! Create a lookup table with the colors reversed.
/*!
@param lut - An indexed lookup table.
@param lutr - The reversed indexed lookup table.
*/
//-----------------------------------------------------------------------------
void ReverseLUT(vtkLookupTable* lut, vtkLookupTable* lutr)
{
  // First do a deep copy just to get the whole structure
  // and then reverse the colors and annotations.
  lutr->DeepCopy(lut);
  vtkIdType t = lut->GetNumberOfTableValues() - 1;
  for (vtkIdType i = t; i >= 0; --i)
  {
    double rgba[4] = {0.0, 0.0, 0.0, 0.0};
    lut->GetColor(i, rgba);
    rgba[3] = lut->GetOpacity(i);
    lutr->SetTableValue(t - i, rgba);
  }
  t = lut->GetNumberOfAnnotatedValues() - 1;
  for (vtkIdType i = t; i >= 0; --i)
  {
    lutr->SetAnnotation(t - i, lut->GetAnnotation(i));
  }
}

//-----------------------------------------------------------------------------
std::vector<int> Frequencies(
  std::vector<std::vector<double>> const& bands, vtkPolyData* src)
{
  std::vector<int> freq(bands.size(), 0);
  vtkIdType tuples = src->GetPointData()->GetScalars()->GetNumberOfTuples();
  for (int i = 0; i < tuples; ++i)
  {
    double* x = src->GetPointData()->GetScalars()->GetTuple(i);
    for (size_t j = 0; j < bands.size(); ++j)
    {
      if (*x <= bands[j][2])
      {
        freq[j] = freq[j] + 1;
        break;
      }
    }
  }
  return freq;
}

//-----------------------------------------------------------------------------
void PrintFrequencies(std::vector<int>& freq)
{
  STLHelpers stlHelpers = STLHelpers();
  int i = 0;
  for (std::vector<int>::const_iterator p = freq.begin(); p != freq.end(); ++p)
  {
    if (p == freq.begin())
    {
      std::cout << "[";
    }
    if (stlHelpers.IsLast(p, freq))
    {
      std::cout << i << ": " << *p << "]";
    }
    else
    {
      std::cout << i << ": " << *p << ", ";
    }
    ++i;
  }
  std::cout << endl;
}

//-----------------------------------------------------------------------------
void MakeGlyphs(vtkPolyData* src, bool const& reverseNormals, vtkGlyph3D* glyph)
{
  // Sometimes the contouring algorithm can create a volume whose gradient
  // vector and ordering of polygon(using the right hand rule) are
  // inconsistent. vtkReverseSense cures this problem.
  vtkSmartPointer<vtkReverseSense> reverse =
    vtkSmartPointer<vtkReverseSense>::New();
  vtkSmartPointer<vtkMaskPoints> maskPts =
    vtkSmartPointer<vtkMaskPoints>::New();
  maskPts->SetOnRatio(5);
  maskPts->RandomModeOn();
  if (reverseNormals)
  {
    reverse->SetInputData(src);
    reverse->ReverseCellsOn();
    reverse->ReverseNormalsOn();
    maskPts->SetInputConnection(reverse->GetOutputPort());
  }
  else
  {
    maskPts->SetInputData(src);
  }

  // Source for the glyph filter
  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();
  arrow->SetTipResolution(16);
  arrow->SetTipLength(0.3);
  arrow->SetTipRadius(0.1);

  glyph->SetSourceConnection(arrow->GetOutputPort());
  glyph->SetInputConnection(maskPts->GetOutputPort());
  glyph->SetVectorModeToUseNormal();
  glyph->SetScaleFactor(1);
  glyph->SetColorModeToColorByVector();
  glyph->SetScaleModeToScaleByVector();
  glyph->OrientOn();
  glyph->Update();
}

//-----------------------------------------------------------------------------
void Display(SURFACE_TYPE st, vtkRenderWindowInteractor* iren)
{

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg{{179, 204, 255, 255}};
    colors->SetColor("BkgColor", bkg.data());

  // ------------------------------------------------------------
  // Create the surface, lookup tables, contour filter etc.
  // ------------------------------------------------------------
  vtkSmartPointer<vtkPolyData> src =
    vtkSmartPointer<vtkPolyData>::New();
  switch (st)
  {
    case TORUS:
    {
      MakeTorus(src);
      break;
    }
    case PARAMETRIC_TORUS:
    {
      MakeParametricTorus(src);
      break;
    }
    case PARAMETRIC_HILLS:
    {
      vtkSmartPointer<vtkPolyData> hills =
        vtkSmartPointer<vtkPolyData>::New();
      MakeParametricHills(hills);
      Clipper(hills, 0.5, 0.5, 0.0, src);
      break;
    }
    default:
    {
      std::cout << "No surface specified." << std::endl;
      return;
    }
  }
  //  Here we are assuming that the active scalars are the curvatures.
  // in the parametric surfaces, so change the name.
  char* curvatureName = src->GetPointData()->GetScalars()->GetName();
  //  Use this range to color the glyphs for the normals by elevation.
  src->GetPointData()->SetActiveScalars("Elevation");
  double scalarRangeElevation[2];
  src->GetScalarRange(scalarRangeElevation);
  src->GetPointData()->SetActiveScalars(curvatureName);
  double scalarRangeCurvatures[2];
  src->GetScalarRange(scalarRangeCurvatures);
  double scalarRange[2];
  scalarRange[0] = scalarRangeCurvatures[0];
  scalarRange[1] = scalarRangeCurvatures[1];

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  MakeLUT(lut);
  vtkIdType numberOfBands = lut->GetNumberOfTableValues();
  std::vector<std::vector<double>> bands;
  if (st == PARAMETRIC_HILLS)
  {
    // Comment this out if you want to see how allocating
    // equally spaced bands works.
    bands = MakeCustomBands(scalarRange, numberOfBands);
    // Adjust the number of table values
    numberOfBands = static_cast<vtkIdType>(bands.size());
    lut->SetNumberOfTableValues(numberOfBands);
  }
  else
  {
    bands = MakeBands(scalarRange, numberOfBands, false);
  }
  lut->SetTableRange(scalarRange);

  // PrintBands(bands);

  // Let's do a frequency table.
  // The number of scalars in each band.
  // std::vector<int> freq = Frequencies(bands, src);
  // PrintFrequencies(freq);

  // We will use the midpoint of the band as the label.
  std::vector<std::string> labels;
  for (std::vector<std::vector<double>>::const_iterator p = bands.begin();
       p != bands.end(); ++p)
  {
    std::ostringstream os;
    os << std::fixed << std::setw(6) << std::setprecision(2) << (*p)[1];
    labels.push_back(os.str());
  }

  // Annotate
  vtkSmartPointer<vtkVariantArray> values =
    vtkSmartPointer<vtkVariantArray>::New();
  for (size_t i = 0; i < labels.size(); ++i)
  {
    values->InsertNextValue(vtkVariant(labels[i]));
  }
  for (vtkIdType i = 0; i < values->GetNumberOfTuples(); ++i)
  {
    lut->SetAnnotation(i, values->GetValue(i).ToString());
  }

  // Create a lookup table with the colors reversed.
  vtkSmartPointer<vtkLookupTable> lutr =
    vtkSmartPointer<vtkLookupTable>::New();
  ReverseLUT(lut, lutr);

  // Create the contour bands.
  vtkSmartPointer<vtkBandedPolyDataContourFilter> bcf =
    vtkSmartPointer<vtkBandedPolyDataContourFilter>::New();
  bcf->SetInputData(src);
  // Use either the minimum or maximum value for each band.
  int i = 0;
  for (std::vector<std::vector<double>>::const_iterator p = bands.begin();
       p != bands.end(); ++p)
  {
    bcf->SetValue(i, (*p)[2]);
    ++i;
  }
  // We will use an indexed lookup table.
  bcf->SetScalarModeToIndex();
  bcf->GenerateContourEdgesOn();

  // Generate the glyphs on the original surface.
  vtkSmartPointer<vtkGlyph3D> glyph =
    vtkSmartPointer<vtkGlyph3D>::New();
  MakeGlyphs(src, false, glyph);

  // ------------------------------------------------------------
  // Create the mappers and actors
  // ------------------------------------------------------------

  vtkSmartPointer<vtkPolyDataMapper> srcMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  srcMapper->SetInputConnection(bcf->GetOutputPort());
  srcMapper->SetScalarRange(scalarRange);
  srcMapper->SetLookupTable(lut);
  srcMapper->SetScalarModeToUseCellData();

  vtkSmartPointer<vtkActor> srcActor =
    vtkSmartPointer<vtkActor>::New();
  srcActor->SetMapper(srcMapper);
  srcActor->RotateX(-45);
  srcActor->RotateZ(45);

  // Create contour edges
  vtkSmartPointer<vtkPolyDataMapper> edgeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  edgeMapper->SetInputData(bcf->GetContourEdgesOutput());
  edgeMapper->SetResolveCoincidentTopologyToPolygonOffset();

  vtkSmartPointer<vtkActor> edgeActor =
    vtkSmartPointer<vtkActor>::New();
  edgeActor->SetMapper(edgeMapper);
  edgeActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());
  edgeActor->RotateX(-45);
  edgeActor->RotateZ(45);

  vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyphMapper->SetInputConnection(glyph->GetOutputPort());
  glyphMapper->SetScalarModeToUsePointFieldData();
  glyphMapper->SetColorModeToMapScalars();
  glyphMapper->ScalarVisibilityOn();
  glyphMapper->SelectColorArray("Elevation");
  // Colour by scalars.
  // The default lookup table is used but you can
  // use whatever lookup table you like.
  glyphMapper->SetScalarRange(scalarRangeElevation);

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->SetMapper(glyphMapper);
  glyphActor->RotateX(-45);
  glyphActor->RotateZ(45);

  // Add a scalar bar->
  vtkSmartPointer<vtkScalarBarActor> scalarBar =
    vtkSmartPointer<vtkScalarBarActor>::New();
  // This LUT puts the lowest value at the top of the scalar bar.
  // scalarBar->SetLookupTable(lut);
  // Use this LUT if you want the highest value at the top.
  scalarBar->SetLookupTable(lutr);
  scalarBar->SetTitle("Gaussian\nCurvature");

  // ------------------------------------------------------------
  // Create the RenderWindow, Renderer and Interactor
  // ------------------------------------------------------------
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();

  renWin->AddRenderer(ren);
  iren->SetRenderWindow(renWin);

  // add actors
  ren->AddViewProp(srcActor);
  ren->AddViewProp(edgeActor);
  ren->AddViewProp(glyphActor);
  ren->AddActor2D(scalarBar);

  ren->SetBackground(colors->GetColor3d("BkgColor").GetData());
  renWin->SetSize(800, 800);
  renWin->Render();

  ren->GetActiveCamera()->Zoom(1.5);
}


}
