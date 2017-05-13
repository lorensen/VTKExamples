[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageImport

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageImport.png?raw=true" width="256" />

**ImageImport.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkXMLImageDataWriter.h>

int main(int, char *[])
{
  // Create a c-style image
  const int width = 4;
  const int height = 4;

  unsigned char cImage[width*height];
  unsigned char value = 0;
  for(unsigned int row = 0; row < height; ++row)
  {
    for(unsigned int col = 0; col < width; ++col)
    {
      cImage[row * width + col] = value;
      value += 10;
    }
  }

  // Convert the c-style image to a vtkImageData
  vtkSmartPointer<vtkImageImport> imageImport =
    vtkSmartPointer<vtkImageImport>::New();
  imageImport->SetDataSpacing(1, 1, 1);
  imageImport->SetDataOrigin(0, 0, 0);
  imageImport->SetWholeExtent(0, width-1, 0, height-1, 0, 0);
  imageImport->SetDataExtentToWholeExtent();
  imageImport->SetDataScalarTypeToUnsignedChar();
  imageImport->SetNumberOfScalarComponents(1);
  imageImport->SetImportVoidPointer(cImage);
  imageImport->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  actor->SetInput(imageImport->GetOutput());
#else
  actor->SetInputData(imageImport->GetOutput());
#endif

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

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
 
PROJECT(ImageImport)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageImport MACOSX_BUNDLE ImageImport.cxx)
 
target_link_libraries(ImageImport ${VTK_LIBRARIES})
```

**Download and Build ImageImport**

Click [here to download ImageImport](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageImport.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageImport.tar* has been downloaded and extracted,
```
cd ImageImport/build 
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
./ImageImport
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

