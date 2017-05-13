[VTKExamples](Home)/[Cxx](Cxx)/Images/DrawOnAnImage

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Images/TestDrawOnAnImage.png" width="256" />

### Description
This example draws a circle in the center of the input image using {{class|vtkImageCanvasSource2D}}'s <code>DrawCircle</code> method.

**DrawOnAnImage.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageViewer2.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageBlend.h>

int main ( int argc, char* argv[] )
{
  //Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " InputFilename(jpg)" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse input arguments
  std::string inputFilename = argv[1];

  // Read the image
  vtkSmartPointer<vtkJPEGReader> jPEGReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( inputFilename.c_str() );
  jPEGReader->Update();

  vtkImageData* image = jPEGReader->GetOutput();

  // Find center of image
  int center[2];
  center[0] = (image->GetExtent()[1] + image->GetExtent()[0]) / 2;
  center[1] = (image->GetExtent()[3] + image->GetExtent()[2]) / 2;

  // Pick a radius for the circle
  int radius;
  radius = (image->GetExtent()[1] < image->GetExtent()[3]) ?
    image->GetExtent()[1] * 2 / 5 : image->GetExtent()[3] * 2 / 5;

  // Draw a circle in the center of the image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetExtent(image->GetExtent());
  drawing->SetDrawColor(0.0, 0.0, 0.0);
  drawing->FillBox(image->GetExtent()[0], image->GetExtent()[1],
    image->GetExtent()[2], image->GetExtent()[3]);
  drawing->SetDrawColor(255.0, 255.0, 255.0);
  drawing->DrawCircle(center[0], center[1], radius);

  // Combine the images (blend takes multiple connections on the 0th
  // input port)
  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(jPEGReader->GetOutputPort());
  blend->AddInputConnection(drawing->GetOutputPort());
  blend->SetOpacity(0,.6);
  blend->SetOpacity(1,.4);

  // Display the result
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(blend->GetOutputPort());
  imageViewer->SetSize(640, 512);
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(1,0,0); //red

  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DrawOnAnImage)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DrawOnAnImage MACOSX_BUNDLE DrawOnAnImage.cxx)
 
target_link_libraries(DrawOnAnImage ${VTK_LIBRARIES})
```

**Download and Build DrawOnAnImage**

Click [here to download DrawOnAnImage](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DrawOnAnImage.tar) and its *CMakeLists.txt* file.
Once the *tarball DrawOnAnImage.tar* has been downloaded and extracted,
```
cd DrawOnAnImage/build 
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
./DrawOnAnImage
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

