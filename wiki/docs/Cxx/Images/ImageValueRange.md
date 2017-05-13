[VTKExamples](Home)/[Cxx](Cxx)/Images/ImageValueRange

**ImageValueRange.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(5,1,1);
#if VTK_MAJOR_VERSION <= 5
  imageData->SetNumberOfScalarComponents(1);
  imageData->SetScalarTypeToDouble();
  imageData->AllocateScalars();
#else
  imageData->AllocateScalars(VTK_DOUBLE,1);
#endif
  int* dims = imageData->GetDimensions();

  for (int x = 0; x < dims[0]; x++)
  {
    double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,0,0));
    pixel[0] = x*10;
  }

  double valuesRange[2];
  vtkDoubleArray::SafeDownCast(imageData->GetPointData()->GetArray("ImageScalars"))->GetValueRange(valuesRange);
  std::cout << "valuesRange = " << valuesRange[0] << " " << valuesRange[1] << std::endl;

  // This should also work:
  // min = vtkImageData->GetOutput()->GetScalarRange()[0] and max = GetScalarRange()[1].
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageValueRange)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageValueRange MACOSX_BUNDLE ImageValueRange.cxx)
 
target_link_libraries(ImageValueRange ${VTK_LIBRARIES})
```

**Download and Build ImageValueRange**

Click [here to download ImageValueRange](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageValueRange.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageValueRange.tar* has been downloaded and extracted,
```
cd ImageValueRange/build 
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
./ImageValueRange
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

