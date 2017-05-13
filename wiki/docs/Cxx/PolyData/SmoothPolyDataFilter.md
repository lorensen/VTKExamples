[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/SmoothPolyDataFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestSmoothPolyDataFilter.png?raw=true" width="256" />

**SmoothPolyDataFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkDelaunay2D.h>
#include <vtkMath.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkCamera.h>


int main(int, char *[])
{
    // Create parabola over a grid of points
    vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();

    int GridSize = 20;
    double z;
    for (int x = -GridSize; x < GridSize; x++)
    {
        for (int y = -GridSize; y < GridSize; y++)
        {
            z = vtkMath::Random(-1, 1)+ 0.05*x*x + 0.05*y*y;
            points->InsertNextPoint(x, y, z);
        }
    }

    // Add the grid points to a polydata object
    vtkSmartPointer<vtkPolyData> inputPolyData =
        vtkSmartPointer<vtkPolyData>::New();
    inputPolyData->SetPoints(points);

    // Triangulate the grid points
    vtkSmartPointer<vtkDelaunay2D> delaunay =
        vtkSmartPointer<vtkDelaunay2D>::New();
#if VTK_MAJOR_VERSION <= 5
    delaunay->SetInput(inputPolyData);
#else
    delaunay->SetInputData(inputPolyData);
#endif
    delaunay->Update();

    vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilter =
        vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    smoothFilter->SetInputConnection(delaunay->GetOutputPort());
    smoothFilter->SetNumberOfIterations(15);
    smoothFilter->SetRelaxationFactor(0.1);
    smoothFilter->FeatureEdgeSmoothingOff();
    smoothFilter->BoundarySmoothingOn();
    smoothFilter->Update();

    // Update normals on newly smoothed polydata
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(smoothFilter->GetOutputPort());
    normalGenerator->ComputePointNormalsOn();
    normalGenerator->ComputeCellNormalsOn();
    normalGenerator->Update();

    vtkSmartPointer<vtkPolyDataMapper> inputMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    inputMapper->SetInputConnection(delaunay->GetOutputPort());
    vtkSmartPointer<vtkActor> inputActor =
        vtkSmartPointer<vtkActor>::New();
    inputActor->SetMapper(inputMapper);

    vtkSmartPointer<vtkPolyDataMapper> smoothedMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    smoothedMapper->SetInputConnection(normalGenerator->GetOutputPort());
    vtkSmartPointer<vtkActor> smoothedActor =
        vtkSmartPointer<vtkActor>::New();
    smoothedActor->SetMapper(smoothedMapper);

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
    double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
    double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

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

    // Add the input parabola to the left and the smoothed parabola to the right
    leftRenderer->AddActor(inputActor);
    rightRenderer->AddActor(smoothedActor);

    leftRenderer->ResetCamera();
    leftRenderer->GetActiveCamera()->Azimuth(130);
    leftRenderer->GetActiveCamera()->Elevation(-80);

    rightRenderer->ResetCamera();
    rightRenderer->GetActiveCamera()->Azimuth(130);
    rightRenderer->GetActiveCamera()->Elevation(-80);

    renderWindow->Render();
    interactor->Start();

    return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SmoothPolyDataFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SmoothPolyDataFilter MACOSX_BUNDLE SmoothPolyDataFilter.cxx)
 
target_link_libraries(SmoothPolyDataFilter ${VTK_LIBRARIES})
```

**Download and Build SmoothPolyDataFilter**

Click [here to download SmoothPolyDataFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SmoothPolyDataFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball SmoothPolyDataFilter.tar* has been downloaded and extracted,
```
cd SmoothPolyDataFilter/build 
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
./SmoothPolyDataFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

