[VTKExamples](/home/)/[Cxx](/Cxx)/Filtering/LandmarkTransform

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Filtering/TestLandmarkTransform.png?raw=true" width="256" />

### Description
 
This example creates two point sets which it assumes are known, ordered correspondences. It then transforms Source to Target and displays the matrix used in the transformation.

**LandmarkTransform.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkLandmarkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  /*
  This demo creates a coordinate frame (+x, +y, +z) of vectors and a rotated,
  peturbed frame (+z, +y, -x) and aligns the rotated frame to the original as best as possible.
  */
  
  vtkSmartPointer<vtkPoints> sourcePoints =
    vtkSmartPointer<vtkPoints>::New();
  double sourcePoint1[3] = {1.0, 0.0, 0.0};
  sourcePoints->InsertNextPoint(sourcePoint1);
  double sourcePoint2[3] = {0.0, 1.0, 0.0};
  sourcePoints->InsertNextPoint(sourcePoint2);
  double sourcePoint3[3] = {0.0, 0.0, 1.0};
  sourcePoints->InsertNextPoint(sourcePoint3);
  
  vtkSmartPointer<vtkPoints> targetPoints =
    vtkSmartPointer<vtkPoints>::New();
  double targetPoint1[3] = {0.0, 0.0, 1.1};
  targetPoints->InsertNextPoint(targetPoint1);
  double targetPoint2[3] = {0.0, 1.02, 0.0};
  targetPoints->InsertNextPoint(targetPoint2);
  double targetPoint3[3] = {-1.11, 0.0, 0.0};
  targetPoints->InsertNextPoint(targetPoint3);
  
  // Setup the transform
  vtkSmartPointer<vtkLandmarkTransform> landmarkTransform = 
    vtkSmartPointer<vtkLandmarkTransform>::New();
  landmarkTransform->SetSourceLandmarks(sourcePoints);
  landmarkTransform->SetTargetLandmarks(targetPoints);
  landmarkTransform->SetModeToRigidBody();
  landmarkTransform->Update(); //should this be here?

  vtkSmartPointer<vtkPolyData> source =
    vtkSmartPointer<vtkPolyData>::New();
  source->SetPoints(sourcePoints);
  
  vtkSmartPointer<vtkPolyData> target =
    vtkSmartPointer<vtkPolyData>::New();
  target->SetPoints(targetPoints);
  
  vtkSmartPointer<vtkVertexGlyphFilter> sourceGlyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  sourceGlyphFilter->SetInputConnection(source->GetProducerPort());
#else
  sourceGlyphFilter->SetInputData(source);
#endif
  sourceGlyphFilter->Update();
  
  vtkSmartPointer<vtkVertexGlyphFilter> targetGlyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  targetGlyphFilter->SetInputConnection(target->GetProducerPort());
#else
  targetGlyphFilter->SetInputData(target);
#endif
  targetGlyphFilter->Update();
    
  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection(sourceGlyphFilter->GetOutputPort());
  transformFilter->SetTransform(landmarkTransform);
  transformFilter->Update();
    
  // Display the transformation matrix that was computed
  vtkMatrix4x4* mat = landmarkTransform->GetMatrix();
  std::cout << "Matrix: " << *mat << std::endl;

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> sourceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sourceMapper->SetInputConnection(sourceGlyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> sourceActor =
    vtkSmartPointer<vtkActor>::New();
  sourceActor->SetMapper(sourceMapper);
  sourceActor->GetProperty()->SetColor(0,1,0);
  sourceActor->GetProperty()->SetPointSize(4);

  vtkSmartPointer<vtkPolyDataMapper> targetMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  targetMapper->SetInputConnection(targetGlyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> targetActor =
    vtkSmartPointer<vtkActor>::New();
  targetActor->SetMapper(targetMapper);
  targetActor->GetProperty()->SetColor(1,0,0);
  targetActor->GetProperty()->SetPointSize(4);
  
  vtkSmartPointer<vtkPolyDataMapper> solutionMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  solutionMapper->SetInputConnection(transformFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> solutionActor =
    vtkSmartPointer<vtkActor>::New();
  solutionActor->SetMapper(solutionMapper);
  solutionActor->GetProperty()->SetColor(0,0,1);
  solutionActor->GetProperty()->SetPointSize(3);
  
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(sourceActor);
  renderer->AddActor(targetActor);
  renderer->AddActor(solutionActor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LandmarkTransform)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LandmarkTransform MACOSX_BUNDLE LandmarkTransform.cxx)
 
target_link_libraries(LandmarkTransform ${VTK_LIBRARIES})
```

**Download and Build LandmarkTransform**

Click [here to download LandmarkTransform](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LandmarkTransform.tar) and its *CMakeLists.txt* file.
Once the *tarball LandmarkTransform.tar* has been downloaded and extracted,
```
cd LandmarkTransform/build 
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
./LandmarkTransform
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

