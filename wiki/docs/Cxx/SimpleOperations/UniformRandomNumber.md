[VTKExamples](Home)/[Cxx](Cxx)/SimpleOperations/UniformRandomNumber

### Description
This example generates 3 random numbers between 0 and 2 from a uniform distribution.

**UniformRandomNumber.cxx**
```c++
#include <vtkMath.h>
#include <time.h>

int main(int, char *[])
{
  // Set the number of random numbers we wish to produce to 3.
  unsigned int numRand = 3;

  // Without this line, the random numbers will be the same every iteration.
  vtkMath::RandomSeed(time(NULL));

  // Generate numRand random numbers from a uniform distribution between 0.0 and 2.0
  for(unsigned int i = 0; i < numRand; i++)
  {
    double a = vtkMath::Random(0.0,2.0);
    std::cout << a << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(UniformRandomNumber)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(UniformRandomNumber MACOSX_BUNDLE UniformRandomNumber.cxx)
 
target_link_libraries(UniformRandomNumber ${VTK_LIBRARIES})
```

**Download and Build UniformRandomNumber**

Click [here to download UniformRandomNumber](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/UniformRandomNumber.tar) and its *CMakeLists.txt* file.
Once the *tarball UniformRandomNumber.tar* has been downloaded and extracted,
```
cd UniformRandomNumber/build 
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
./UniformRandomNumber
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

