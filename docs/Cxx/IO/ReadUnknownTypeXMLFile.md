[VTKExamples](/index/)/[Cxx](/Cxx)/IO/ReadUnknownTypeXMLFile

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestReadUnknownTypeXMLFile.png?raw=true" width="256" />

### Description
This examples reads either a vtu (unstructured grid) or vtp (polydata) file and displays it to the screen.

**ReadUnknownTypeXMLFile.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLGenericDataObjectReader.h>

int main(int argc, char *argv[])
{
  // Ensure a filename was specified
  if(argc < 2)
  {
    std::cerr << "Required arguments: InputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  // Get the filename from the command line
  std::string inputFilename = argv[1];

  // Get all data from the file
  vtkSmartPointer<vtkXMLGenericDataObjectReader> reader =
    vtkSmartPointer<vtkXMLGenericDataObjectReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // All of the standard data types can be checked and obtained like this:
  if(vtkPolyData::SafeDownCast(reader->GetOutput()))
  {
    std::cout << "File is a polydata" << std::endl;
  }
  else if(vtkUnstructuredGrid::SafeDownCast(reader->GetOutput()))
  {
    std::cout << "File is an unstructured grid" << std::endl;
  }

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReadUnknownTypeXMLFile)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadUnknownTypeXMLFile MACOSX_BUNDLE ReadUnknownTypeXMLFile.cxx)
 
target_link_libraries(ReadUnknownTypeXMLFile ${VTK_LIBRARIES})
```

**Download and Build ReadUnknownTypeXMLFile**

Click [here to download ReadUnknownTypeXMLFile](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadUnknownTypeXMLFile.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadUnknownTypeXMLFile.tar* has been downloaded and extracted,
```
cd ReadUnknownTypeXMLFile/build 
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
./ReadUnknownTypeXMLFile
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

