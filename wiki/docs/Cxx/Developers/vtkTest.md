[VTKExamples](/home/)/[Cxx](/Cxx)/Developers/vtkTest

### Description
<source lang="cpp">
#ifndef __vtkTest_h
#define __vtkTest_h

#include "vtkDataObject.h"

class vtkTest : public vtkDataObject
{
  public:
    static vtkTest* New();
    vtkTypeMacro(vtkTest,vtkDataObject);
    void PrintSelf( ostream& os, vtkIndent indent );
    void ShallowCopy(vtkTest* t);
    
    vtkGetMacro(Value, double);
    vtkSetMacro(Value, double);
    
  protected:
    vtkTest();
    ~vtkTest();
    
    
  private:
    vtkTest( const vtkTest& ); // Not implemented.
    void operator = ( const vtkTest& ); // Not implemented.
    
    double Value;
};

#endif 
</source>

**vtkTest.cxx**
```c++
#include "vtkTest.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTest);

vtkTest::vtkTest()
{
  this->Value = 0.0;
}

vtkTest::~vtkTest()
{

}

void vtkTest::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}

void vtkTest::ShallowCopy(vtkTest* t)
{
  this->Value = t->GetValue(); 
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTest)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTest MACOSX_BUNDLE vtkTest.cxx)
 
target_link_libraries(vtkTest ${VTK_LIBRARIES})
```

**Download and Build vtkTest**

Click [here to download vtkTest](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTest.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTest.tar* has been downloaded and extracted,
```
cd vtkTest/build 
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
./vtkTest
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

