[VTKExamples](/home/)/[Cxx](/Cxx)/Demos/vtkTestFilter

### Description
<source lang="cpp">
#include "vtkTestFilter.h"

#include "vtkObjectFactory.h"
#include "vtkCommand.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"
#include "vtkAppendPolyData.h"
#include "vtkSphereSource.h"

vtkStandardNewMacro(vtkTestFilter);

vtkTestFilter::vtkTestFilter()
{
  this->SetNumberOfInputPorts(0);
  this->Output = vtkSmartPointer<vtkPolyData>::New();

  this->RefreshEvent = vtkCommand::UserEvent + 1;

}

int vtkTestFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{
  // Get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  this->Output->DeepCopy(output);

  for(unsigned int i = 0; i < 10; i++)
    {
    Iterate(i);
    this->InvokeEvent(this->RefreshEvent, NULL);
    }

  output->ShallowCopy(this->Output);

  return 1;
}

void vtkTestFilter::Iterate(unsigned int iteration)
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(iteration, 0, 0);
  sphereSource->SetRadius(0.2);
  sphereSource->Update();

  vtkSmartPointer<vtkAppendPolyData> appendFilter =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(this->Output->GetProducerPort());
  appendFilter->AddInputConnection(sphereSource->GetOutputPort());
  appendFilter->Update();

  this->Output->DeepCopy(appendFilter->GetOutput());
}

</source>

**vtkTestFilter.cxx**
```c++
#include "vtkTestFilter.h"

#include "vtkObjectFactory.h"
#include "vtkCommand.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"
#include "vtkAppendPolyData.h"
#include "vtkSphereSource.h"

vtkStandardNewMacro(vtkTestFilter);

vtkTestFilter::vtkTestFilter()
{
  this->SetNumberOfInputPorts(0);
  this->Output = vtkSmartPointer<vtkPolyData>::New();

  this->RefreshEvent = vtkCommand::UserEvent + 1;

}

int vtkTestFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{
  // Get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  this->Output->DeepCopy(output);

  for(unsigned int i = 0; i < 10; i++)
  {
    Iterate(i);
    this->InvokeEvent(this->RefreshEvent, NULL);
  }

  output->ShallowCopy(this->Output);

  return 1;
}

void vtkTestFilter::Iterate(unsigned int iteration)
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(iteration, 0, 0);
  sphereSource->SetRadius(0.2);
  sphereSource->Update();

  vtkSmartPointer<vtkAppendPolyData> appendFilter =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(this->Output->GetProducerPort());
  appendFilter->AddInputConnection(sphereSource->GetOutputPort());
  appendFilter->Update();

  this->Output->DeepCopy(appendFilter->GetOutput());
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestFilter MACOSX_BUNDLE vtkTestFilter.cxx)
 
target_link_libraries(vtkTestFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestFilter**

Click [here to download vtkTestFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestFilter.tar* has been downloaded and extracted,
```
cd vtkTestFilter/build 
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
./vtkTestFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

