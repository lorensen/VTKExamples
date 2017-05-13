[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/ImplicitModeller

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestImplicitModeller.png?raw=true" width="256" />

**ImplicitModeller.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImplicitModeller.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> inputPolyData;
  if(argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetPhiResolution(15);
    sphereSource->SetThetaResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  vtkSmartPointer<vtkImplicitModeller> implicitModeller =
    vtkSmartPointer<vtkImplicitModeller>::New();
  implicitModeller->SetSampleDimensions(50,50,50);
#if VTK_MAJOR_VERSION <= 5
  implicitModeller->SetInput(inputPolyData);
#else
  implicitModeller->SetInputData(inputPolyData);
#endif
  implicitModeller->AdjustBoundsOn();
  implicitModeller->SetAdjustDistance(.1); // Adjust by 10%
  implicitModeller->SetMaximumDistance(.1);

  // Compute the range to select a reasonable contour value
  double bounds[6];
  inputPolyData->GetBounds(bounds);
  double xrange = bounds[1] - bounds[0];

  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contourFilter =
    vtkSmartPointer<vtkContourFilter>::New();
  contourFilter->SetInputConnection(implicitModeller->GetOutputPort());
  contourFilter->SetValue(0, xrange/30.0); // 30% of xrange

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(contourFilter->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .3);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImplicitModeller)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImplicitModeller MACOSX_BUNDLE ImplicitModeller.cxx)
 
target_link_libraries(ImplicitModeller ${VTK_LIBRARIES})
```

**Download and Build ImplicitModeller**

Click [here to download ImplicitModeller](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImplicitModeller.tar) and its *CMakeLists.txt* file.
Once the *tarball ImplicitModeller.tar* has been downloaded and extracted,
```
cd ImplicitModeller/build 
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
./ImplicitModeller
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

