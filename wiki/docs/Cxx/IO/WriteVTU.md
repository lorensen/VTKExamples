[VTKExamples](/home/)/[Cxx](/Cxx)/IO/WriteVTU

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestWriteVTU.png?raw=true" width="256" />

### Description
This example writes a VTU file.

**WriteVTU.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkCellArray.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkVertexGlyphFilter.h>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cout << "Required arguments: OutputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(0, 1, 1);

   vtkSmartPointer<vtkTetra> tetra =
    vtkSmartPointer<vtkTetra>::New();

  tetra->GetPointIds()->SetId(0, 0);
  tetra->GetPointIds()->SetId(1, 1);
  tetra->GetPointIds()->SetId(2, 2);
  tetra->GetPointIds()->SetId(3, 3);

  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(tetra);


  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid->SetPoints(points);
  unstructuredGrid->SetCells(VTK_TETRA, cellArray);

  // Write file
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(filename.c_str());
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(unstructuredGrid);
#else
  writer->SetInputData(unstructuredGrid);
#endif
  writer->Write();

  // Read and display file for verification that it was written correclty
  vtkSmartPointer<vtkXMLUnstructuredGridReader> reader =
    vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

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
 
PROJECT(WriteVTU)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WriteVTU MACOSX_BUNDLE WriteVTU.cxx)
 
target_link_libraries(WriteVTU ${VTK_LIBRARIES})
```

**Download and Build WriteVTU**

Click [here to download WriteVTU](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WriteVTU.tar) and its *CMakeLists.txt* file.
Once the *tarball WriteVTU.tar* has been downloaded and extracted,
```
cd WriteVTU/build 
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
./WriteVTU
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

