[VTKExamples](/home/)/[Cxx](/Cxx)/Picking/CellPicking

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Picking/TestCellPicking.png?raw=true" width="256" />

### Description
This example demonstrates how to get the coordinates of the point on an actor that is clicked with the left mouse button. It also indicates which cell the selected point belongs to by highlighting the edges of that cell.

**CellPicking.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkIdTypeArray.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPlaneSource.h>
#include <vtkCellPicker.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkObjectFactory.h>

// Catch mouse events
class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
  public:
  static MouseInteractorStyle* New();

  MouseInteractorStyle()
  {
    selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    selectedActor = vtkSmartPointer<vtkActor>::New();
  }

    virtual void OnLeftButtonDown()
    {
      // Get the location of the click (in window coordinates)
      int* pos = this->GetInteractor()->GetEventPosition();

      vtkSmartPointer<vtkCellPicker> picker =
        vtkSmartPointer<vtkCellPicker>::New();
      picker->SetTolerance(0.0005);

      // Pick from this location.
      picker->Pick(pos[0], pos[1], 0, this->GetDefaultRenderer());

      double* worldPosition = picker->GetPickPosition();
      std::cout << "Cell id is: " << picker->GetCellId() << std::endl;

      if(picker->GetCellId() != -1)
      {

        std::cout << "Pick position is: " << worldPosition[0] << " " << worldPosition[1]
                  << " " << worldPosition[2] << endl;

        vtkSmartPointer<vtkIdTypeArray> ids =
          vtkSmartPointer<vtkIdTypeArray>::New();
        ids->SetNumberOfComponents(1);
        ids->InsertNextValue(picker->GetCellId());

        vtkSmartPointer<vtkSelectionNode> selectionNode =
          vtkSmartPointer<vtkSelectionNode>::New();
        selectionNode->SetFieldType(vtkSelectionNode::CELL);
        selectionNode->SetContentType(vtkSelectionNode::INDICES);
        selectionNode->SetSelectionList(ids);

        vtkSmartPointer<vtkSelection> selection =
          vtkSmartPointer<vtkSelection>::New();
        selection->AddNode(selectionNode);

        vtkSmartPointer<vtkExtractSelection> extractSelection =
          vtkSmartPointer<vtkExtractSelection>::New();
#if VTK_MAJOR_VERSION <= 5
        extractSelection->SetInput(0, this->Data);
        extractSelection->SetInput(1, selection);
#else
        extractSelection->SetInputData(0, this->Data);
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


#if VTK_MAJOR_VERSION <= 5
        selectedMapper->SetInputConnection(
          selected->GetProducerPort());
#else
        selectedMapper->SetInputData(selected);
#endif

        selectedActor->SetMapper(selectedMapper);
        selectedActor->GetProperty()->EdgeVisibilityOn();
        selectedActor->GetProperty()->SetEdgeColor(1,0,0);
        selectedActor->GetProperty()->SetLineWidth(3);

        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(selectedActor);

      }
      // Forward events
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

    vtkSmartPointer<vtkPolyData> Data;
    vtkSmartPointer<vtkDataSetMapper> selectedMapper;
    vtkSmartPointer<vtkActor> selectedActor;

};

vtkStandardNewMacro(MouseInteractorStyle);

int main (int, char *[])
{
  vtkSmartPointer<vtkPlaneSource> planeSource =
    vtkSmartPointer<vtkPlaneSource>::New();
  planeSource->Update();

  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(planeSource->GetOutputPort());
  triangleFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(triangleFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->SetColor(0,1,0); //green
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  // Set the custom stype to use for interaction.
  vtkSmartPointer<MouseInteractorStyle> style =
    vtkSmartPointer<MouseInteractorStyle>::New();
  style->SetDefaultRenderer(renderer);
  style->Data = triangleFilter->GetOutput();

  renderWindowInteractor->SetInteractorStyle(style);

  renderer->AddActor(actor);
  renderer->ResetCamera();

  renderer->SetBackground(0,0,1); // Blue

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CellPicking)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CellPicking MACOSX_BUNDLE CellPicking.cxx)
 
target_link_libraries(CellPicking ${VTK_LIBRARIES})
```

**Download and Build CellPicking**

Click [here to download CellPicking](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CellPicking.tar) and its *CMakeLists.txt* file.
Once the *tarball CellPicking.tar* has been downloaded and extracted,
```
cd CellPicking/build 
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
./CellPicking
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

