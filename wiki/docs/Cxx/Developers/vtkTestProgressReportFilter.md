[VTKExamples](/index/)/[Cxx](/Cxx)/Developers/vtkTestProgressReportFilter

### Description
<source lang="cpp">
#ifndef __vtkTestProgressReportFilter_h
#define __vtkTestProgressReportFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestProgressReportFilter : public vtkPolyDataAlgorithm
{
public:
  static vtkTestProgressReportFilter *New();
  vtkTypeMacro(vtkTestProgressReportFilter,vtkAlgorithm);
 
protected:
  vtkTestProgressReportFilter(){}
  ~vtkTestProgressReportFilter() VTK_OVERRIDE {}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;
 
private:
  vtkTestProgressReportFilter(const vtkTestProgressReportFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkTestProgressReportFilter&) VTK_DELETE_FUNCTION;
 
};
 
#endif
</source>

**vtkTestProgressReportFilter.cxx**
```c++
#include "vtkTestProgressReportFilter.h"
 
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"
 
vtkStandardNewMacro(vtkTestProgressReportFilter);

int vtkTestProgressReportFilter::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
 
  // Get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
 
 
  // Get the input and ouptut
  vtkPolyData *input = vtkPolyData::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
 
  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));
 
  for(vtkIdType i = 0; i < input->GetNumberOfPoints(); i++)
  {
    this->UpdateProgress(static_cast<double>(i)/input->GetNumberOfPoints());
  }
     
  output->ShallowCopy(input);
 
  return 1;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestProgressReportFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestProgressReportFilter MACOSX_BUNDLE vtkTestProgressReportFilter.cxx)
 
target_link_libraries(vtkTestProgressReportFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestProgressReportFilter**

Click [here to download vtkTestProgressReportFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestProgressReportFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestProgressReportFilter.tar* has been downloaded and extracted,
```
cd vtkTestProgressReportFilter/build 
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
./vtkTestProgressReportFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

