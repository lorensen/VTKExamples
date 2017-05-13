[VTKExamples](Home)/[Cxx](Cxx)/SimpleOperations/GaussianRandomNumber

### Description
This example generates 3 random numbers from a Gaussian distribution with mean 0.0 and standard deviation 2.0.

**GaussianRandomNumber.cxx**
```c++
#include <vtkMath.h>
#include <time.h>

int main(int, char *[])
{
  //The number of random numbers we wish to produce
  unsigned int numRand = 3;

  //without this line, the random numbers will be the same every iteration
  vtkMath::RandomSeed(time(NULL));

  //Generate numRand random numbers from a Gaussian distribution with mean 0.0 and standard deviation 2.0
  for(unsigned int i = 0; i < numRand; i++)
  {
    double a = vtkMath::Gaussian(0.0,2.0);
    std::cout << a << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GaussianRandomNumber)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GaussianRandomNumber MACOSX_BUNDLE GaussianRandomNumber.cxx)
 
target_link_libraries(GaussianRandomNumber ${VTK_LIBRARIES})
```

**Download and Build GaussianRandomNumber**

Click [here to download GaussianRandomNumber](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GaussianRandomNumber.tar) and its *CMakeLists.txt* file.
Once the *tarball GaussianRandomNumber.tar* has been downloaded and extracted,
```
cd GaussianRandomNumber/build 
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
./GaussianRandomNumber
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

