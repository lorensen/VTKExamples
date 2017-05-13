[VTKExamples](/home/)/[Cxx](/Cxx)/VolumeRendering/MinIntensityRendering

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/VolumeRendering/TestMinIntensityRendering.png?raw=true" width="256" />

**MinIntensityRendering.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkFiniteDifferenceGradientEstimator.h>
#include <vtkImageClip.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    std::cerr << "Required arguments: vtkFile" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1]; //  "/Data/ironProt.vtk";

  // Create the renderers, render window, and interactor
  vtkSmartPointer<vtkRenderWindow> renWin = 
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  renWin->AddRenderer(ren);
   
  // Read the data from a vtk file
  vtkSmartPointer<vtkStructuredPointsReader> reader = 
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();
 
  // Create a transfer function mapping scalar value to opacity
  vtkSmartPointer<vtkPiecewiseFunction> oTFun = 
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  oTFun->AddSegment(0, 1.0, 256, 0.1);
 
  vtkSmartPointer<vtkColorTransferFunction> cTFun = 
    vtkSmartPointer<vtkColorTransferFunction>::New();
  cTFun->AddRGBPoint(   0, 1.0, 1.0, 1.0 );
  cTFun->AddRGBPoint( 255, 1.0, 1.0, 1.0 );
 
  // Need to crop to actually see minimum intensity
  vtkSmartPointer<vtkImageClip> clip = 
    vtkSmartPointer<vtkImageClip>::New();
  clip->SetInputConnection( reader->GetOutputPort() );
  clip->SetOutputWholeExtent(0,66,0,66,30,37);
  clip->ClipDataOn();
 
  vtkSmartPointer<vtkVolumeProperty> property = 
    vtkSmartPointer<vtkVolumeProperty>::New();
  property->SetScalarOpacity(oTFun);
  property->SetColor(cTFun);
  property->SetInterpolationTypeToLinear();
 
  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> mapper = 
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  mapper->SetBlendModeToMinimumIntensity();
  mapper->SetInputConnection( clip->GetOutputPort() );
 
  vtkSmartPointer<vtkVolume> volume = 
    vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(mapper);
  volume->SetProperty(property);
 
  ren->AddViewProp(volume);
  renWin->Render();
  iren->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MinIntensityRendering)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MinIntensityRendering MACOSX_BUNDLE MinIntensityRendering.cxx)
 
target_link_libraries(MinIntensityRendering ${VTK_LIBRARIES})
```

**Download and Build MinIntensityRendering**

Click [here to download MinIntensityRendering](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MinIntensityRendering.tar) and its *CMakeLists.txt* file.
Once the *tarball MinIntensityRendering.tar* has been downloaded and extracted,
```
cd MinIntensityRendering/build 
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
./MinIntensityRendering
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

