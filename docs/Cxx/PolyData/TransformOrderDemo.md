[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/TransformOrderDemo

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestTransformOrderDemo.png?raw=true" width="256" />

### Description
This example creates an image. In the left viewport, it translates the image, then translates and rotates the image. In the right viewport, it rotates the image, then rotates and translates the image. One can see that the result is clearly not the same!

**TransformOrderDemo.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkAxesActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetInputConnection(source->GetOutputPort());
  castFilter->SetOutputScalarTypeToUnsignedChar();
  castFilter->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor1a =
    vtkSmartPointer<vtkImageActor>::New();
  actor1a->GetMapper()->SetInputConnection(castFilter->GetOutputPort());
  vtkSmartPointer<vtkImageActor> actor1b =
    vtkSmartPointer<vtkImageActor>::New();
  actor1b->GetMapper()->SetInputConnection(castFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> actor2a =
    vtkSmartPointer<vtkImageActor>::New();
  actor2a->GetMapper()->SetInputConnection(castFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> actor2b =
    vtkSmartPointer<vtkImageActor>::New();
  actor2b->GetMapper()->SetInputConnection(castFilter->GetOutputPort());
  
  // Create the transformation
  vtkSmartPointer<vtkTransform> transform1a =
    vtkSmartPointer<vtkTransform>::New();
  transform1a->PostMultiply();
  transform1a->Translate(10.0, 0.0, 0.0);
  actor1a->SetUserTransform(transform1a);

  vtkSmartPointer<vtkTransform> transform1b =
    vtkSmartPointer<vtkTransform>::New();
  transform1b->PostMultiply();
  transform1b->Translate(10.0, 0.0, 0.0);
  transform1b->RotateZ(40.0);
  actor1b->SetUserTransform(transform1b);
  
  vtkSmartPointer<vtkTransform> transform2a =
    vtkSmartPointer<vtkTransform>::New();
  transform2a->PostMultiply();
  transform2a->RotateZ(40.0);
  actor2a->SetUserTransform(transform2a);

  vtkSmartPointer<vtkTransform> transform2b =
    vtkSmartPointer<vtkTransform>::New();
  transform2b->PostMultiply();
  transform2b->RotateZ(40.0);
  transform2b->Translate(10.0, 0.0, 0.0);
  actor2b->SetUserTransform(transform2b);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Cetup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

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

  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
  axes->AxisLabelsOff();
  axes->SetTotalLength(5,5,5);
  
  leftRenderer->AddActor(axes);
  leftRenderer->AddActor(actor1a);
  leftRenderer->AddActor(actor1b);

  rightRenderer->AddActor(axes);
  rightRenderer->AddActor(actor2a);
  rightRenderer->AddActor(actor2b);

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
 
PROJECT(TransformOrderDemo)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TransformOrderDemo MACOSX_BUNDLE TransformOrderDemo.cxx)
 
target_link_libraries(TransformOrderDemo ${VTK_LIBRARIES})
```

**Download and Build TransformOrderDemo**

Click [here to download TransformOrderDemo](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TransformOrderDemo.tar) and its *CMakeLists.txt* file.
Once the *tarball TransformOrderDemo.tar* has been downloaded and extracted,
```
cd TransformOrderDemo/build 
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
./TransformOrderDemo
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

