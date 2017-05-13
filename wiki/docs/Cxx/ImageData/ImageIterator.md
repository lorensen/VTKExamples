[VTKExamples](/home/)/[Cxx](/Cxx)/ImageData/ImageIterator

### Description
Extracts an extent from an image using an image iterator.

**ImageIterator.cxx**
```c++
#include <vtkVersion.h>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageIterator.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
      vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetDimensions(10,20,30);
#if VTK_MAJOR_VERSION <= 5
  imageData->SetNumberOfScalarComponents(3);
  imageData->SetScalarTypeToDouble();
  imageData->AllocateScalars();
#else
  imageData->AllocateScalars(VTK_DOUBLE,3);
#endif

  // Fill every entry of the image data with x,y,z
  int* dims = imageData->GetDimensions();
  double *ptr = static_cast<double *>(imageData->GetScalarPointer(0, 0, 0));
  for (int z=0; z<dims[2]; z++)
  {
    for (int y=0; y<dims[1]; y++)
    {
      for (int x=0; x<dims[0]; x++)
      {
        *ptr++ = z;
        *ptr++ = y;
        *ptr++ = x;
      }
    }
  }

  // Define the extent to be extracted
  int extent[6];
  extent[0] = 2; extent[1] = 5;
  extent[2] = 2; extent[3] = 5;
  extent[4] = 15; extent[5] = 15;

  // Retrieve the entries from the image data and print them to the screen
  vtkImageIterator<double> it(imageData, extent);
  while(!it.IsAtEnd())
  {
    double* valIt = it.BeginSpan();
    double *valEnd = it.EndSpan();
    while (valIt != valEnd)
    {
      // Increment for each component
      double x = *valIt++;
      double y = *valIt++;
      double z = *valIt++;
      std::cout << "("
                << x << ","
                << y << ","
                << z << ") ";
    }
    std::cout << std::endl;
    it.NextSpan();
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageIterator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageIterator MACOSX_BUNDLE ImageIterator.cxx)
 
target_link_libraries(ImageIterator ${VTK_LIBRARIES})
```

**Download and Build ImageIterator**

Click [here to download ImageIterator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageIterator.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageIterator.tar* has been downloaded and extracted,
```
cd ImageIterator/build 
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
./ImageIterator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

