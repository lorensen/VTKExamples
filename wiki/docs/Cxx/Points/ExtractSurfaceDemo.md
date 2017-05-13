[VTKExamples](/index/)/[Cxx](/Cxx)/Points/ExtractSurfaceDemo

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Points/TestExtractSurfaceDemo.png?raw=true" width="256" />

### Description
This example loosely follows the most excellent paper by Curless and
Levoy: ["A Volumetric Method for Building Complex Models from Range
Images."](https://graphics.stanford.edu/papers/volrange) First it
estimates normals from the points, then creates a signed distance
field, followed by surface extraction of the zero-level set of the
distance field.

The image was created using the [Armadillo
dataset](https://github.com/lorensen/VTKWikiExamples/blob/master/Testing/Data/Armadillo.ply?raw=true)

This is a demo version of [ExtractSurface](Cxx/Points/ExtractSurface). It displays some a sampling of the normals with arrows. It also uses a different color for the front and back surfaces.

**NOTE:** The classes used in this example require vtk 7.1 or later.


**ExtractSurfaceDemo.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>
#include <vtkSTLReader.h>
#include <vtkPointSource.h>

#include <vtkPCANormalEstimation.h>
#include <vtkSignedDistance.h>
#include <vtkExtractSurface.h>
#include <vtkPointData.h>

#include <vtkArrowSource.h>
#include <vtkMaskPoints.h>
#include <vtkGlyph3D.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtksys/SystemTools.hxx>

static void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph);
static vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;

  double bounds[6];
  polyData->GetBounds(bounds);
  double range[3];
  for (int i = 0; i < 3; ++i)
  {
    range[i] = bounds[2*i + 1] - bounds[2*i];
  }

  int sampleSize = 15;

  std::cout << "Sample size is: " << sampleSize << std::endl;
  // Do we need to estimate normals?
  vtkSmartPointer<vtkSignedDistance> distance =
    vtkSmartPointer<vtkSignedDistance>::New();
  vtkSmartPointer<vtkPCANormalEstimation> normals =
    vtkSmartPointer<vtkPCANormalEstimation>::New();
  if (polyData->GetPointData()->GetNormals())
  {
    std::cout << "Using normals from input file" << std::endl;
    distance->SetInputData (polyData);
  }
  else
  {
    std::cout << "Estimating normals using PCANormalEstimation" << std::endl;
    normals->SetInputData (polyData);
    normals->SetSampleSize(sampleSize);
    normals->SetNormalOrientationToGraphTraversal();
    normals->FlipNormalsOn();
    distance->SetInputConnection (normals->GetOutputPort());
  }
  std::cout << "Range: "
            << range[0] << ", "
            << range[1] << ", "
            << range[2] << std::endl;
  int dimension = 512;
  double radius;
  radius = range[0] / static_cast<double>(dimension) * 3; // ~3 voxels
  std::cout << "Radius: " << radius << std::endl;

  distance->SetRadius(radius);
  distance->SetDimensions(dimension, dimension, dimension);
  distance->SetBounds(
    bounds[0] - range[0] * .1,
    bounds[1] + range[0] * .1,
    bounds[2] - range[1] * .1,
    bounds[3] + range[1] * .1,
    bounds[4] - range[2] * .1,
    bounds[5] + range[2] * .1);

  vtkSmartPointer<vtkExtractSurface> surface =
    vtkSmartPointer<vtkExtractSurface>::New();
  surface->SetInputConnection (distance->GetOutputPort());
  surface->SetRadius(radius * .99);
  surface->HoleFillingOn();
  surface->Update();

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  if (polyData->GetPointData()->GetNormals())
  {
    MakeGlyphs(polyData, radius * 2.0, glyph3D.GetPointer());
  }
  else
  {
    MakeGlyphs(normals->GetOutput(), radius * 2.0, glyph3D.GetPointer());
  }
  vtkSmartPointer<vtkPolyDataMapper> surfaceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  surfaceMapper->SetInputConnection(surface->GetOutputPort());
  surfaceMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkProperty> backProp =
    vtkSmartPointer<vtkProperty>::New();
  backProp->SetColor(0.8900, 0.8100, 0.3400);

  vtkSmartPointer<vtkActor> surfaceActor =
    vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(surfaceMapper);
  surfaceActor->GetProperty()->SetColor(1.0000, 0.4900, 0.2500);
  surfaceActor->SetBackfaceProperty(backProp);

  vtkSmartPointer<vtkPolyDataMapper> glyph3DMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkActor> glyph3DActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor->SetMapper(glyph3DMapper);
  glyph3DActor->GetProperty()->SetColor(0.6902, 0.7686, 0.8706);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(surfaceActor);
  ren1->AddActor(glyph3DActor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.0);
  ren1->ResetCameraClippingRange();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph)
{
  vtkSmartPointer<vtkMaskPoints> maskPts =
    vtkSmartPointer<vtkMaskPoints>::New();
  maskPts->SetOnRatio(20);
  maskPts->RandomModeOn();
  maskPts->SetInputData(src);
  // Source for the glyph filter
  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();
  arrow->SetTipResolution(16);
  arrow->SetTipLength(.3);
  arrow->SetTipRadius(.1);

  glyph->SetSourceConnection(arrow->GetOutputPort());
  glyph->SetInputConnection(maskPts->GetOutputPort());
  glyph->SetVectorModeToUseNormal();
//  glyph->SetColorModeToColorByVector();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(size);
  glyph->OrientOn();
  glyph->Update();
}

static vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkPointSource> points =
      vtkSmartPointer<vtkPointSource>::New();
    points->SetNumberOfPoints(100000);
    points->SetRadius(10.0);
    points->SetCenter(vtkMath::Random(-100, 100),
                      vtkMath::Random(-100, 100),
                      vtkMath::Random(-100, 100));
    points->SetDistributionToShell();
    points->Update();
    polyData = points->GetOutput();
  }
  return polyData;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractSurfaceDemo)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractSurfaceDemo MACOSX_BUNDLE ExtractSurfaceDemo.cxx)
 
target_link_libraries(ExtractSurfaceDemo ${VTK_LIBRARIES})
```

**Download and Build ExtractSurfaceDemo**

Click [here to download ExtractSurfaceDemo](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractSurfaceDemo.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractSurfaceDemo.tar* has been downloaded and extracted,
```
cd ExtractSurfaceDemo/build 
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
./ExtractSurfaceDemo
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

