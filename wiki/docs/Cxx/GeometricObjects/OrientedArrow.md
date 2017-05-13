[VTKExamples](/home/)/[Cxx](/Cxx)/GeometricObjects/OrientedArrow

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/GeometricObjects/TestOrientedArrow.png?raw=true" width="256" />

### Description
This example illustrates how to create and display an arrow that passes through two points.

It demonstrates two different ways to apply the transform:
1. Use [vtkTransformPolyDataFilter](http://www.vtk.org/doc/nightly/html/classvtkTransformPolyDataFilter.html) to create a new transformed polydata. This method is useful if the transformed polydata is needed later in the pipeline, e.g. vtkGlyph3DFilter.
2. Apply the transform directly to the actor using [vtkProp3D's SetUserMatrix](http://www.vtk.org/doc/nightly/html/classvtkProp3D.html#a950378fc70405a58bd998c00f84a39a3). No new data is produced.

Switch between the two methods by #defining USER_MATRIX or leaving out the #define.

NOTE:  Compare this example with [Oriented Cylinder](Cxx/GeometricObjects/OrientedCylinder) . The transform is different because the cylinder height direction is along the y-axis and the arrow height is along the x axis.
 

**OrientedArrow.cxx**
```c++
#define USER_MATRIX
#include <vtkArrowSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <time.h>

int main(int, char *[])
{
  //Create an arrow.
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();

  // Generate a random start and end point
  double startPoint[3], endPoint[3];
#ifndef main
  vtkMath::RandomSeed(time(NULL));
#else
  vtkMath::RandomSeed(8775070);
#endif
  startPoint[0] = vtkMath::Random(-10,10);
  startPoint[1] = vtkMath::Random(-10,10);
  startPoint[2] = vtkMath::Random(-10,10);
  endPoint[0] = vtkMath::Random(-10,10);
  endPoint[1] = vtkMath::Random(-10,10);
  endPoint[2] = vtkMath::Random(-10,10);

  // Compute a basis
  double normalizedX[3];
  double normalizedY[3];
  double normalizedZ[3];

  // The X axis is a vector from start to end
  vtkMath::Subtract(endPoint, startPoint, normalizedX);
  double length = vtkMath::Norm(normalizedX);
  vtkMath::Normalize(normalizedX);

  // The Z axis is an arbitrary vector cross X
  double arbitrary[3];
  arbitrary[0] = vtkMath::Random(-10,10);
  arbitrary[1] = vtkMath::Random(-10,10);
  arbitrary[2] = vtkMath::Random(-10,10);
  vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
  vtkMath::Normalize(normalizedZ);

  // The Y axis is Z cross X
  vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();

  // Create the direction cosine matrix
  matrix->Identity();
  for (unsigned int i = 0; i < 3; i++)
  {
    matrix->SetElement(i, 0, normalizedX[i]);
    matrix->SetElement(i, 1, normalizedY[i]);
    matrix->SetElement(i, 2, normalizedZ[i]);
  }

  // Apply the transforms
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(startPoint);
  transform->Concatenate(matrix);
  transform->Scale(length, length, length);

  // Transform the polydata
  vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformPD->SetTransform(transform);
  transformPD->SetInputConnection(arrowSource->GetOutputPort());

  //Create a mapper and actor for the arrow
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
#ifdef USER_MATRIX
  mapper->SetInputConnection(arrowSource->GetOutputPort());
  actor->SetUserMatrix(transform->GetMatrix());
#else
  mapper->SetInputConnection(transformPD->GetOutputPort());
#endif
  actor->SetMapper(mapper);

  // Create spheres for start and end point
  vtkSmartPointer<vtkSphereSource> sphereStartSource =
    vtkSmartPointer<vtkSphereSource>::New();
    sphereStartSource->SetCenter(startPoint);
  vtkSmartPointer<vtkPolyDataMapper> sphereStartMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereStartMapper->SetInputConnection(sphereStartSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereStart =
    vtkSmartPointer<vtkActor>::New();
  sphereStart->SetMapper(sphereStartMapper);
  sphereStart->GetProperty()->SetColor(1.0, 1.0, .3);

  vtkSmartPointer<vtkSphereSource> sphereEndSource =
    vtkSmartPointer<vtkSphereSource>::New();
    sphereEndSource->SetCenter(endPoint);
  vtkSmartPointer<vtkPolyDataMapper> sphereEndMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereEndMapper->SetInputConnection(sphereEndSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereEnd =
    vtkSmartPointer<vtkActor>::New();
  sphereEnd->SetMapper(sphereEndMapper);
  sphereEnd->GetProperty()->SetColor(1.0, .3, .3);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(sphereStart);
  renderer->AddActor(sphereEnd);
  renderer->SetBackground(.1, .2, .3); // Background color dark blue


  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OrientedArrow)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OrientedArrow MACOSX_BUNDLE OrientedArrow.cxx)
 
target_link_libraries(OrientedArrow ${VTK_LIBRARIES})
```

**Download and Build OrientedArrow**

Click [here to download OrientedArrow](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OrientedArrow.tar) and its *CMakeLists.txt* file.
Once the *tarball OrientedArrow.tar* has been downloaded and extracted,
```
cd OrientedArrow/build 
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
./OrientedArrow
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

