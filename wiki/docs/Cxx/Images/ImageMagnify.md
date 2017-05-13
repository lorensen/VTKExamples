[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageMagnify

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageMagnify.png?raw=true" width="256" />

### Description
vtkImageMagnify increases the dimensions of an image by integral magnification factors. It also adjusts the spacing of the pixels so that the magnified image covers the same region as the original image. To stretch the image, the pixel spacing needs to be adjusted. This example uses vtkImageChangeInformation to modify the magnified image's spacing. The result is an image that has increased numbers of pixels and is stretched in the magnified directions.

**ImageMagnify.cxx**
```c++
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageMagnify.h>
#include <vtkImageChangeInformation.h>

int main(int argc, char *argv[])
{
  // Handle the arguments
  if(argc < 2)
  {
    std::cout << "Required arguments: filename.png" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);

  // Increase the dimensions of the image
  vtkSmartPointer<vtkImageMagnify> magnifyFilter =
    vtkSmartPointer<vtkImageMagnify>::New();
  magnifyFilter->SetInputConnection(reader->GetOutputPort());
  magnifyFilter->SetMagnificationFactors(2,1,1);
  magnifyFilter->Update();

  // Adjust the spacing of the magnified image. This will stretch the
  // image
  vtkSmartPointer<vtkImageChangeInformation> changeFilter =
    vtkSmartPointer<vtkImageChangeInformation>::New();
  changeFilter->SetInputConnection(magnifyFilter->GetOutputPort());
  changeFilter->SetSpacingScale(
    magnifyFilter->GetMagnificationFactors()[0],
    magnifyFilter->GetMagnificationFactors()[1],
    magnifyFilter->GetMagnificationFactors()[2]);

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> magnifiedActor =
    vtkSmartPointer<vtkImageActor>::New();
  magnifiedActor->GetMapper()->SetInputConnection(
    changeFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double magnifiedViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> magnifiedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  magnifiedRenderer->SetViewport(magnifiedViewport);
  magnifiedRenderer->AddActor(magnifiedActor);
  magnifiedRenderer->ResetCamera();
  magnifiedRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(magnifiedRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return  EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageMagnify)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageMagnify MACOSX_BUNDLE ImageMagnify.cxx)
 
target_link_libraries(ImageMagnify ${VTK_LIBRARIES})
```

**Download and Build ImageMagnify**

Click [here to download ImageMagnify](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageMagnify.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageMagnify.tar* has been downloaded and extracted,
```
cd ImageMagnify/build 
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
./ImageMagnify
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

