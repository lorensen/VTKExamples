[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageText

### Description
This example demonstrates how to draw text onto an image ({{class|vtkImageData}}). It uses {{class|vtkImageBlend}} to blend the text and the image. For another example using vtkImageBlend, see []([../CombineImages]).

See also []([../../Visualization/DrawText]) for an example of drawing text, also in 2D, but into the render window rather than into a vtkImageData object.

**ImageText.cxx**
```c++
#include <vtkImageBlend.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkPNGWriter.h>
#include <vtkSmartPointer.h>
#include <vtkFreeTypeUtilities.h>
#include <vtkTextProperty.h>
#include <vtkImageCanvasSource2D.h>

// must build VTK with VTK_USE_SYSTEM_FREETYPE=ON

int main(int argc, char* argv[])
{
  // Create a black image with a red circle of radius 50 centered at (60, 60)
  vtkSmartPointer<vtkImageCanvasSource2D> drawing =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar(); // PNGWriter requires unsigned char (or unsigned short)
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 150, 0, 120, 0, 0); // xmin, xmax, ymin, ymax, zmin, zmax
  drawing->SetDrawColor(255, 0, 0); // red
  drawing->DrawCircle(60, 60, 50); // parameters: x, y, radius

  // Create an image of text
  vtkSmartPointer<vtkFreeTypeUtilities> freeType = vtkSmartPointer<vtkFreeTypeUtilities>::New();
  vtkSmartPointer<vtkTextProperty> textProperty = vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetColor(1.0, 1.0, 0.0); // yellow
  textProperty->SetFontSize(24);
  vtkSmartPointer<vtkImageData> textImage = vtkSmartPointer<vtkImageData>::New();
  freeType->RenderString(textProperty, "Test String", textImage);

  // Combine the images
  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(drawing->GetOutputPort());
  blend->AddInputData(textImage);
  blend->SetOpacity(0, 0.5); // background image: 50% opaque
  blend->SetOpacity(1, 1.0); // text: 100% opaque
  blend->Update();

  vtkSmartPointer<vtkPNGWriter> writer =
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName("output.png");
  writer->SetInputConnection(blend->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageText)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageText MACOSX_BUNDLE ImageText.cxx)
 
target_link_libraries(ImageText ${VTK_LIBRARIES})
```

**Download and Build ImageText**

Click [here to download ImageText](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageText.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageText.tar* has been downloaded and extracted,
```
cd ImageText/build 
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
./ImageText
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

