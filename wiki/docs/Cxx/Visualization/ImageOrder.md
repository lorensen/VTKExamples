[VTKExamples](Home)/[Cxx](Cxx)/Visualization/ImageOrder

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Visualization/TestImageOrder.png" width="256" />

**ImageOrder.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

static void CreateWhiteImage(vtkSmartPointer<vtkImageData> image);
static void CreateRedImage(vtkSmartPointer<vtkImageData> image);

int main(int, char* [])
{
  // Image 1
  vtkSmartPointer<vtkImageData> whiteImage =
    vtkSmartPointer<vtkImageData>::New();
  CreateWhiteImage(whiteImage);

  vtkSmartPointer<vtkImageActor> whiteImageActor =
    vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  whiteImageActor->SetInput(whiteImage);
#else
  whiteImageActor->SetInputData(whiteImage);
#endif

  // Image 2
  vtkSmartPointer<vtkImageData> redImage =
    vtkSmartPointer<vtkImageData>::New();
  CreateRedImage(redImage);

  vtkSmartPointer<vtkImageActor> redImageActor =
    vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  redImageActor->SetInput(redImage);
#else
  redImageActor->SetInputData(redImage);
#endif

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  // Red image is displayed
  renderer->AddActor(whiteImageActor);
  renderer->AddActor(redImageActor);

  // White image is displayed
  //renderer->AddActor(redImageActor);
  //renderer->AddActor(whiteImageActor);

  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

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

void CreateWhiteImage(vtkSmartPointer<vtkImageData> image)
{
  // Create a white image
  image->SetDimensions(10,10,1);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);
#endif

  int* dims = image->GetDimensions();

  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 255;
      pixel[1] = 255;
      pixel[2] = 255;
    }
  }
}

void CreateRedImage(vtkSmartPointer<vtkImageData> image)
{
  // Create a red image
  image->SetDimensions(10,10,1);

#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(3);
  image->SetScalarTypeToUnsignedChar();
  image->AllocateScalars();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,3);
#endif
  int* dims = image->GetDimensions();

  for (int y = 0; y < dims[1]; y++)
  {
    for (int x = 0; x < dims[0]; x++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x,y,0));
      pixel[0] = 255;
      pixel[1] = 0;
      pixel[2] = 0;
    }
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageOrder)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageOrder MACOSX_BUNDLE ImageOrder.cxx)
 
target_link_libraries(ImageOrder ${VTK_LIBRARIES})
```

**Download and Build ImageOrder**

Click [here to download ImageOrder](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageOrder.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageOrder.tar* has been downloaded and extracted,
```
cd ImageOrder/build 
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
./ImageOrder
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

