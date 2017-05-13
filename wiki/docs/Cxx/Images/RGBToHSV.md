[VTKExamples](/home/)/[Cxx](/Cxx)/Images/RGBToHSV

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestRGBToHSV.png?raw=true" width="256" />

### Description
Convert RGB channels to HSV channels.

**RGBToHSV.cxx**
```c++
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkSmartPointer.h>
#include <vtkImageRGBToHSV.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkImageExtractComponents.h>

#include <string>

int main(int argc, char *argv[])
{
  // Verify command line arguments
  if(argc != 2)
  {
    std::cerr << "Required arguments: image" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  std::cout << "Reading file: " << inputFilename << std::endl;

  // Read JPG file
  vtkSmartPointer<vtkJPEGReader> reader =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkSmartPointer<vtkImageRGBToHSV> hsvFilter =
    vtkSmartPointer<vtkImageRGBToHSV>::New();
  hsvFilter->SetInputConnection(reader->GetOutputPort());
  hsvFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractHueFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractHueFilter->SetInputConnection(hsvFilter->GetOutputPort());
  extractHueFilter->SetComponents(0);
  extractHueFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractSaturationFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractSaturationFilter->SetInputConnection(hsvFilter->GetOutputPort());
  extractSaturationFilter->SetComponents(1);
  extractSaturationFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractValueFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractValueFilter->SetInputConnection(hsvFilter->GetOutputPort());
  extractValueFilter->SetComponents(2);
  extractValueFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> hActor =
    vtkSmartPointer<vtkImageActor>::New();
  hActor->GetMapper()->SetInputConnection(
    extractHueFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> sActor =
    vtkSmartPointer<vtkImageActor>::New();
  sActor->GetMapper()->SetInputConnection(
    extractSaturationFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> vActor =
    vtkSmartPointer<vtkImageActor>::New();
  vActor->GetMapper()->SetInputConnection(
    extractValueFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double hViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double sViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double vViewport[4] = {0.75, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> inputRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inputRenderer->SetViewport(inputViewport);
  inputRenderer->AddActor(inputActor);
  inputRenderer->ResetCamera();
  inputRenderer->SetBackground(.4, .5, .9);

  vtkSmartPointer<vtkRenderer> hRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  hRenderer->SetViewport(hViewport);
  hRenderer->AddActor(hActor);
  hRenderer->ResetCamera();
  hRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> sRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  sRenderer->SetViewport(sViewport);
  sRenderer->AddActor(sActor);
  sRenderer->ResetCamera();
  sRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> vRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vRenderer->SetViewport(vViewport);
  vRenderer->AddActor(vActor);
  vRenderer->ResetCamera();
  vRenderer->SetBackground(.4, .5, .8);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(hRenderer);
  renderWindow->AddRenderer(sRenderer);
  renderWindow->AddRenderer(vRenderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RGBToHSV)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RGBToHSV MACOSX_BUNDLE RGBToHSV.cxx)
 
target_link_libraries(RGBToHSV ${VTK_LIBRARIES})
```

**Download and Build RGBToHSV**

Click [here to download RGBToHSV](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RGBToHSV.tar) and its *CMakeLists.txt* file.
Once the *tarball RGBToHSV.tar* has been downloaded and extracted,
```
cd RGBToHSV/build 
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
./RGBToHSV
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

