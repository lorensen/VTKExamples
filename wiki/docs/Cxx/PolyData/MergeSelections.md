[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/MergeSelections

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestMergeSelections.png?raw=true" width="256" />

### Description
* Fixed by Mirko Heuegger

**MergeSelections.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkInformation.h>
#include <vtkPointSource.h>
#include <vtkExtractSelection.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkIdTypeArray.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(50);
  pointSource->Update();

  std::cout << "There are " << pointSource->GetOutput()->GetNumberOfPoints()
            << " input points." << std::endl;

  vtkSmartPointer<vtkIdTypeArray> ids1 =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids1->SetNumberOfComponents(1);

  // Set values
  for(unsigned int i = 10; i < 20; i++)
  {
    ids1->InsertNextValue(i);
  }

  vtkSmartPointer<vtkIdTypeArray> ids2 =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids2->SetNumberOfComponents(1);

  for(unsigned int i = 15; i < 30; i++)
  {
    ids2->InsertNextValue(i);
  }

  vtkSmartPointer<vtkSelectionNode> selectionNode1 =
    vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode1->SetFieldType(vtkSelectionNode::POINT);
  selectionNode1->SetContentType(vtkSelectionNode::INDICES);
  selectionNode1->SetSelectionList(ids1);

  vtkSmartPointer<vtkSelectionNode> selectionNode2 =
    vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode2->SetFieldType(vtkSelectionNode::POINT);
  selectionNode2->SetContentType(vtkSelectionNode::INDICES);
  selectionNode2->SetSelectionList(ids2);

  vtkSmartPointer<vtkSelection> selection1 =
    vtkSmartPointer<vtkSelection>::New();
  selection1->AddNode(selectionNode1);

  vtkSmartPointer<vtkSelection> selection2 =
    vtkSmartPointer<vtkSelection>::New();
  selection2->AddNode(selectionNode2);

  vtkSmartPointer<vtkSelection> selectionCombined =
    vtkSmartPointer<vtkSelection>::New();
  selectionCombined->AddNode(selectionNode1);
  selectionCombined->Union(selectionNode2);

  std::cout << "There are " << selectionCombined->GetNumberOfNodes() << " nodes." << std::endl;

  vtkSmartPointer<vtkExtractSelection> extractSelection1 =
    vtkSmartPointer<vtkExtractSelection>::New();
  extractSelection1->SetInputConnection(0, pointSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  extractSelection1->SetInput(1, selection1);
#else
  extractSelection1->SetInputData(1, selection1);
#endif
  extractSelection1->Update();

  vtkSmartPointer<vtkExtractSelection> extractSelection2 =
    vtkSmartPointer<vtkExtractSelection>::New();
  extractSelection2->SetInputConnection(0, pointSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  extractSelection2->SetInput(1, selection2);
#else
  extractSelection2->SetInputData(1, selection2);
#endif
  extractSelection2->Update();

  vtkSmartPointer<vtkExtractSelection> extractSelectionCombined =
    vtkSmartPointer<vtkExtractSelection>::New();
  extractSelectionCombined->SetInputConnection(0, pointSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  extractSelectionCombined->SetInput(1, selectionCombined);
#else
  extractSelectionCombined->SetInputData(1, selectionCombined);
#endif
  extractSelectionCombined->Update();

  // In selection
  vtkDataSet* ds = vtkDataSet::SafeDownCast(extractSelectionCombined->GetOutput());
  std::cout << "There are " << ds->GetNumberOfPoints() << " points in the selection." << std::endl;
  std::cout << "There are " << ds->GetNumberOfCells() << " cells in the selection." << std::endl;

  /*
  // Not in selection
  selectionNode1->GetProperties()->Set(vtkSelectionNode::INVERSE(), 1); //invert the selection
  selectionNode2->GetProperties()->Set(vtkSelectionNode::INVERSE(), 1); //invert the selection
  extractSelection->Update();
  std::cout << "There are " << vtkDataSet::SafeDownCast (extractSelection->GetOutput())->GetNumberOfPoints()
            << " points not in the selection." << std::endl;
  */

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapperOriginal =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperOriginal->SetInputConnection(pointSource->GetOutputPort());
  mapperOriginal->ScalarVisibilityOff();

  vtkSmartPointer<vtkDataSetMapper> mapper1 =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper1->SetInputConnection(extractSelection1->GetOutputPort());
  mapper1->ScalarVisibilityOff();

  vtkSmartPointer<vtkDataSetMapper> mapper2 =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper2->SetInputConnection(extractSelection2->GetOutputPort());
  mapper2->ScalarVisibilityOff();

  vtkSmartPointer<vtkDataSetMapper> mapperCombined =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapperCombined->SetInputConnection(extractSelectionCombined->GetOutputPort());
  mapperCombined->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(mapperOriginal);

  vtkSmartPointer<vtkActor> actor1 =
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);

  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);

  vtkSmartPointer<vtkActor> actorCombined =
    vtkSmartPointer<vtkActor>::New();
  actorCombined->SetMapper(mapperCombined);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(1000,250);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  double originalViewport[4] = {0.0, 0.0, 0.25, 1.0};
  double selection1Viewport[4] = {0.25, 0.0, 0.5, 1.0};
  double selection2Viewport[4] = {0.5, 0.0, 0.75, 1.0};
  double selectionCombinedViewport[4] = {0.75, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);

  vtkSmartPointer<vtkRenderer> selection1Renderer =
    vtkSmartPointer<vtkRenderer>::New();
  selection1Renderer->SetViewport(selection1Viewport);

  vtkSmartPointer<vtkRenderer> selection2Renderer =
    vtkSmartPointer<vtkRenderer>::New();
  selection2Renderer->SetViewport(selection2Viewport);

  vtkSmartPointer<vtkRenderer> selectionCombinedRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  selectionCombinedRenderer->SetViewport(selectionCombinedViewport);

  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(selection1Renderer);
  renderWindow->AddRenderer(selection2Renderer);
  renderWindow->AddRenderer(selectionCombinedRenderer);

  originalRenderer->AddActor(originalActor);
  selection1Renderer->AddActor(actor1);
  selection2Renderer->AddActor(actor2);
  selectionCombinedRenderer->AddActor(actorCombined);
  //renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MergeSelections)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MergeSelections MACOSX_BUNDLE MergeSelections.cxx)
 
target_link_libraries(MergeSelections ${VTK_LIBRARIES})
```

**Download and Build MergeSelections**

Click [here to download MergeSelections](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MergeSelections.tar) and its *CMakeLists.txt* file.
Once the *tarball MergeSelections.tar* has been downloaded and extracted,
```
cd MergeSelections/build 
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
./MergeSelections
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

