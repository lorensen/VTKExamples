[VTKExamples](/home/)/[Cxx](/Cxx)/Images/Colored2DImageFusion

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestColored2DImageFusion.png?raw=true" width="256" />

### Description
This example use the vtkImageBlend class for a simple fusion of two 2D images with different color maps for each of the images.

* Contributed by: Tim Hutz

**Colored2DImageFusion.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkImageBlend.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkJPEGReader.h>
#include <vtkLookupTable.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[])
{
  // Parse input arguments
  if ( argc != 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkLookupTable> imgFirstColorMap =
    vtkSmartPointer<vtkLookupTable>::New(); // hot color map
  imgFirstColorMap->SetRange( 0.0, 255.0 );
  imgFirstColorMap->SetHueRange( 0.0, 0.1 );
  imgFirstColorMap->SetValueRange( 0.4, 0.8 );
  imgFirstColorMap->Build();

  vtkSmartPointer<vtkLookupTable> imgSecondColorMap =
      vtkSmartPointer<vtkLookupTable>::New(); // cold color map
  imgSecondColorMap->SetRange( 0.0, 255.0 );
  imgSecondColorMap->SetHueRange( 0.67, 0.68 );
  imgSecondColorMap->SetValueRange( 0.4, 0.8 );
  imgSecondColorMap->Build();

  vtkSmartPointer<vtkJPEGReader> imgReader =
      vtkSmartPointer<vtkJPEGReader>::New();
  imgReader->SetFileName( argv[1] );

  vtkSmartPointer<vtkJPEGReader> imgReaderMoving =
      vtkSmartPointer<vtkJPEGReader>::New();
  imgReaderMoving->SetFileName( argv[2] );

  vtkSmartPointer<vtkImageMapToColors> firstColorMapper =
      vtkSmartPointer<vtkImageMapToColors>::New();
  firstColorMapper->SetInputConnection( imgReader->GetOutputPort() );
  firstColorMapper->SetLookupTable( imgFirstColorMap );

  vtkSmartPointer<vtkImageMapToColors> secondColorMapper =
      vtkSmartPointer<vtkImageMapToColors>::New();
  secondColorMapper->SetInputConnection( imgReaderMoving->GetOutputPort() );
  secondColorMapper->SetLookupTable( imgSecondColorMap );

  vtkSmartPointer<vtkImageBlend> imgBlender =
      vtkSmartPointer<vtkImageBlend>::New();
  imgBlender->SetOpacity( 0, 0.5 );
  imgBlender->SetOpacity( 1, 0.5 );
  imgBlender->AddInputConnection( firstColorMapper->GetOutputPort() );
  imgBlender->AddInputConnection( secondColorMapper->GetOutputPort() );

  vtkSmartPointer<vtkDataSetMapper> imgDataSetMapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
  imgDataSetMapper->SetInputConnection(imgBlender->GetOutputPort());

  vtkSmartPointer<vtkActor> imgActor =
      vtkSmartPointer<vtkActor>::New();
  imgActor->SetMapper( imgDataSetMapper );

  vtkSmartPointer<vtkRenderer> imgRenderer =
      vtkSmartPointer<vtkRenderer>::New();
  imgRenderer->AddActor( imgActor );

  vtkSmartPointer<vtkRenderWindow> imgRenderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  imgRenderWindow->AddRenderer( imgRenderer );

  vtkSmartPointer<vtkRenderWindowInteractor> imgInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imgInteractor->SetRenderWindow( imgRenderWindow );
  imgInteractor->Initialize();
  imgInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Colored2DImageFusion)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Colored2DImageFusion MACOSX_BUNDLE Colored2DImageFusion.cxx)
 
target_link_libraries(Colored2DImageFusion ${VTK_LIBRARIES})
```

**Download and Build Colored2DImageFusion**

Click [here to download Colored2DImageFusion](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Colored2DImageFusion.tar) and its *CMakeLists.txt* file.
Once the *tarball Colored2DImageFusion.tar* has been downloaded and extracted,
```
cd Colored2DImageFusion/build 
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
./Colored2DImageFusion
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

