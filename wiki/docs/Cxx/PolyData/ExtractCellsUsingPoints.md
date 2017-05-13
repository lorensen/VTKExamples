[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ExtractCellsUsingPoints

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestExtractCellsUsingPoints.png?raw=true" width="256" />

**ExtractCellsUsingPoints.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkInformation.h>
#include <vtkSphereSource.h>
#include <vtkExtractSelection.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkIdTypeArray.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfPoints()
            << " input points." << std::endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfCells()
            << " input cells." << std::endl;

  vtkSmartPointer<vtkIdTypeArray> ids =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids->SetNumberOfComponents(1);

  // Set values

  for(vtkIdType i = 0; i < sphereSource->GetOutput()->GetNumberOfPoints()-15; i++)
  {
    ids->InsertNextValue(i);
  }

  vtkSmartPointer<vtkSelectionNode> selectionNode =
    vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode->SetFieldType(vtkSelectionNode::POINT);
  selectionNode->SetContentType(vtkSelectionNode::INDICES);
  selectionNode->SetSelectionList(ids);
  selectionNode->GetProperties()->Set(vtkSelectionNode::CONTAINING_CELLS(), 1);

  vtkSmartPointer<vtkSelection> selection =
    vtkSmartPointer<vtkSelection>::New();
  selection->AddNode(selectionNode);

  vtkSmartPointer<vtkExtractSelection> extractSelection =
    vtkSmartPointer<vtkExtractSelection>::New();

  extractSelection->SetInputConnection(0, sphereSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  extractSelection->SetInput(1, selection);
#else
  extractSelection->SetInputData(1, selection);
#endif
  extractSelection->Update();

  // In selection
  vtkSmartPointer<vtkUnstructuredGrid> selected =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  selected->ShallowCopy(extractSelection->GetOutput());

  std::cout << "There are " << selected->GetNumberOfPoints()
            << " points in the selection." << std::endl;
  std::cout << "There are " << selected->GetNumberOfCells()
            << " cells in the selection." << std::endl;

  // Get points that are NOT in the selection
  selectionNode->GetProperties()->Set(vtkSelectionNode::INVERSE(), 1); //invert the selection
  extractSelection->Update();

  vtkSmartPointer<vtkUnstructuredGrid> notSelected =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  notSelected->ShallowCopy(extractSelection->GetOutput());

  std::cout << "There are " << notSelected->GetNumberOfPoints()
            << " points NOT in the selection." << std::endl;
  std::cout << "There are " << notSelected->GetNumberOfCells()
            << " cells NOT in the selection." << std::endl;

  vtkSmartPointer<vtkDataSetMapper> inputMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  inputMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);

  vtkSmartPointer<vtkDataSetMapper> selectedMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  selectedMapper->SetInputConnection(selected->GetProducerPort());
#else
  selectedMapper->SetInputData(selected);
#endif
  vtkSmartPointer<vtkActor> selectedActor =
    vtkSmartPointer<vtkActor>::New();
  selectedActor->SetMapper(selectedMapper);

  vtkSmartPointer<vtkDataSetMapper> notSelectedMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  notSelectedMapper->SetInputConnection(notSelected->GetProducerPort());
#else
  notSelectedMapper->SetInputData(notSelected);
#endif
  vtkSmartPointer<vtkActor> notSelectedActor =
    vtkSmartPointer<vtkActor>::New();
  notSelectedActor->SetMapper(notSelectedMapper);

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double centerViewport[4] = {0.33, 0.0, .66, 1.0};
  double rightViewport[4] = {0.66, 0.0, 1.0, 1.0};

  // Setup the renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> centerRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(centerRenderer);
  centerRenderer->SetViewport(centerViewport);
  centerRenderer->SetBackground(.3, .1, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(inputActor);
  centerRenderer->AddActor(selectedActor);
  rightRenderer->AddActor(notSelectedActor);

  leftRenderer->ResetCamera();
  centerRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractCellsUsingPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractCellsUsingPoints MACOSX_BUNDLE ExtractCellsUsingPoints.cxx)
 
target_link_libraries(ExtractCellsUsingPoints ${VTK_LIBRARIES})
```

**Download and Build ExtractCellsUsingPoints**

Click [here to download ExtractCellsUsingPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractCellsUsingPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractCellsUsingPoints.tar* has been downloaded and extracted,
```
cd ExtractCellsUsingPoints/build 
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
./ExtractCellsUsingPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

