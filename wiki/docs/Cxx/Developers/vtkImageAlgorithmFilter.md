[VTKExamples](Home)/[Cxx](Cxx)/Developers/vtkImageAlgorithmFilter

### Description
<source lang="cpp">
#ifndef __vtkImageAlgorithmFilter_h
#define __vtkImageAlgorithmFilter_h

#include "vtkImageAlgorithm.h"

class vtkImageAlgorithmFilter : public vtkImageAlgorithm 
{
public:
  static vtkImageAlgorithmFilter *New();
  vtkTypeMacro(vtkImageAlgorithmFilter,vtkImageAlgorithm);

  vtkImageAlgorithmFilter(){}
  
protected:

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkImageAlgorithmFilter(const vtkImageAlgorithmFilter&);  // Not implemented.
  void operator=(const vtkImageAlgorithmFilter&);  // Not implemented.
};

#endif
</source>

**vtkImageAlgorithmFilter.cxx**
```c++
#include "vtkImageAlgorithmFilter.h"

#include "vtkImageData.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkImageAlgorithmFilter);

int vtkImageAlgorithmFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{
  // Get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  
  // Get the input and ouptut
  vtkImageData *input = vtkImageData::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  vtkImageData *output = vtkImageData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));
    
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->ShallowCopy(input);
  
  image->SetScalarComponentFromDouble(0,0,0,0, 5.0);
  
  output->ShallowCopy(image);

  // Without these lines, the output will appear real but will not work as the input to any other filters
  int extent[6];
  input->GetExtent(extent);
  output->SetExtent(extent);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
               extent,
               6);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               extent,
               6);
  return 1;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkImageAlgorithmFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkImageAlgorithmFilter MACOSX_BUNDLE vtkImageAlgorithmFilter.cxx)
 
target_link_libraries(vtkImageAlgorithmFilter ${VTK_LIBRARIES})
```

**Download and Build vtkImageAlgorithmFilter**

Click [here to download vtkImageAlgorithmFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkImageAlgorithmFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkImageAlgorithmFilter.tar* has been downloaded and extracted,
```
cd vtkImageAlgorithmFilter/build 
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
./vtkImageAlgorithmFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

