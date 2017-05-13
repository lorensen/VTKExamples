[VTKExamples](/index/)/[Cxx](/Cxx)/IO/ReadDICOM

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestReadDICOM.png?raw=true" width="256" />

### Description
This example reads a DICOM file and displays it on the screen. [Here](http://www.vtk.org/Wiki/images/2/27/DICOM_Prostate.zip) is an example data set.

See also: [ExportDICOMtoVTI](Cxx/IO/ExportDICOMtoVTI) and [ReadDICOM](Cxx/IO/ReadDICOM).

**ReadDICOM.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(.img)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read all the DICOM files in the specified directory.
  vtkSmartPointer<vtkDICOMImageReader> reader =
    vtkSmartPointer<vtkDICOMImageReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(reader->GetOutputPort());
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReadDICOM)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadDICOM MACOSX_BUNDLE ReadDICOM.cxx)
 
target_link_libraries(ReadDICOM ${VTK_LIBRARIES})
```

**Download and Build ReadDICOM**

Click [here to download ReadDICOM](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadDICOM.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadDICOM.tar* has been downloaded and extracted,
```
cd ReadDICOM/build 
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
./ReadDICOM
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

