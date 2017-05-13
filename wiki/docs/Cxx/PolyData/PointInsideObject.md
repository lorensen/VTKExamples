[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/PointInsideObject

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestPointInsideObject.png?raw=true" width="256" />

### Description
This example creates a cube at the origin with side 1. Then it checks if the points are inside the cube. There is one point inside, one in the border and one outside. The answer for the first one should be yes, and for the other two, no. 
Then render the cube and the points to see the result.

**PointInsideObject.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkIntArray.h>
#include <vtkDataArray.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>


int main(int, char *argv[])
{
  //cube centered in origin, 1cm side.
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->Update();

  vtkPolyData* cube = cubeSource->GetOutput();

  double testInside[3] = {0.0, 0.0, 0.0};
  double testOutside[3] = {0.7, 0.0, 0.0};
  double testBorderOutside[3] = {0.5, 0.0, 0.0};
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(testInside);
  points->InsertNextPoint(testOutside);
  points->InsertNextPoint(testBorderOutside);

  vtkSmartPointer<vtkPolyData> pointsPolydata =
    vtkSmartPointer<vtkPolyData>::New();
  pointsPolydata->SetPoints(points);

  //Points inside test
  vtkSmartPointer<vtkSelectEnclosedPoints> selectEnclosedPoints =
    vtkSmartPointer<vtkSelectEnclosedPoints>::New();
#if VTK_MAJOR_VERSION <= 5
  selectEnclosedPoints->SetInput(pointsPolydata);
#else
  selectEnclosedPoints->SetInputData(pointsPolydata);
#endif
#if VTK_MAJOR_VERSION <= 5
  selectEnclosedPoints->SetSurface(cube);
#else
  selectEnclosedPoints->SetSurfaceData(cube);
#endif
  selectEnclosedPoints->Update();

  for(unsigned int i = 0; i < 2; i++)
  {
    std::cout << "Point " << i << ": " << selectEnclosedPoints->IsInside(i) << std::endl;
  }

  vtkDataArray* insideArray = vtkDataArray::SafeDownCast(selectEnclosedPoints->GetOutput()->GetPointData()->GetArray("SelectedPoints"));

  for(vtkIdType i = 0; i < insideArray->GetNumberOfTuples(); i++)
  {
    std::cout << i << " : " << insideArray->GetComponent(i,0) << std::endl;
  }


  //RENDERING PART

  //Cube mapper, actor
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetOpacity(0.5);

  //Points mapper, actor
  //First, apply vtkVertexGlyphFilter to make cells around points, vtk only render cells.
  vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
  vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexGlyphFilter->AddInput(pointsPolydata);
#else
  vertexGlyphFilter->AddInputData(pointsPolydata);
#endif
  vertexGlyphFilter->Update();

 vtkSmartPointer<vtkPolyDataMapper> pointsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointsMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> pointsActor =
    vtkSmartPointer<vtkActor>::New();
  pointsActor->SetMapper(pointsMapper);
  pointsActor->GetProperty()->SetPointSize(5);
  pointsActor->GetProperty()->SetColor(0.0,0.0,1);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(cubeActor);
  renderer->AddActor(pointsActor);
  renderer->SetBackground(.0, 1,.0);

  // Render and interact
  renderWindow->SetWindowName(argv[0]);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PointInsideObject)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PointInsideObject MACOSX_BUNDLE PointInsideObject.cxx)
 
target_link_libraries(PointInsideObject ${VTK_LIBRARIES})
```

**Download and Build PointInsideObject**

Click [here to download PointInsideObject](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PointInsideObject.tar) and its *CMakeLists.txt* file.
Once the *tarball PointInsideObject.tar* has been downloaded and extracted,
```
cd PointInsideObject/build 
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
./PointInsideObject
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

