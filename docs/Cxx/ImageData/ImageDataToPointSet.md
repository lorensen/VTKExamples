[VTKExamples](/index/)/[Cxx](/Cxx)/ImageData/ImageDataToPointSet

**ImageDataToPointSet.cxx**
```c++
#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkPoints.h>
#include <vtkImageDataToPointSet.h>
#include <vtkSmartPointer.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkStructuredGrid.h>

static void CreateImage(vtkImageData* image);

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  CreateImage(image);

  vtkSmartPointer<vtkImageDataToPointSet> imageDataToPointSet =
    vtkSmartPointer<vtkImageDataToPointSet>::New();
#if VTK_MAJOR_VERSION <= 5
  imageDataToPointSet->SetInputConnection(image->GetProducerPort());
#else
  imageDataToPointSet->SetInputData(image);
#endif
  imageDataToPointSet->Update();

  vtkSmartPointer<vtkXMLStructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
  writer->SetInputConnection(imageDataToPointSet->GetOutputPort());
  writer->SetFileName("Test.vts");
  writer->Write();

  return EXIT_SUCCESS;
}

void CreateImage(vtkImageData* image)
{
  // Create an image
  image->SetDimensions(3,3,1);
#if VTK_MAJOR_VERSION <= 5
  image->SetNumberOfScalarComponents(1);
  image->SetScalarTypeToUnsignedChar();
#else
  image->AllocateScalars(VTK_UNSIGNED_CHAR,1);
#endif

  int dims[3];
  image->GetDimensions(dims);
  for(int i = 0; i < dims[0]; i++)
  {
    for(int j = 0; j < dims[1]; j++)
    {
      unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(i,j,0));
      pixel[0] = 1;
    }
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageDataToPointSet)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageDataToPointSet MACOSX_BUNDLE ImageDataToPointSet.cxx)
 
target_link_libraries(ImageDataToPointSet ${VTK_LIBRARIES})
```

**Download and Build ImageDataToPointSet**

Click [here to download ImageDataToPointSet](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageDataToPointSet.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageDataToPointSet.tar* has been downloaded and extracted,
```
cd ImageDataToPointSet/build 
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
./ImageDataToPointSet
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

