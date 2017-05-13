[VTKExamples](/home/)/[Cxx](/Cxx)/ImageData/IterateImageData

### Description
This example demonstrates how to set and access locations in a 3D image.

**IterateImageData.cxx**
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
  imageData->SetDimensions(2,3,1);
#if VTK_MAJOR_VERSION <= 5
  imageData->SetNumberOfScalarComponents(1);
  imageData->SetScalarTypeToDouble();
#else
  imageData->AllocateScalars(VTK_DOUBLE,1);
#endif

  int* dims = imageData->GetDimensions();
  // int dims[3]; // can't do this

  std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

  std::cout << "Number of points: " << imageData->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << imageData->GetNumberOfCells() << std::endl;

  // Fill every entry of the image data with "2.0"
  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
        pixel[0] = 2.0;
      }
    }
  }

  // Retrieve the entries from the image data and print them to the screen
  for (int z = 0; z < dims[2]; z++)
  {
    for (int y = 0; y < dims[1]; y++)
    {
      for (int x = 0; x < dims[0]; x++)
      {
        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
        // do something with v
        std::cout << pixel[0] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  // Access the data linearly
  /*
    vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->SetExtent(0,1,0,1,0,0);
  image->SetScalarTypeToInt();
  image->SetNumberOfScalarComponents(1);

  int* pixel;

  pixel = static_cast<int*>(image->GetScalarPointer(0,0,0));
  pixel[0] = 1;

  pixel = static_cast<int*>(image->GetScalarPointer(1,0,0));
  pixel[0] = 2;

  pixel = static_cast<int*>(image->GetScalarPointer(0,1,0));
  pixel[0] = 3;

  pixel = static_cast<int*>(image->GetScalarPointer(1,1,0));
  pixel[0] = 4;

  vtkIntArray* scalars = vtkIntArray::SafeDownCast(image->GetPointData()->GetArray("ImageScalars"));
  std::cout << "Scalars has " << scalars->GetNumberOfComponents() << " components" << std::endl;
  std::cout << "Scalars has " << scalars->GetNumberOfTuples() << " tuples" << std::endl;

  for(vtkIdType i = 0; i < scalars->GetNumberOfTuples(); i++)
    {
    std::cout << scalars->GetValue(i) << std::endl;
    }
  */
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IterateImageData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IterateImageData MACOSX_BUNDLE IterateImageData.cxx)
 
target_link_libraries(IterateImageData ${VTK_LIBRARIES})
```

**Download and Build IterateImageData**

Click [here to download IterateImageData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IterateImageData.tar) and its *CMakeLists.txt* file.
Once the *tarball IterateImageData.tar* has been downloaded and extracted,
```
cd IterateImageData/build 
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
./IterateImageData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

