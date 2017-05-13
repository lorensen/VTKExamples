[VTKExamples](/index/)/[Cxx](/Cxx)/Developers/vtkTestReader

### Description
<source lang="cpp">
#ifndef __vtkTestReader_h
#define __vtkTestReader_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestReader : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeMacro(vtkTestReader,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkTestReader *New();
	
protected:
  vtkTestReader();
  ~vtkTestReader();
  
  int FillOutputPortInformation( int port, vtkInformation* info );
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestReader(const vtkTestReader&);  // Not implemented.
  void operator=(const vtkTestReader&);  // Not implemented.

  char* FileName;
};

#endif

</source>

**vtkTestReader.cxx**
```c++
#include "vtkTestReader.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkNew.h"

vtkStandardNewMacro(vtkTestReader);

vtkTestReader::vtkTestReader()
{
  this->FileName = NULL;
  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
}

vtkTestReader::~vtkTestReader()
{

}

// This override is not needed as the FillOutputPortInformation on vtkPolyDataAlgorithm
// does this.  Override this if you need something different from one output that
// is a vtkPolyData
int vtkTestReader::FillOutputPortInformation( int port, vtkInformation* info )
{
  if ( port == 0 )
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
    
    return 1;
  }

  return 0;
}

int vtkTestReader::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{

  // Get the output
  vtkPolyData *output = vtkPolyData::GetData(outputVector,0)
  
  vtkNew<vtkPolyData> polydata;
  vtkNew<vtkPoints> points;
  points->InsertNextPoint(0.0, 0.0, 0.0);
  polydata->SetPoints(points.GetPointer());
  
  //output = polydata.GetPointer(); //doesn't work
  output->ShallowCopy(polydata.GetPointer());
    
  return 1;
}


//----------------------------------------------------------------------------
void vtkTestReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: " 
      << (this->FileName ? this->FileName : "(none)") << "\n";	
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(vtkTestReader)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(vtkTestReader MACOSX_BUNDLE vtkTestReader.cxx)
 
target_link_libraries(vtkTestReader ${VTK_LIBRARIES})
```

**Download and Build vtkTestReader**

Click [here to download vtkTestReader](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/vtkTestReader.tar) and its *CMakeLists.txt* file.
Once the *tarball vtkTestReader.tar* has been downloaded and extracted,
```
cd vtkTestReader/build 
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
./vtkTestReader
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

