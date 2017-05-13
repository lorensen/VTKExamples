[VTKExamples](/index/)/[Cxx](/Cxx)/Images/ImageExport

**ImageExport.cxx**
```c++
#include <vtkImageData.h>
#include <vtkImageExport.h>
#include <vtkSmartPointer.h>
#include <vtkVersion.h>

int main(int, char *[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData =
    vtkSmartPointer<vtkImageData>::New();

  // Specify the size of the image data
  int dims[3] = {2,3,1};

  imageData->SetDimensions(dims[0], dims[1], dims[2]);
#if VTK_MAJOR_VERSION <= 5
  imageData->SetNumberOfScalarComponents(1);
  imageData->SetScalarTypeToUnsignedChar();
#else
  imageData->AllocateScalars(VTK_UNSIGNED_CHAR,1);
#endif

  unsigned char value = 0;
  for(int row = 0; row < dims[0]; ++row)
  {
    for(int col = 0; col < dims[1]; ++col)
    {
      unsigned char* pixel =
        static_cast<unsigned char*>(imageData->GetScalarPointer(row, col, 0));
      pixel[0] = value;
      value += 10;
    }
  }

  // Create the c-style image to convert the VTK image to
  unsigned char *cImage = new unsigned char[dims[0]*dims[1]*dims[2]];

  vtkSmartPointer<vtkImageExport> exporter =
    vtkSmartPointer<vtkImageExport>::New();
#if VTK_MAJOR_VERSION <= 5
  exporter->SetInput(imageData);
#else
  exporter->SetInputData(imageData);
#endif
  exporter->ImageLowerLeftOn();
  exporter->Update();
  exporter->Export(cImage);

  // Output the raw c-style image
  for(int row = 0; row < dims[0]; ++row)
  {
    for(int col = 0; col < dims[1]; ++col)
    {
      std::cout << static_cast<int>(cImage[col * dims[0] + row]) << " ";
    }
    std::cout << std::endl;
  }
  delete [] cImage;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageExport)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageExport MACOSX_BUNDLE ImageExport.cxx)
 
target_link_libraries(ImageExport ${VTK_LIBRARIES})
```

**Download and Build ImageExport**

Click [here to download ImageExport](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageExport.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageExport.tar* has been downloaded and extracted,
```
cd ImageExport/build 
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
./ImageExport
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

