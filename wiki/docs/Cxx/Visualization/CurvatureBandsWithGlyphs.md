[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/CurvatureBandsWithGlyphs

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestCurvatureBandsWithGlyphs.png?raw=true" width="256" />

### Description
In this example we are coloring the surface by partitioning the gaussian curvature into bands and using arrows to display the normals on the surface.

Rather beautiful surfaces are generated.

The banded contour filter and an indexed lookup table are used along with 
the gaussian curvature filter to generate the banding on the surface.
To further enhance the surface the surface normals are
glyphed and colored by elevation using the default lookup table. 

The example also demonstrates partitioning the pipelines into functions and how
to generate a custom lookup table to handle irregular distributions of data.

For generating surfaces, the trick here is to return vtkPolydata for surfaces
thereby hiding the particular surface properties in the implementation of the
function. This allows us to specify multiple surface types and, in this code,
to use an enum to pick the one we want.

The surface selected is the parametric random hills surface. The problem with
the random hills surface is that most of the gaussian curvatures will lie in the range -1 to 0.2 (say) with a few large values say 20 to 40 at the peaks of the hills. Thus we need to manually allocate the color banding, this is done in the function MakeCustomBands(). The ranges selected in this function were determined by generating a frequency table for 20 bands and seeing where the values lie in the table. Then from this the distribution of the bands was made to best show the nature of the surface. The edges of the random hills surface have large irregular values so these are clipped.

The process is as follows:
1. Use an enum to select your surface generating elevations and curvatures and clipping is needed.
2. Use vtkColorSeries to make an indexed lookup table.
3. Then we use the number of colors in the lookup table and the scalar range of the surface to create a list/vector of bands. If need be we generate manual bands.
4. This list is then used to define the labels for the scalar bar using the midpoints of the ranges in the bands as the labels.
5. Once this is done, we annotate the lookup table and then create a reversed lookup table. This will be used by the scalar bar actor.
6.The maximum values in the ranges in the bands are used to set the bands in the banded contour filter.
7. Glyphs are then created for the normals.
8. Then everything is put together for the rendering in the usual actor/mapper pipeline. The reversed lookup table is used by the scalar bar actor so that the maximum value is at the top if the actor is placed in its default orientation/position.9. The function Display() pulls together all the components and returns a vtkRenderWindowInteractor so that you can interact with the image.

Feel free to experiment with different color schemes and/or the other
sources from the parametric function group or the torus etc.

Note that in the function MakeParametricHills() we use ClockwiseOrderingOff() when using vtkParametricRandomHills as a source, this ensures that the normals face in the expected direction, the default is ClockwiseOrderingOn(). As an alternative, in MakeGlyphs(), you can set reverseNormals to true thereby invoking vtkReverseSense to achieve the same effect.

You will usually need to adjust the parameters for maskPts,
arrow and glyph for a nice appearance.
Do this in the function MakeGlyphs().

PrintBands() and PrintFrequencies() allow you to inspect the bands and
the number of scalars in each band. These are useful if you want to
get an idea of the distribution of the scalars in each band.

**CurvatureBandsWithGlyphs.cxx**
```c++
// The source
#include <vtkSuperquadricSource.h>
#include <vtkParametricTorus.h>
#include <vtkParametricRandomHills.h>
#include <vtkParametricFunctionSource.h>
#include <vtkTriangleFilter.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSphereSource.h>
#include <vtkPlaneSource.h>
#include <vtkElevationFilter.h>
// Curvatures
#include <vtkClipPolyData.h>
#include <vtkCurvatures.h>
#include <vtkPlane.h>
#include <vtkImplicitBoolean.h>
// For annotating
#include <vtkVariantArray.h>
// Lookup table
#include <vtkColorSeries.h>
#include <vtkLookupTable.h>
// For glyphing
#include <vtkReverseSense.h>
#include <vtkMaskPoints.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
// For contouring
#include <vtkBandedPolyDataContourFilter.h>
// Mappers, actors, renderers etc.
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkScalarBarActor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkSmartPointer.h>
#define VTK_SP(type, name)\
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>

enum SURFACE_TYPE { TORUS = 0, PARAMETRIC_HILLS, PARAMETRIC_TORUS };

namespace {
  //! Some STL Utilities.
  class STLHelpers
  {
  public:
    //---------------------------------------------------------------------------
    STLHelpers(){}

    //---------------------------------------------------------------------------
    virtual ~STLHelpers(){}

    //-----------------------------------------------------------------------------
    // Convert a string to lowercase.
    std::string ToLowercase(const std::string & str)
    {
      std::string s;
      std::transform(str.begin(), str.end(), std::back_inserter(s),
        (int(*)(int))std::tolower);
      return s;
    }

    //-----------------------------------------------------------------------------
    // Replace all occurrences of old_value in a string with new_value.
    std::string ReplaceAll(std::string & str,
      const std::string & old_value, const std::string & new_value)
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
    bool IsLast(Iter iter, const Cont & cont)
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
  std::vector<std::vector<double> > MakeBands(double const dR[2],
    int const & numberOfBands, bool const & nearestInteger);

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
  std::vector<std::vector<double> > MakeCustomBands(double const dR[2],
    int const & numberOfBands);

  //! Divide a range into integral bands
  /*!
  Divide a range into bands
  @param dR - [min, max] the range that is to be covered by the bands.
  @return A List consisting of [min, midpoint, max] for each band.
  */
  std::vector<std::vector<double> > MakeIntegralBands(double const dR[2]);

  //! Print the bands.
  /*!
  @param bands - the bands.
  */
  void PrintBands(std::vector<std::vector<double> > const & bands);

  //! Generate elevations over the surface.
  /*!
  @param src - the vtkPolyData source.
  @param elev - the vtkPolyData source with elevations.
  */
  void MakeElevations(vtkPolyData *src, vtkPolyData *elev);

  //! Make a torus as the source.
  /*!
  @param The vtkPolyData source with normal and scalar data.
  */
  void MakeTorus(vtkPolyData *src);

  //! Make a parametric torus as the source.
  /*!
  @param The vtkPolyData source with normal and scalar data.
  */
  void MakeParametricTorus(vtkPolyData *src);

  //! Make a parametric hills surface as the source.
  /*!
  @param The vtkPolyData source with normal and scalar data.
  */
  void MakeParametricHills(vtkPolyData *src);

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
  void Clipper(vtkPolyData *src,
    double const & dx, double const & dy,
    double const & dz, vtkPolyData *clipped);

  //! Calculate curvatures.
  /*!
  The source must be triangulated.
  @param src - the source.
  @param curv - vtkPolyData with normals and scalar data representing curvatures.
  */
  void CalculateCurvatures(vtkPolyData *src, vtkPolyData *curv);

  /*!
  @param lut - An indexed lookup table.
  */
  void MakeLUT(vtkLookupTable *lut);

  //! Create a lookup table with the colors reversed.
  /*!
  @param lut - An indexed lookup table.
  @param lutr - The reversed indexed lookup table.
  */
  void ReverseLUT(vtkLookupTable *lut, vtkLookupTable *lutr);

  //! Count the number of scalars in each band.
  /*!
  @param bands - the bands.
  @param src - the vtkPolyData source.
  @return The frequencies of the scalars in each band.
  */
  std::vector<int> Frequencies(
    std::vector<std::vector<double> > const & bands,
    vtkPolyData * src);

  //! Print the frequency table.
  /*!
  @param freq - the frequencies.
  */
  void PrintFrequencies(std::vector<int> & freq);

  //!  Glyph the normals on the surface.
  /*!
  @param src - the vtkPolyData source.
  @param reverseNormals - if True the normals on the surface are reversed.
  @param glyph - The glyphs.
  */
  void MakeGlyphs(vtkPolyData *src, bool const & reverseNormals,
    vtkGlyph3D *glyph);

  //! Assemble the surface for display.
  /*!
  @param st - the surface to display.
  @param iren - the interactor.
  */
  void Display(SURFACE_TYPE st, vtkRenderWindowInteractor *iren);

  //-----------------------------------------------------------------------------
  std::vector<std::vector<double> > MakeBands(double const dR[2],
    int const & numberOfBands, bool const & nearestInteger)
  {
    std::vector<std::vector<double> > bands;
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
  std::vector<std::vector<double> > MakeCustomBands(double const dR[2],
    int const & numberOfBands)
  {
    std::vector<std::vector<double> > bands;
    if ((dR[1] < dR[0]) || (numberOfBands <= 0))
    {
      return bands;
    }
    // We can do this much better in c++11!
    double myBands[][2] = {
        { -0.7, -0.05 }, { -0.05, 0 },
        { 0, 0.13 }, { 0.13, 1.07 },
        { 1.07, 35.4 }, { 35.4, 37.1 }
      };
    std::vector<std::vector<double> > x;
    for (int i = 0; i < 6; ++i)
    {
      std::vector<double> tmp(2);
      tmp[0] = myBands[i][0]; tmp[1] = myBands[i][1];
      x.push_back(tmp);
    }
    // Set the minimum to match the range minimum.
    x[0][0] = dR[0];
    size_t sz = (static_cast<size_t>(numberOfBands) < x.size()) ?
      static_cast<size_t>(numberOfBands) : x.size();
    // Adjust the last band.
    std::vector<double> t = x[sz - 1];
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
  std::vector<std::vector<double> > MakeIntegralBands(double const dR[2])
  {
    std::vector<std::vector<double> > bands;
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
  void PrintBands(std::vector<std::vector<double> > const & bands)
  {
    STLHelpers stlHelpers = STLHelpers();
    for (std::vector<std::vector<double> >::const_iterator p = bands.begin();
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
  void MakeElevations(vtkPolyData *src, vtkPolyData *elev)
  {
    double bounds[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    src->GetBounds(bounds);
    VTK_SP(vtkElevationFilter, elevFilter);
    elevFilter->SetInputData(src);
    elevFilter->SetLowPoint(0, bounds[2], 0);
    elevFilter->SetHighPoint(0, bounds[3], 0);
    elevFilter->SetScalarRange(bounds[2], bounds[3]);
    elevFilter->Update();
    elev->DeepCopy(elevFilter->GetPolyDataOutput());
  }

  //-----------------------------------------------------------------------------
  void MakeTorus(vtkPolyData *src)
  {
    VTK_SP(vtkSuperquadricSource, source);
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
    VTK_SP(vtkTriangleFilter, tri);
    tri->SetInputConnection(source->GetOutputPort());

    // The quadric has nasty discontinuities from the way the edges are generated
    // so let's pass it though a CleanPolyDataFilter and merge any points which
    // are coincident, or very close
    VTK_SP(vtkCleanPolyData, cleaner);
    cleaner->SetInputConnection(tri->GetOutputPort());
    cleaner->SetTolerance(0.005);
    cleaner->Update();

    VTK_SP(vtkPolyData, elev);
    MakeElevations(cleaner->GetOutput(), elev);
    CalculateCurvatures(elev, src);
  }

  //-----------------------------------------------------------------------------
  void MakeParametricTorus(vtkPolyData *src)
  {
    VTK_SP(vtkParametricTorus, fn);
    fn->SetRingRadius(5);
    fn->SetCrossSectionRadius(2);

    VTK_SP(vtkParametricFunctionSource, source);
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
  void MakeParametricHills(vtkPolyData *src)
  {
    VTK_SP(vtkParametricRandomHills, fn);
    fn->AllowRandomGenerationOn();
    fn->SetRandomSeed(1);
    fn->SetNumberOfHills(30);
    if (strcmp(fn->GetClassName(), "vtkParametricRandomHills") == 0)
    {
      // Make the normals face out of the surface.
      fn->ClockwiseOrderingOff();
    }

    VTK_SP(vtkParametricFunctionSource, source);
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
  void Clipper(vtkPolyData *src,
    double const & dx, double const & dy,
    double const & dz, vtkPolyData *clipped)
  {
    double bounds[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    src->GetBounds(bounds);

    VTK_SP(vtkPlane, plane1);
    plane1->SetOrigin(bounds[0] + dx, 0, 0);
    plane1->SetNormal(1, 0, 0);

    VTK_SP(vtkPlane, plane2);
    plane2->SetOrigin(bounds[1] - dx, 0, 0);
    plane2->SetNormal(-1, 0, 0);

    VTK_SP(vtkPlane, plane3);
    plane3->SetOrigin(0, bounds[2] + dy, 0);
    plane3->SetNormal(0, 1, 0);

    VTK_SP(vtkPlane, plane4);
    plane4->SetOrigin(0, bounds[3] - dy, 0);
    plane4->SetNormal(0, -1, 0);

    VTK_SP(vtkPlane, plane5);
    plane5->SetOrigin(0, 0, bounds[4] + dz);
    plane5->SetNormal(0, 0, 1);

    VTK_SP(vtkPlane, plane6);
    plane6->SetOrigin(0, 0, bounds[5] - dz);
    plane6->SetNormal(0, 0, -1);

    VTK_SP(vtkImplicitBoolean, clipFunction);
    clipFunction->SetOperationTypeToUnion();
    clipFunction->AddFunction(plane1);
    clipFunction->AddFunction(plane2);
    clipFunction->AddFunction(plane3);
    clipFunction->AddFunction(plane4);
    clipFunction->AddFunction(plane5);
    clipFunction->AddFunction(plane6);

    // Create clipper for the random hills
    VTK_SP(vtkClipPolyData, clipper);
    clipper->SetClipFunction(clipFunction);
    clipper->SetInputData(src);
    clipper->GenerateClipScalarsOff();
    clipper->GenerateClippedOutputOff();
    //clipper->GenerateClippedOutputOn();
    clipper->Update();
    clipped->DeepCopy(clipper->GetOutput());
  }

  //-----------------------------------------------------------------------------
  void CalculateCurvatures(vtkPolyData *src, vtkPolyData *curv)
  {
    // Calculate the curvature.
    VTK_SP(vtkCurvatures, curvature);
    curvature->SetCurvatureTypeToGaussian();
    curvature->SetInputData(src);
    curvature->Update();
    curv->DeepCopy(curvature->GetOutput());
  }

  //-----------------------------------------------------------------------------
  void MakeLUT(vtkLookupTable *lut)
  {
    // Make the lookup table.
    VTK_SP(vtkColorSeries, colorSeries);
    // Select a color scheme.
    int colorSeriesEnum;
    //colorSeriesEnum = colorSeries->BREWER_DIVERGING_BROWN_BLUE_GREEN_9;
    //colorSeriesEnum = colorSeries->BREWER_DIVERGING_SPECTRAL_10;
    //colorSeriesEnum = colorSeries->BREWER_DIVERGING_SPECTRAL_3;
    //colorSeriesEnum = colorSeries->BREWER_DIVERGING_PURPLE_ORANGE_9;
    //colorSeriesEnum = colorSeries->BREWER_SEQUENTIAL_BLUE_PURPLE_9;
    //colorSeriesEnum = colorSeries->BREWER_SEQUENTIAL_BLUE_GREEN_9;
    colorSeriesEnum = colorSeries->BREWER_QUALITATIVE_SET3;
    //colorSeriesEnum = colorSeries->CITRUS;
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
  void ReverseLUT(vtkLookupTable *lut, vtkLookupTable *lutr)
  {
    // First do a deep copy just to get the whole structure
    // and then reverse the colors and annotations.
    lutr->DeepCopy(lut);
    vtkIdType t = lut->GetNumberOfTableValues() - 1;
    for (vtkIdType i = t; i >= 0; --i)
    {
      double rgba[4] = { 0.0, 0.0, 0.0, 0.0 };
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
    std::vector<std::vector<double> > const & bands,
    vtkPolyData * src)
  {
    std::vector<int> freq(bands.size(), 0);
    vtkIdType tuples =
      src->GetPointData()->GetScalars()->GetNumberOfTuples();
    for (int i = 0; i < tuples; ++i)
    {
      double *x = src->GetPointData()->GetScalars()->GetTuple(i);
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
  void PrintFrequencies(std::vector<int> & freq)
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
  void MakeGlyphs(vtkPolyData *src, bool const & reverseNormals, vtkGlyph3D *glyph)
  {
    // Sometimes the contouring algorithm can create a volume whose gradient
    // vector and ordering of polygon(using the right hand rule) are
    // inconsistent. vtkReverseSense cures this problem.
    VTK_SP(vtkReverseSense, reverse);
    VTK_SP(vtkMaskPoints, maskPts);
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
    VTK_SP(vtkArrowSource, arrow);
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
  void Display(SURFACE_TYPE st, vtkRenderWindowInteractor *iren)
  {
    // ------------------------------------------------------------
    // Create the surface, lookup tables, contour filter etc.
    // ------------------------------------------------------------
    VTK_SP(vtkPolyData, src);
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
        VTK_SP(vtkPolyData, hills);
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
    char * curvatureName = src->GetPointData()->GetScalars()->GetName();
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

    VTK_SP(vtkLookupTable, lut);
    MakeLUT(lut);
    vtkIdType numberOfBands = lut->GetNumberOfTableValues();
    std::vector<std::vector<double> > bands;
    if (st == PARAMETRIC_HILLS)
    {
      // Comment this out if you want to see how allocating
      // equally spaced bands works.
      bands = MakeCustomBands(scalarRange, numberOfBands);
      // Adjust the number of table values
      numberOfBands = bands.size();
      lut->SetNumberOfTableValues(numberOfBands);
    }
    else
    {
      bands = MakeBands(scalarRange, numberOfBands, false);
    }
    lut->SetTableRange(scalarRange);

    //PrintBands(bands);

    // Let's do a frequency table.
    // The number of scalars in each band.
    //std::vector<int> freq = Frequencies(bands, src);
    //PrintFrequencies(freq);

    // We will use the midpoint of the band as the label.
    std::vector<std::string> labels;
    for (std::vector<std::vector<double> >::const_iterator p = bands.begin();
      p != bands.end(); ++p)
    {
      std::ostringstream os;
      os << std::fixed << std::setw(6) << std::setprecision(2) << (*p)[1];
      labels.push_back(os.str());
    }

    // Annotate
    VTK_SP(vtkVariantArray, values);
    for (size_t i = 0; i < labels.size(); ++i)
    {
      values->InsertNextValue(vtkVariant(labels[i]));
    }
    for (vtkIdType i = 0; i < values->GetNumberOfTuples(); ++i)
    {
      lut->SetAnnotation(i, values->GetValue(i).ToString());
    }

    // Create a lookup table with the colors reversed.
    VTK_SP(vtkLookupTable, lutr);
    ReverseLUT(lut, lutr);

    // Create the contour bands.
    VTK_SP(vtkBandedPolyDataContourFilter, bcf);
    bcf->SetInputData(src);
    // Use either the minimum or maximum value for each band.
    int i = 0;
    for (std::vector<std::vector<double> >::const_iterator p = bands.begin();
      p != bands.end(); ++p)
    {
      bcf->SetValue(i, (*p)[2]);
      ++i;
    }
    // We will use an indexed lookup table.
    bcf->SetScalarModeToIndex();
    bcf->GenerateContourEdgesOn();

    // Generate the glyphs on the original surface.
    VTK_SP(vtkGlyph3D, glyph);
    MakeGlyphs(src, false, glyph);

    // ------------------------------------------------------------
    // Create the mappers and actors
    // ------------------------------------------------------------

    VTK_SP(vtkPolyDataMapper, srcMapper);
    srcMapper->SetInputConnection(bcf->GetOutputPort());
    srcMapper->SetScalarRange(scalarRange);
    srcMapper->SetLookupTable(lut);
    srcMapper->SetScalarModeToUseCellData();

    VTK_SP(vtkActor, srcActor);
    srcActor->SetMapper(srcMapper);
    srcActor->RotateX(-45);
    srcActor->RotateZ(45);

    // Create contour edges
    VTK_SP(vtkPolyDataMapper, edgeMapper);
    edgeMapper->SetInputData(bcf->GetContourEdgesOutput());
    edgeMapper->SetResolveCoincidentTopologyToPolygonOffset();

    VTK_SP(vtkActor, edgeActor);
    edgeActor->SetMapper(edgeMapper);
    edgeActor->GetProperty()->SetColor(0, 0, 0);
    edgeActor->RotateX(-45);
    edgeActor->RotateZ(45);

    VTK_SP(vtkPolyDataMapper, glyphMapper);
    glyphMapper->SetInputConnection(glyph->GetOutputPort());
    glyphMapper->SetScalarModeToUsePointFieldData();
    glyphMapper->SetColorModeToMapScalars();
    glyphMapper->ScalarVisibilityOn();
    glyphMapper->SelectColorArray("Elevation");
    // Colour by scalars.
    // The default lookup table is used but you can
    // use whatever lookup table you like.
    glyphMapper->SetScalarRange(scalarRangeElevation);

    VTK_SP(vtkActor, glyphActor);
    glyphActor->SetMapper(glyphMapper);
    glyphActor->RotateX(-45);
    glyphActor->RotateZ(45);

    // Add a scalar bar->
    VTK_SP(vtkScalarBarActor, scalarBar);
    // This LUT puts the lowest value at the top of the scalar bar.
    //scalarBar->SetLookupTable(lut);
    // Use this LUT if you want the highest value at the top.
    scalarBar->SetLookupTable(lutr);
    scalarBar->SetTitle("Gaussian\nCurvature");

    // ------------------------------------------------------------
    // Create the RenderWindow, Renderer and Interactor
    // ------------------------------------------------------------
    VTK_SP(vtkRenderer, ren);
    VTK_SP(vtkRenderWindow, renWin);

    renWin->AddRenderer(ren);
    iren->SetRenderWindow(renWin);

    // add actors
    ren->AddViewProp(srcActor);
    ren->AddViewProp(edgeActor);
    ren->AddViewProp(glyphActor);
    ren->AddActor2D(scalarBar);

    ren->SetBackground(0.7, 0.8, 1.0);
    renWin->SetSize(800, 800);
    renWin->Render();

    ren->GetActiveCamera()->Zoom(1.5);
  }

} // end of unnamed namespace

//-----------------------------------------------------------------------------
//! Make and display the surface.
int main(int, char *[])
{
  VTK_SP(vtkRenderWindowInteractor, iren);
  // Select the surface you want displayed.
  //Display(TORUS, iren);
  //Display(PARAMETRIC_TORUS, iren);
  Display(PARAMETRIC_HILLS, iren);
  iren->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CurvatureBandsWithGlyphs)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CurvatureBandsWithGlyphs MACOSX_BUNDLE CurvatureBandsWithGlyphs.cxx)
 
target_link_libraries(CurvatureBandsWithGlyphs ${VTK_LIBRARIES})
```

**Download and Build CurvatureBandsWithGlyphs**

Click [here to download CurvatureBandsWithGlyphs](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CurvatureBandsWithGlyphs.tar) and its *CMakeLists.txt* file.
Once the *tarball CurvatureBandsWithGlyphs.tar* has been downloaded and extracted,
```
cd CurvatureBandsWithGlyphs/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./CurvatureBandsWithGlyphs
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

