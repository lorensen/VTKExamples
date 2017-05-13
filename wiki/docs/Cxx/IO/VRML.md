[VTKExamples](/home/)/[Cxx](/Cxx)/IO/VRML

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestVRML.png?raw=true" width="256" />

### Description
This example loads a wrl file and displays it on the screen. An example file is [here](http://www.vtk.org/Wiki/Image:Bridge.wrl.zip).

**VRML.cxx**
```c++
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVRMLImporter.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main ( int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];
  std::cout << "Reading " << filename << std::endl;

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // VRML Import
  vtkSmartPointer<vtkVRMLImporter> importer = vtkSmartPointer<vtkVRMLImporter>::New();
  importer->SetFileName ( filename.c_str() );
  importer->SetRenderWindow(renderWindow);
  importer->Update();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VRML)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VRML MACOSX_BUNDLE VRML.cxx)
 
target_link_libraries(VRML ${VTK_LIBRARIES})
```

**Download and Build VRML**

Click [here to download VRML](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VRML.tar) and its *CMakeLists.txt* file.
Once the *tarball VRML.tar* has been downloaded and extracted,
```
cd VRML/build 
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
./VRML
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

