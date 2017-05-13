[VTKExamples](Home)/[Cxx](Cxx)/Developers/ImageAlgorithmFilter

### Description
This example demonstrates how to setup the pipeline for a {{class|vtkImageAlgorithm}} filter that takes a {{class|vtkImageData}} as input and produces another vtkImageData as output. This particular example creates a 2x2 image and fills it with "2"s. The filter changes the (0,0) element to a 5.

**ImageAlgorithmFilter.cxx**
```c++
#include <vtkSmartPointer.h>

#include "vtkImageAlgorithmFilter.h"
#include "vtkImageData.h"

void PrintImage(vtkImageData* image);

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> input =
    vtkSmartPointer<vtkImageData>::New();
  // Setup the image
  input->SetDimensions(2,2,1);
  input->AllocateScalars(VTK_DOUBLE,1);

  // Fill every entry of the image data with "2.0"
  int* dims = input->GetDimensions();

  for (int y=0; y<dims[1]; y++)
  {
    for (int x=0; x<dims[0]; x++)
    {
      input->SetScalarComponentFromDouble(x,y,0,0,2.0);
    }
  }

  std::cout << "Input image: " << std::endl;
  PrintImage(input);

  vtkSmartPointer<vtkImageAlgorithmFilter> filter =
    vtkSmartPointer<vtkImageAlgorithmFilter>::New();
  filter->SetInputData(input);
  filter->Update();

  vtkImageData* output = filter->GetOutput();

  std::cout << "Output image: " << std::endl;
  PrintImage(output);

  return 0;
}

void PrintImage(vtkImageData* image)
{
  int* dims = image->GetDimensions();

  for (int y=0; y<dims[1]; y++)
  {
    for (int x=0; x<dims[0]; x++)
    {
      double v = image->GetScalarComponentAsDouble(x,y,0,0);
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageAlgorithmFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageAlgorithmFilter MACOSX_BUNDLE ImageAlgorithmFilter.cxx)
 
target_link_libraries(ImageAlgorithmFilter ${VTK_LIBRARIES})
```

**Download and Build ImageAlgorithmFilter**

Click [here to download ImageAlgorithmFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageAlgorithmFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageAlgorithmFilter.tar* has been downloaded and extracted,
```
cd ImageAlgorithmFilter/build 
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
./ImageAlgorithmFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

