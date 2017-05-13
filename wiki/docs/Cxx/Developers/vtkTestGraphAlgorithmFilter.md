[VTKExamples](Home)/[Cxx](Cxx)/Developers/vtkTestGraphAlgorithmFilter

### Description
<source lang="cpp">
#ifndef __vtkTestGraphAlgorithmFilter_h
#define __vtkTestGraphAlgorithmFilter_h

#include "vtkGraphAlgorithm.h"

class vtkTestGraphAlgorithmFilter : public vtkGraphAlgorithm 
{
public:
  vtkTypeMacro(vtkTestGraphAlgorithmFilter,vtkGraphAlgorithm);
  
  static vtkTestGraphAlgorithmFilter *New();
	
protected:
  vtkTestGraphAlgorithmFilter(){}
  ~vtkTestGraphAlgorithmFilter(){}
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestGraphAlgorithmFilter(const vtkTestGraphAlgorithmFilter&);  // Not implemented.
  void operator=(const vtkTestGraphAlgorithmFilter&);  // Not implemented.

};

#endif
</source>

**vtkTestGraphAlgorithmFilter.cxx**
```c++
#include "vtkTestGraphAlgorithmFilter.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"
#include "vtkMutableUndirectedGraph.h"
#include "vtkMutableDirectedGraph.h"
#include "vtkMutableGraphHelper.h"

vtkStandardNewMacro(vtkTestGraphAlgorithmFilter);

int vtkTestGraphAlgorithmFilter::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{

  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the input and ouptut
  vtkGraph *input = vtkGraph::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkGraph *output = vtkGraph::SafeDownCast(
                                    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkSmartPointer<vtkMutableDirectedGraph> mdg =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  vtkSmartPointer<vtkMutableUndirectedGraph> mug =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  if(input->IsA("vtkMutableUndirectedGraph"))
  {
    vtkSmartPointer<vtkMutableUndirectedGraph> ug =
      vtkSmartPointer<vtkMutableUndirectedGraph>::New();
    ug->AddVertex();
    output->ShallowCopy(ug);
  }
  else if(input->IsA("vtkMutableDirectedGraph"))
  {
    vtkSmartPointer<vtkMutableDirectedGraph> dg =
      vtkSmartPointer<vtkMutableDirectedGraph>::New();
    dg->AddVertex();
    output->ShallowCopy(dg);
  }


  std::cout << "Output is type: " << output->GetClassName() << std::endl;

  return 1;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestGraphAlgorithmFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestGraphAlgorithmFilter MACOSX_BUNDLE vtkTestGraphAlgorithmFilter.cxx)
 
target_link_libraries(vtkTestGraphAlgorithmFilter ${VTK_LIBRARIES})
```

**Download and Build vtkTestGraphAlgorithmFilter**

Click [here to download vtkTestGraphAlgorithmFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestGraphAlgorithmFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestGraphAlgorithmFilter.tar* has been downloaded and extracted,
```
cd vtkTestGraphAlgorithmFilter/build 
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
./vtkTestGraphAlgorithmFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

