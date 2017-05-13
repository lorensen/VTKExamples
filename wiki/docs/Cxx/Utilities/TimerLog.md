[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/TimerLog

**TimerLog.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkTimerLog.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkTimerLog> timerLog = 
      vtkSmartPointer<vtkTimerLog>::New();
  
  std::cout << "Current time: " << timerLog->GetUniversalTime() << std::endl;
  
  timerLog->MarkEvent("opened file");
  
  timerLog->MarkEvent("did other stuff");
  
  std::cout << "Timer log:" << *timerLog << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TimerLog)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TimerLog MACOSX_BUNDLE TimerLog.cxx)
 
target_link_libraries(TimerLog ${VTK_LIBRARIES})
```

**Download and Build TimerLog**

Click [here to download TimerLog](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TimerLog.tar) and its *CMakeLists.txt* file.
Once the *tarball TimerLog.tar* has been downloaded and extracted,
```
cd TimerLog/build 
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
./TimerLog
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

