[VTKExamples](/index/)/[Cxx](/Cxx)/Meshes/SplitPolyData

### Description
The vtkOBBDicer filter breaks up an input mesh into a number of pieces. The resulting mesh contains scalar point data that can be used to extract the individual pieces with a filter like vtkThresholdFilter. This example stores each piece into a .vtp file.

**SplitPolyData.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkOBBDicer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkThreshold.h>
#include <vtkGeometryFilter.h>

#include <vtksys/SystemTools.hxx>
#include <sstream>

int main(int argc, char *argv[])
{
  std::string filename;
  std::string extension;

  vtkSmartPointer<vtkPolyData> inputPolyData;
  if(argc > 1)
  {
    filename = vtksys::SystemTools::GetFilenameWithoutExtension(std::string(argv[1]));
    extension = vtksys::SystemTools::GetFilenameExtension(std::string(argv[1]));
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    filename = "sphere";
    extension = ".vtp";
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  // Create pipeline
  vtkSmartPointer<vtkOBBDicer> dicer =
  vtkSmartPointer<vtkOBBDicer>::New();
#if VTK_MAJOR_VERSION <= 5
  dicer->SetInput(inputPolyData);
#else
  dicer->SetInputData(inputPolyData);
#endif
  dicer->SetNumberOfPieces(4);
  dicer->SetDiceModeToSpecifiedNumberOfPieces();
  dicer->Update();

  vtkSmartPointer<vtkThreshold> selector =
    vtkSmartPointer<vtkThreshold>::New();
  selector->SetInputArrayToProcess(0, 0, 0, 0, "vtkOBBDicer_GroupIds");
  selector->SetInputConnection(dicer->GetOutputPort());
  selector->AllScalarsOff();
  vtkSmartPointer<vtkGeometryFilter> geometry =
    vtkSmartPointer<vtkGeometryFilter>::New();
  geometry->SetInputConnection(selector->GetOutputPort());

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(geometry->GetOutputPort());
  for (int i = 0; i < dicer->GetNumberOfActualPieces(); ++i)
  {
    std::stringstream pieceName;
    pieceName << filename << "_" << i + 1 << extension;
    selector->ThresholdBetween(i, i);
    writer->SetFileName(pieceName.str().c_str());
    writer->Write();
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(SplitPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(SplitPolyData MACOSX_BUNDLE SplitPolyData.cxx)
 
target_link_libraries(SplitPolyData ${VTK_LIBRARIES})
```

**Download and Build SplitPolyData**

Click [here to download SplitPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/SplitPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball SplitPolyData.tar* has been downloaded and extracted,
```
cd SplitPolyData/build 
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
./SplitPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

