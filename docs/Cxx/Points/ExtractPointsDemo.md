[VTKExamples](/index/)/[Cxx](/Cxx)/Points/ExtractPointsDemo

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Points/TestExtractPointsDemo.png?raw=true" width="256" />

### Description
Demonstrates point extraction from four implicit functions: sphere, cone, cylinder and superquadric.

'''NOTE: The classes used in this example require vtk 7.1 or later.'''

**ExtractPointsDemo.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkExtractPoints.h>

#include <vtkBoundedPointSource.h>
#include <vtkSphere.h>
#include <vtkCone.h>
#include <vtkCylinder.h>
#include <vtkSuperquadric.h>
#include <vtkBoundedPointSource.h>

#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vector>

int main (int argc, char *argv[])
{
  // Create implicit functions
  vtkSmartPointer<vtkCone> cone =
    vtkSmartPointer<vtkCone>::New();
  cone->SetAngle(30.0);
  vtkSmartPointer<vtkSphere> sphere =
    vtkSmartPointer<vtkSphere>::New();
  vtkSmartPointer<vtkCylinder> cylinder =
    vtkSmartPointer<vtkCylinder>::New();
  vtkSmartPointer<vtkSuperquadric> superquadric =
    vtkSmartPointer<vtkSuperquadric>::New();
  superquadric->SetPhiRoundness(2.5);
  superquadric->SetThetaRoundness(.5);

  // Store the functions
  std::vector<vtkSmartPointer<vtkImplicitFunction> > functions;
  functions.push_back(sphere);
  functions.push_back(cone);
  functions.push_back(cylinder);
  functions.push_back(superquadric);

  vtkSmartPointer<vtkBoundedPointSource> pointSource =
    vtkSmartPointer<vtkBoundedPointSource>::New();
  pointSource->SetNumberOfPoints(100000);

  // Rows and columns
  unsigned int gridXDimensions = 2;
  unsigned int gridYDimensions = 2;

  // Need a renderer even if there is no actor
  std::vector<vtkSmartPointer<vtkRenderer> > renderers;
  double background[6] = {.4, .5, .6, .6, .5, .4};
  for(size_t i = 0;
      i < gridXDimensions * gridYDimensions;
      i++)
  {
    renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
    renderers[i]->SetBackground(background);
    std::rotate(background, background + 1, background + 6);
  }

  // Glyphs
  double radius = .02;
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(radius);

  // One render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  int rendererSize = 256;
  renderWindow->SetSize(
    rendererSize*gridXDimensions, rendererSize*gridYDimensions);

  // Create a pipelone for each function
  for(int row = 0; row < static_cast<int>(gridYDimensions); row++)
  {
    for(int col = 0; col < static_cast<int>(gridXDimensions); col++)
    {
      int index = row*gridXDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] =
        {static_cast<double>(col) * rendererSize / (gridXDimensions * rendererSize),
         static_cast<double>(gridYDimensions - (row+1)) * rendererSize / (gridYDimensions * rendererSize),
         static_cast<double>(col+1)*rendererSize / (gridXDimensions * rendererSize),
         static_cast<double>(gridYDimensions - row) * rendererSize / (gridYDimensions * rendererSize)};
      renderWindow->AddRenderer(renderers[index]);
      renderers[index]->SetViewport(viewport);
      if(index > static_cast<int>(functions.size() - 1))
      {
        continue;
      }
      // Define the pipeline
      vtkSmartPointer<vtkExtractPoints> extract =
        vtkSmartPointer<vtkExtractPoints>::New();
      extract->SetInputConnection(pointSource->GetOutputPort());
      extract->SetImplicitFunction(functions[index]);

      vtkSmartPointer<vtkGlyph3D> glyph =
        vtkSmartPointer<vtkGlyph3D>::New();
      glyph->SetInputConnection(extract->GetOutputPort());
      glyph->SetSourceConnection(sphereSource->GetOutputPort());
      glyph->ScalingOff();

      vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
      glyphMapper->SetInputConnection(glyph->GetOutputPort());
      glyphMapper->ScalarVisibilityOff();

      vtkSmartPointer<vtkActor> glyphActor =
        vtkSmartPointer<vtkActor>::New();
      glyphActor->SetMapper(glyphMapper);

      renderers[index]->AddActor(glyphActor);
      renderers[index]->ResetCamera();
      renderers[index]->GetActiveCamera()->Azimuth(30);
      renderers[index]->GetActiveCamera()->Elevation(-30);
      renderers[index]->GetActiveCamera()->Dolly(1.1);
      renderers[index]->ResetCameraClippingRange();
    }
  }
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractPointsDemo)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractPointsDemo MACOSX_BUNDLE ExtractPointsDemo.cxx)
 
target_link_libraries(ExtractPointsDemo ${VTK_LIBRARIES})
```

**Download and Build ExtractPointsDemo**

Click [here to download ExtractPointsDemo](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractPointsDemo.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractPointsDemo.tar* has been downloaded and extracted,
```
cd ExtractPointsDemo/build 
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
./ExtractPointsDemo
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

