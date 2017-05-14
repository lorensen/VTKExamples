[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/DiscretizableColorTransferFunction

**DiscretizableColorTransferFunction.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkDiscretizableColorTransferFunction.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDiscretizableColorTransferFunction> discretizableColorTransferFunction = 
    vtkSmartPointer<vtkDiscretizableColorTransferFunction>::New();
  
  discretizableColorTransferFunction->DiscretizeOn();
  discretizableColorTransferFunction->SetNumberOfValues(10);
  
  discretizableColorTransferFunction->AddRGBPoint(0.0, 1, 0, 0);
  discretizableColorTransferFunction->AddRGBPoint(10.0, 0, 1, 0);
  discretizableColorTransferFunction->Build();
  
  double color[3];
  discretizableColorTransferFunction->GetColor(1.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  discretizableColorTransferFunction->GetColor(5.0, color);
  std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DiscretizableColorTransferFunction)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DiscretizableColorTransferFunction MACOSX_BUNDLE DiscretizableColorTransferFunction.cxx)
 
target_link_libraries(DiscretizableColorTransferFunction ${VTK_LIBRARIES})
```

**Download and Build DiscretizableColorTransferFunction**

Click [here to download DiscretizableColorTransferFunction](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DiscretizableColorTransferFunction.tar) and its *CMakeLists.txt* file.
Once the *tarball DiscretizableColorTransferFunction.tar* has been downloaded and extracted,
```
cd DiscretizableColorTransferFunction/build 
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
./DiscretizableColorTransferFunction
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

