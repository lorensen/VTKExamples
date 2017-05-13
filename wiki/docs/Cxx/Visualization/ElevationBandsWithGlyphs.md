[VTKExamples](Home)/[Cxx](Cxx)/Visualization/ElevationBandsWithGlyphs

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestElevationBandsWithGlyphs.png" width="256" />

### Description
In this example we are coloring the surface by partitioning the elevation
into bands and using arrows to display the normals on the surface.

Rather beautiful surfaces are generated.

The banded contour filter and an indexed lookup table are used along with 
the elevation filter to generate the banding on the surface.
To further enhance the surface the surface normals are
glyphed and colored by elevation using the default lookup table. 

The example also demonstrates partitioning the pipelines into functions.

For generating surfaces, the trick here is to return vtkPolydata for surfaces
thereby hiding the particular surface properties in the implementation of the
function. This allows us to specify multiple surface types and, in this code,
to use an enum to pick the one we want.

The process is as follows:
1. Use an enum to select your surface.
2. Use vtkColorSeries to make an indexed lookup table.
3. Then we use the number of colors in the lookup table and the scalar range of the surface to create a list/vector of bands.
4. This list is then used to define the labels for the scalar bar using the midpoints of the ranges in the bands as the labels.
5. Once this is done, we annotate the lookup table and then create a reversed lookup table. This will be used by the scalar bar actor.
6. The maximum values in the ranges in the bands are used to set the bands in the banded contour filter.
7. Glyphs are then created for the normals.
8. Then everything is put together for the rendering in the usual actor/mapper pipeline. The reversed lookup table is used by the scalar bar actor so that the maximum value is at the top if the actor is placed in its default orientation/position.
9. The function Display() pulls together all the components and returns a vtkRenderWindowInteractor so that you can interact with the image.

Feel free to experiment with different color schemes and/or the other
sources from the parametric function group or a cone etc.

Note that in the function MakeParametricSurface() we use ClockwiseOrderingOff() when using vtkParametricRandomHills as a source, this ensures that the normals face in the expected direction, the default is ClockwiseOrderingOn(). As an alternative, in MakeGlyphs(), you can set reverseNormals to true thereby invoking vtkReverseSense to achieve the same effect.

You will usually need to adjust the parameters for maskPts,
arrow and glyph for a nice appearance.
Do this in the function MakeGlyphs().

You may also need to add an elevation filter to generate the scalars
as demonstrated in MakePlane() and MakeSphere().

PrintBands() and PrintFrequencies() allow you to inspect the bands and
the number of scalars in each band. These are useful if you want to
get an idea of the distribution of the scalars in each band.

**ElevationBandsWithGlyphs.cxx**
```c++
// The source
#include <vtkParametricRandomHills.h>
#include <vtkParametricFunctionSource.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSphereSource.h>
#include <vtkPlaneSource.h>
#include <vtkElevationFilter.h>
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

enum SURFACE_TYPE { PLANE = 0, SPHERE, PARAMETRIC_SURFACE };

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

  //! Make a plane as the source.
  /*!
  @param src - the vtkPolyData source.
  */
  void MakePlane(vtkPolyData *src);

  //! Make a sphere as the source.
  /*!
  @param src - the vtkPolyData source.
  */
  void MakeSphere(vtkPolyData *src);

  //! Make a parametric surface as the source.
  /*!
  @param src - the vtkPolyData source.
  */
  void MakeParametricSurface(vtkPolyData *src);

  //! Create a lookup table.
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
  @param iren - the vtkRenderWindowInteractor.
  */
  void Display(SURFACE_TYPE st, vtkRenderWindowInteractor *iren);

  //-----------------------------------------------------------------------------

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
  void MakeSphere(vtkPolyData *src)
  {
    VTK_SP(vtkSphereSource, source);
    source->SetCenter(0.0, 0.0, 0.0);
    source->SetRadius(10.0);
    source->SetThetaResolution(32);
    source->SetPhiResolution(32);
    source->Update();
    MakeElevations(source->GetOutput(), src);
  }

  //-----------------------------------------------------------------------------
  void MakePlane(vtkPolyData *src)
  {
    VTK_SP(vtkPlaneSource, source);
    source->SetOrigin(-10.0, -10.0, 0.0);
    source->SetPoint2(-10.0, 10.0, 0.0);
    source->SetPoint1(10.0, -10.0, 0.0);
    source->SetXResolution(20);
    source->SetYResolution(20);
    source->Update();
    MakeElevations(source->GetOutput(), src);
  }

  //-----------------------------------------------------------------------------
  void MakeParametricSurface(vtkPolyData *src)
  {
    VTK_SP(vtkParametricRandomHills, fn);
    fn->AllowRandomGenerationOn();
    fn->SetRandomSeed(1);
    fn->SetNumberOfHills(30);
    if (strcmp(fn->GetClassName(),"vtkParametricRandomHills") == 0)
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
    source->GetOutput()->GetPointData()->GetScalars()->SetName("Scalars");
    src->DeepCopy(source->GetOutput());
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
    lut->SetNanColor(1, 0, 0, 1);
  }

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
  //! Make and display the surface.
  void Display(SURFACE_TYPE st, vtkRenderWindowInteractor *iren)
  {
    // ------------------------------------------------------------
    // Create the surface, lookup tables, contour filter etc.
    // ------------------------------------------------------------
    VTK_SP(vtkPolyData, src);
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

    VTK_SP(vtkLookupTable, lut);
    MakeLUT(lut);
    lut->SetTableRange(scalarRange);
    vtkIdType numberOfBands = lut->GetNumberOfTableValues();

    std::vector<std::vector<double> > bands =
      MakeBands(scalarRange, numberOfBands, false);
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
    // Color by scalars.
    // The default lookup table is used but you can
    // use whatever lookup table you like.
    glyphMapper->SetScalarRange(scalarRange);

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
    scalarBar->SetTitle("Elevation (m)");

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
  //Display(PLANE, iren);
  //Display(SPHERE, iren);
  Display(PARAMETRIC_SURFACE, iren);
  iren->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ElevationBandsWithGlyphs)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ElevationBandsWithGlyphs MACOSX_BUNDLE ElevationBandsWithGlyphs.cxx)
 
target_link_libraries(ElevationBandsWithGlyphs ${VTK_LIBRARIES})
```

**Download and Build ElevationBandsWithGlyphs**

Click [here to download ElevationBandsWithGlyphs](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ElevationBandsWithGlyphs.tar) and its *CMakeLists.txt* file.
Once the *tarball ElevationBandsWithGlyphs.tar* has been downloaded and extracted,
```
cd ElevationBandsWithGlyphs/build 
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
./ElevationBandsWithGlyphs
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

