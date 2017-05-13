[VTKExamples](Home)/[Cxx](Cxx)/ImageData/ImageReslice

**ImageReslice.cxx**
```c++
#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkImageData.h>
#include <vtkIntArray.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkImageReslice.h>
 
int main(int, char *[] )
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->SetExtent(0, 9, 0, 9, 0, 0);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(1);
  image->SetScalarTypeToInt();
#else
  image->AllocateScalars(VTK_INT,1);
#endif
  int* pixel = static_cast<int*>(image->GetScalarPointer(0,9,0));
  std::cout << "pixel: " << *pixel << std::endl;

  vtkSmartPointer<vtkImageReslice> reslice =
    vtkSmartPointer<vtkImageReslice>::New();
  reslice->SetOutputExtent(0, 9, 0, 100, 0, 0);
#if VTK_MAJOR_VERSION <= 5
  reslice->SetInputConnection(image->GetProducerPort());
#else
  reslice->SetInputData(image);
#endif
  reslice->Update();

  int* pixel2 = static_cast<int*>(reslice->GetOutput()->GetScalarPointer(0,11,0));
  std::cout << "pixel2: " << *pixel2 << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageReslice)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageReslice MACOSX_BUNDLE ImageReslice.cxx)
 
target_link_libraries(ImageReslice ${VTK_LIBRARIES})
```

**Download and Build ImageReslice**

Click [here to download ImageReslice](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageReslice.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageReslice.tar* has been downloaded and extracted,
```
cd ImageReslice/build 
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
./ImageReslice
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

