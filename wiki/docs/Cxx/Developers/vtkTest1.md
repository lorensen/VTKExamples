[VTKExamples](Home)/[Cxx](Cxx)/Developers/vtkTest1

### Description
<source lang="cpp">
#ifndef __vtkTest1_h
#define __vtkTest1_h

#include "vtkDataObject.h"

class vtkTest1 : public vtkDataObject
{
  public:
    static vtkTest1* New();
    vtkTypeMacro(vtkTest1,vtkDataObject);
    void PrintSelf( ostream& os, vtkIndent indent );

    vtkGetMacro(Value, double);
    
  protected:
    vtkTest1();
    ~vtkTest1();

  private:
    vtkTest1( const vtkTest1& ); // Not implemented.
    void operator = ( const vtkTest1& ); // Not implemented.
    
    double Value;
};

#endif 
</source>

**vtkTest1.cxx**
```c++
#include "vtkTest1.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTest1);

vtkTest1::vtkTest1()
{
  this->Value = 4.5;
}

vtkTest1::~vtkTest1()
{

}

void vtkTest1::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTest1)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTest1 MACOSX_BUNDLE vtkTest1.cxx)
 
target_link_libraries(vtkTest1 ${VTK_LIBRARIES})
```

**Download and Build vtkTest1**

Click [here to download vtkTest1](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTest1.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTest1.tar* has been downloaded and extracted,
```
cd vtkTest1/build 
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
./vtkTest1
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

