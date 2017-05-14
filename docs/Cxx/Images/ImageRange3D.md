[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageRange3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageRange3D.png?raw=true" width="256" />

**ImageRange3D.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageRange3D.h>
#include <vtkImageCast.h>

int main(int argc, char* argv[])
{
  // Parse input arguments
  if ( argc != 2 )
  {
    std::cout << "Required parameters: Filename.jpg" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read the image
  vtkSmartPointer<vtkJPEGReader> reader =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageRange3D> rangeFilter =
    vtkSmartPointer<vtkImageRange3D>::New();
  rangeFilter->SetInputConnection(reader->GetOutputPort());
  rangeFilter->SetKernelSize(5,5,5);
  rangeFilter->Update();


  vtkSmartPointer<vtkImageCast> rangeCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  rangeCastFilter->SetInputConnection(rangeFilter->GetOutputPort());
  rangeCastFilter->SetOutputScalarTypeToUnsignedChar();
  rangeCastFilter->Update();

  vtkSmartPointer<vtkImageActor> rangeActor =
    vtkSmartPointer<vtkImageActor>::New();
  rangeActor->GetMapper()->SetInputConnection(
    rangeCastFilter->GetOutputPort());

   // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rangeViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> rangeRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rangeRenderer->SetViewport(rangeViewport);
  rangeRenderer->AddActor(rangeActor);
  rangeRenderer->ResetCamera();
  rangeRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(rangeRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageRange3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageRange3D MACOSX_BUNDLE ImageRange3D.cxx)
 
target_link_libraries(ImageRange3D ${VTK_LIBRARIES})
```

**Download and Build ImageRange3D**

Click [here to download ImageRange3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageRange3D.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageRange3D.tar* has been downloaded and extracted,
```
cd ImageRange3D/build 
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
./ImageRange3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

