[VTKExamples](/index/)/[Cxx](/Cxx)/SimpleOperations/RandomSequence

### Description
This is the "new" (December, 2009) VTK way to produce random numbers. It is actually a random sequence generator.

**RandomSequence.cxx**
```c++
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  //Create a random sequence generator.
  vtkSmartPointer<vtkMinimalStandardRandomSequence> sequence = 
      vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();

  // initialize the sequence
  sequence->SetSeed(1);

  //Get 3 random numbers.
  double x = sequence->GetValue();
  sequence->Next();
  double y = sequence->GetValue();
  sequence->Next();
  double z = sequence->GetValue();
  
  // You can also use seq->GetRangeValue(-1.0,1.0); 
  //to set a range on the random values.

  //Output the resulting random numbersl
  std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RandomSequence)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RandomSequence MACOSX_BUNDLE RandomSequence.cxx)
 
target_link_libraries(RandomSequence ${VTK_LIBRARIES})
```

**Download and Build RandomSequence**

Click [here to download RandomSequence](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RandomSequence.tar) and its *CMakeLists.txt* file.
Once the *tarball RandomSequence.tar* has been downloaded and extracted,
```
cd RandomSequence/build 
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
./RandomSequence
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

