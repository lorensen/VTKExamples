[VTKExamples](/home/)/[Cxx](/Cxx)/Developers/vtkTestMultipleInputPortsFilter

### Description
<source lang="cpp">
// .NAME vtkTestMultipleInputPortsFilter
// .SECTION Description
// vtkTestMultipleInputPortsFilter

#ifndef __vtkTestMultipleInputPortsFilter_h
#define __vtkTestMultipleInputPortsFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestMultipleInputPortsFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkTestMultipleInputPortsFilter *New();
  vtkTypeMacro(vtkTestMultipleInputPortsFilter,vtkPolyDataAlgorithm);

protected:
  vtkTestMultipleInputPortsFilter();
  ~vtkTestMultipleInputPortsFilter() VTK_OVERRIDE {}

  int FillInputPortInformation( int port, vtkInformation* info ) VTK_OVERRIDE;
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;

private:
  vtkTestMultipleInputPortsFilter(const vtkTestMultipleInputPortsFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkTestMultipleInputPortsFilter&) VTK_DELETE_FUNCTION;

};

#endif
</source>

**vtkTestMultipleInputPortsFilter.cxx**
```c++
#include "vtkTestMultipleInputPortsFilter.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkTestMultipleInputPortsFilter);

vtkTestMultipleInputPortsFilter::vtkTestMultipleInputPortsFilter()
{
  this->SetNumberOfInputPorts(2);
}

int vtkTestMultipleInputPortsFilter::FillInputPortInformation( int port, vtkInformation* info )
{
  if ( port == 0 )
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
    return 1;
  }
  else if(port == 1)
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
    return 1;
  }

  return 0;
}

int vtkTestMultipleInputPortsFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the info objects
  vtkInformation *inInfo0 = inputVector[0]->GetInformationObject(0);
  vtkInformation *inInfo1 = inputVector[1]->GetInformationObject(0);

  vtkInformation *outInfo = outputVector->GetInformationObject(0);


  // get the input and ouptut
  vtkPolyData *input0 = vtkPolyData::SafeDownCast(
      inInfo0->Get(vtkDataObject::DATA_OBJECT()));

  std::cout << "input0 has " << input0->GetNumberOfPoints() << " points." << std::endl;

  vtkPolyData *input1 = vtkPolyData::SafeDownCast(
      inInfo1->Get(vtkDataObject::DATA_OBJECT()));

  std::cout << "input1 has " << input1->GetNumberOfPoints() << " points." << std::endl;

  vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  output->ShallowCopy(input0);

  return 1;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestMultipleInputPortsFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestMultipleInputPortsFilter MACOSX_BUNDLE vtkTestMultipleInputPortsFilter.cxx)
 
target_link_libraries(vtkTestMultipleInputPortsFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestMultipleInputPortsFilter**

Click [here to download vtkTestMultipleInputPortsFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestMultipleInputPortsFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestMultipleInputPortsFilter.tar* has been downloaded and extracted,
```
cd vtkTestMultipleInputPortsFilter/build 
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
./vtkTestMultipleInputPortsFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

