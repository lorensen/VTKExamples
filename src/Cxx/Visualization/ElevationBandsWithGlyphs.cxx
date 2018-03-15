#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkBandedPolyDataContourFilter.h>
#include <vtkCamera.h>
#include <vtkColorSeries.h>
#include <vtkElevationFilter.h>
#include <vtkGlyph3D.h>
#include <vtkLookupTable.h>
#include <vtkMaskPoints.h>
#include <vtkNamedColors.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricRandomHills.h>
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
  PLANE = 0,
  SPHERE,
  PARAMETRIC_SURFACE
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

//! Make a plane as the source.
/*!
@param src - the vtkPolyData source.
*/
void MakePlane(vtkPolyData* src);

//! Make a sphere as the source.
/*!
@param src - the vtkPolyData source.
*/
void MakeSphere(vtkPolyData* src);

//! Make a parametric surface as the source.
/*!
@param src - the vtkPolyData source.
*/
void MakeParametricSurface(vtkPolyData* src);

//! Create a lookup table.
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
@param iren - the vtkRenderWindowInteractor.
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
  // Display(PLANE, iren);
  // Display(SPHERE, iren);
  Display(PARAMETRIC_SURFACE, iren);
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
void MakeSphere(vtkPolyData* src)
{
  vtkSmartPointer<vtkSphereSource> source =
    vtkSmartPointer<vtkSphereSource>::New();
  source->SetCenter(0.0, 0.0, 0.0);
  source->SetRadius(10.0);
  source->SetThetaResolution(32);
  source->SetPhiResolution(32);
  source->Update();
  MakeElevations(source->GetOutput(), src);
}

//-----------------------------------------------------------------------------
void MakePlane(vtkPolyData* src)
{
  vtkSmartPointer<vtkPlaneSource> source =
    vtkSmartPointer<vtkPlaneSource>::New();
  source->SetOrigin(-10.0, -10.0, 0.0);
  source->SetPoint2(-10.0, 10.0, 0.0);
  source->SetPoint1(10.0, -10.0, 0.0);
  source->SetXResolution(20);
  source->SetYResolution(20);
  source->Update();
  MakeElevations(source->GetOutput(), src);
}

//-----------------------------------------------------------------------------
void MakeParametricSurface(vtkPolyData* src)
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
  source->GetOutput()->GetPointData()->GetScalars()->SetName("Scalars");
  src->DeepCopy(source->GetOutput());
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
  lut->SetNanColor(1, 0, 0, 1);
}

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
//! Make and display the surface.
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
    case PLANE:
    {
      MakePlane(src);
      break;
    }
    case SPHERE:
    {
      MakeSphere(src);
      break;
    }
    case PARAMETRIC_SURFACE:
    {
      MakeParametricSurface(src);
      // The scalars are named "Scalars"by default
      // in the parametric surfaces, so change the name.
      src->GetPointData()->GetScalars()->SetName("Elevation");
      break;
    }
    default:
    {
      std::cout << "No surface specified." << std::endl;
      return;
    }
  }
  double scalarRange[2];
  src->GetScalarRange(scalarRange);

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  MakeLUT(lut);
  lut->SetTableRange(scalarRange);
  vtkIdType numberOfBands = lut->GetNumberOfTableValues();

  std::vector<std::vector<double>> bands =
    MakeBands(scalarRange, numberOfBands, false);
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
  // Color by scalars.
  // The default lookup table is used but you can
  // use whatever lookup table you like.
  glyphMapper->SetScalarRange(scalarRange);

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
  scalarBar->SetTitle("Elevation (m)");

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
