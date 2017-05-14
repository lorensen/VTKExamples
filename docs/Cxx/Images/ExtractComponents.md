[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ExtractComponents

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestExtractComponents.png?raw=true" width="256" />

### Description
This example separates an image into the red channel, the green channel, and the blue channel using {{class|vtkImageExtractComponents}}.

For the reverse operation, see []([../CombiningRGBChannels]).

**ExtractComponents.cxx**
```c++
#include <vtkImageData.h>
#include <vtkJPEGReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>

int main(int argc, char *argv[])
{
  // Verify command line arguments
  if (argc != 2 )
  {
    std::cout << "Required parameters: InputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse command line arguments
  std::string inputFilename = argv[1];

  // Read JPG file
  vtkSmartPointer<vtkJPEGReader> reader =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();


  vtkSmartPointer<vtkImageExtractComponents> extractRedFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractRedFilter->SetInputConnection(reader->GetOutputPort());
  extractRedFilter->SetComponents(0);
  extractRedFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractGreenFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractGreenFilter->SetInputConnection(reader->GetOutputPort());
  extractGreenFilter->SetComponents(1);
  extractGreenFilter->Update();

  vtkSmartPointer<vtkImageExtractComponents> extractBlueFilter =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extractBlueFilter->SetInputConnection(reader->GetOutputPort());
  extractBlueFilter->SetComponents(2);
  extractBlueFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> redActor =
    vtkSmartPointer<vtkImageActor>::New();
  redActor->GetMapper()->SetInputConnection(extractRedFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> greenActor =
    vtkSmartPointer<vtkImageActor>::New();
  greenActor->GetMapper()->SetInputConnection(extractGreenFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> blueActor =
    vtkSmartPointer<vtkImageActor>::New();
  blueActor->GetMapper()->SetInputConnection(extractBlueFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double redViewport[4] = {0.25, 0.0, 0.5, 1.0};
  double greenViewport[4] = {0.5, 0.0, 0.75, 1.0};
  double blueViewport[4] = {0.75, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> inputRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inputRenderer->SetViewport(inputViewport);
  inputRenderer->AddActor(inputActor);
  inputRenderer->ResetCamera();
  inputRenderer->SetBackground(.4, .5, .9);

  vtkSmartPointer<vtkRenderer> redRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  redRenderer->SetViewport(redViewport);
  redRenderer->AddActor(redActor);
  redRenderer->ResetCamera();
  redRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> greenRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  greenRenderer->SetViewport(greenViewport);
  greenRenderer->AddActor(greenActor);
  greenRenderer->ResetCamera();
  greenRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderer> blueRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  blueRenderer->SetViewport(blueViewport);
  blueRenderer->AddActor(blueActor);
  blueRenderer->ResetCamera();
  blueRenderer->SetBackground(.4, .5, .8);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000, 250);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(redRenderer);
  renderWindow->AddRenderer(greenRenderer);
  renderWindow->AddRenderer(blueRenderer);

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
 
PROJECT(ExtractComponents)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractComponents MACOSX_BUNDLE ExtractComponents.cxx)
 
target_link_libraries(ExtractComponents ${VTK_LIBRARIES})
```

**Download and Build ExtractComponents**

Click [here to download ExtractComponents](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractComponents.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractComponents.tar* has been downloaded and extracted,
```
cd ExtractComponents/build 
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
./ExtractComponents
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

