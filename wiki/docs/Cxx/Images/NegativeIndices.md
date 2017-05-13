[VTKExamples](/index/)/[Cxx](/Cxx)/Images/NegativeIndices

**NegativeIndices.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  imageData->SetExtent(-5, 5, -5, 5, -5, 5);

  // Fill every entry of the image data with "2.0"
  int* extent = imageData->GetExtent();

#if VTK_MAJOR_VERSION <= 5
  imageData->SetNumberOfScalarComponents(1);
#else
  imageData->AllocateScalars(VTK_UNSIGNED_CHAR,1);
#endif

  std::cout << "Extent: " << " xmin: " << extent[0] << " xmax: " << extent[1]
            << " ymin: " << extent[2] << " ymax: " << extent[3]
            << " zmin: " << extent[4] << " zmax: " << extent[5] << std::endl;


  for (int z = extent[4]; z < extent[5]; z++)
  {
    for (int y = extent[2]; y < extent[3]; y++)
    {
      for (int x = extent[0]; x < extent[1]; x++)
      {
        imageData->SetScalarComponentFromDouble(x,y,z,0,2.0);
      }
    }
  }

  // Retrieve the entries from the image data and print them to the screen
  for (int z = extent[4]; z < extent[5]; z++)
  {
    for (int y = extent[2]; y < extent[3]; y++)
    {
      for (int x = extent[0]; x < extent[1]; x++)
      {
        // Zero is the component, add another loop if you have more
        // than one component
        double v = imageData->GetScalarComponentAsDouble(x,y,z,0);
        // Eo something with v
        std::cout << v << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(NegativeIndices)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(NegativeIndices MACOSX_BUNDLE NegativeIndices.cxx)
 
target_link_libraries(NegativeIndices ${VTK_LIBRARIES})
```

**Download and Build NegativeIndices**

Click [here to download NegativeIndices](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/NegativeIndices.tar) and its *CMakeLists.txt* file.
Once the *tarball NegativeIndices.tar* has been downloaded and extracted,
```
cd NegativeIndices/build 
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
./NegativeIndices
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

