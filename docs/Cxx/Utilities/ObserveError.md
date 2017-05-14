[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/ObserveError

### Description
When vtk encounters an error or warning, by default the message is written to standard output. This example shows how to catch the error or warning. The example prints to standard output, but an application may wish to present the error or warning in a different manner, e.g. write to a log file or present the message in a window.

**ObserveError.cxx**
```c++
#include <string>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkCommand.h>

class ErrorObserver : public vtkCommand
{
public:
  ErrorObserver():
    Error(false),
    Warning(false),
    ErrorMessage(""),
    WarningMessage("") {}
  static ErrorObserver *New()
  {
  return new ErrorObserver;
  }
  bool GetError() const
  {
  return this->Error;
  }
  bool GetWarning() const
  {
  return this->Warning;
  }
  void Clear()
  {
  this->Error = false;
  this->Warning = false;
  this->ErrorMessage = "";
  this->WarningMessage = "";
  }
  virtual void Execute(vtkObject *vtkNotUsed(caller),
                       unsigned long event,
                       void *calldata)
  {
  switch(event)
  {
    case vtkCommand::ErrorEvent:
      ErrorMessage = static_cast<char *>(calldata);
      this->Error = true;
      break;
    case vtkCommand::WarningEvent:
      WarningMessage = static_cast<char *>(calldata);
      this->Warning = true;
      break;
  }
  }
  std::string GetErrorMessage()
  {
  return ErrorMessage;
  }
std::string GetWarningMessage()
{
  return WarningMessage;
}
private:
  bool        Error;
  bool        Warning;
  std::string ErrorMessage;
  std::string WarningMessage;
};

int main (int, char *[])
{
  vtkSmartPointer<ErrorObserver>  errorObserver =
    vtkSmartPointer<ErrorObserver>::New();

  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->AddObserver(vtkCommand::ErrorEvent,errorObserver);
  image->AddObserver(vtkCommand::WarningEvent,errorObserver);
  image->GetCell(1);
  if (errorObserver->GetError())
  {
    std::cout << "Caught error! " << errorObserver->GetErrorMessage();
  }

  image->ShallowCopy(NULL);
  if (errorObserver->GetWarning())
  {
    std::cout << "Caught warning! " << errorObserver->GetWarningMessage();
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ObserveError)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ObserveError MACOSX_BUNDLE ObserveError.cxx)
 
target_link_libraries(ObserveError ${VTK_LIBRARIES})
```

**Download and Build ObserveError**

Click [here to download ObserveError](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ObserveError.tar) and its *CMakeLists.txt* file.
Once the *tarball ObserveError.tar* has been downloaded and extracted,
```
cd ObserveError/build 
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
./ObserveError
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

