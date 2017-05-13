[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageCityBlockDistance

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageCityBlockDistance.png?raw=true" width="256" />

### Description
Compute the Manhattan distance from every point to every black point in a binary image.

**ImageCityBlockDistance.cxx**
```c++
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCast.h>
#include <vtkImageThreshold.h>
#include <vtkJPEGReader.h>
#include <vtkPNGReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageExtractComponents.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkImageCityBlockDistance.h>

int main(int argc, char *argv[])
{
  // Verify command line arguments
  if (argc < 2 )
  {
    std::cout << "Usage: " << argv[0] << " BinaryImage.jpg" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse command line arguments
  std::string inputFilename = argv[1];

  // Read file
  vtkSmartPointer<vtkJPEGReader> reader =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetOutputScalarTypeToShort();
  castFilter->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageCityBlockDistance> cityBlockDistanceFilter =
    vtkSmartPointer<vtkImageCityBlockDistance>::New();
  cityBlockDistanceFilter->SetInputConnection(castFilter->GetOutputPort());
  cityBlockDistanceFilter->SetDimensionality(2);
  cityBlockDistanceFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageCast> inputCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  inputCastFilter->SetOutputScalarTypeToUnsignedChar();
  inputCastFilter->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(inputCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageCast> distanceCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  distanceCastFilter->SetOutputScalarTypeToUnsignedChar();
  distanceCastFilter->SetInputConnection(cityBlockDistanceFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> distanceActor =
    vtkSmartPointer<vtkImageActor>::New();
  distanceActor->GetMapper()->SetInputConnection(
    distanceCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double inputViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double distanceViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> inputRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  inputRenderer->SetViewport(inputViewport);
  inputRenderer->AddActor(inputActor);
  inputRenderer->ResetCamera();
  inputRenderer->SetBackground(.4, .5, .9);

  vtkSmartPointer<vtkRenderer> distanceRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  distanceRenderer->SetViewport(distanceViewport);
  distanceRenderer->AddActor(distanceActor);
  distanceRenderer->ResetCamera();
  distanceRenderer->SetBackground(.4, .5, .7);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(inputRenderer);
  renderWindow->AddRenderer(distanceRenderer);

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
 
PROJECT(ImageCityBlockDistance)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageCityBlockDistance MACOSX_BUNDLE ImageCityBlockDistance.cxx)
 
target_link_libraries(ImageCityBlockDistance ${VTK_LIBRARIES})
```

**Download and Build ImageCityBlockDistance**

Click [here to download ImageCityBlockDistance](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageCityBlockDistance.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageCityBlockDistance.tar* has been downloaded and extracted,
```
cd ImageCityBlockDistance/build 
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
./ImageCityBlockDistance
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

