[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/QuantizePolyDataPoints

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestQuantizePolyDataPoints.png?raw=true" width="256" />

### Description
This example demonstrates how to "snap" points onto a discrete grid. This example rounds the coordinates of each point the the nearest .1

**QuantizePolyDataPoints.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkQuantizePolyDataPoints.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkXMLPolyDataReader.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(10);
  pointSource->Update();

  std::cout << "There are " << pointSource->GetNumberOfPoints()
            << " points." << std::endl;

  vtkSmartPointer<vtkQuantizePolyDataPoints> quantizeFilter =
    vtkSmartPointer<vtkQuantizePolyDataPoints>::New();
  quantizeFilter->SetInputConnection(pointSource->GetOutputPort());
  quantizeFilter->SetQFactor(.1);
  quantizeFilter->Update();

  vtkPolyData* quantized = quantizeFilter->GetOutput();
  std::cout << "There are " << quantized->GetNumberOfPoints()
            << " quantized points." << std::endl;

  for(vtkIdType i = 0; i < pointSource->GetOutput()->GetNumberOfPoints(); i++)
  {
    double pOrig[3];
    double pQuantized[3];
    pointSource->GetOutput()->GetPoint(i,pOrig);
    quantized->GetPoints()->GetPoint(i,pQuantized);

    std::cout << "Point " << i << " : ("
              << pOrig[0] << ", " << pOrig[1] << ", " << pOrig[2] << ")"
              << " (" << pQuantized[0] << ", " << pQuantized[1] << ", " << pQuantized[2]
              << ")" << std::endl;
  }

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(pointSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);

  vtkSmartPointer<vtkPolyDataMapper> quantizedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  quantizedMapper->SetInputConnection(quantizeFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> quantizedActor =
    vtkSmartPointer<vtkActor>::New();
  quantizedActor->SetMapper(quantizedMapper);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  // Add the sphere to the left and the cube to the right
  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(quantizedActor);

  leftRenderer->ResetCamera();

  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(QuantizePolyDataPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(QuantizePolyDataPoints MACOSX_BUNDLE QuantizePolyDataPoints.cxx)
 
target_link_libraries(QuantizePolyDataPoints ${VTK_LIBRARIES})
```

**Download and Build QuantizePolyDataPoints**

Click [here to download QuantizePolyDataPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/QuantizePolyDataPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball QuantizePolyDataPoints.tar* has been downloaded and extracted,
```
cd QuantizePolyDataPoints/build 
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
./QuantizePolyDataPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

