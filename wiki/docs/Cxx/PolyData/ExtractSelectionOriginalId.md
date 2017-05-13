[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/ExtractSelectionOriginalId

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestExtractSelectionOriginalId.png?raw=true" width="256" />

**ExtractSelectionOriginalId.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkIdTypeArray.h>
#include <vtkInformation.h>
#include <vtkPointSource.h>
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
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(50);
  pointSource->Update();

  std::cout << "There are " << pointSource->GetOutput()->GetNumberOfPoints()
            << " input points." << std::endl;

  vtkSmartPointer<vtkIdTypeArray> ids =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids->SetNumberOfComponents(1);

  //set values
  for(unsigned int i = 10; i < 20; i++)
  {
    ids->InsertNextValue(i);
  }

  vtkSmartPointer<vtkSelectionNode> selectionNode =
      vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode->SetFieldType(vtkSelectionNode::POINT);
  selectionNode->SetContentType(vtkSelectionNode::INDICES);
  selectionNode->SetSelectionList(ids);

  vtkSmartPointer<vtkSelection> selection =
      vtkSmartPointer<vtkSelection>::New();
  selection->AddNode(selectionNode);

  vtkSmartPointer<vtkExtractSelection> extractSelection =
      vtkSmartPointer<vtkExtractSelection>::New();

  extractSelection->SetInputConnection(0, pointSource->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
  extractSelection->SetInput(1, selection);
#else
  extractSelection->SetInputData(1, selection);
#endif
  extractSelection->Update();

  //in selection
  vtkSmartPointer<vtkUnstructuredGrid> selected =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  selected->ShallowCopy(extractSelection->GetOutput());

  std::cout << "There are " << selected->GetNumberOfPoints()
            << " points in the selection." << std::endl;

  selected->Print(std::cout);

  vtkIdTypeArray* originalIds = vtkIdTypeArray::SafeDownCast(selected->GetPointData()->GetArray("vtkOriginalPointIds"));

  for(vtkIdType i = 0; i < originalIds->GetNumberOfTuples(); i++)
  {
    std::cout << "Point " << i << " was originally point " << originalIds->GetValue(i) << std::endl;
  }

  for(vtkIdType i = 0; i < originalIds->GetNumberOfTuples(); i++)
  {
    vtkIdType query = originalIds->GetValue(i);
    for(vtkIdType j = 0; j < originalIds->GetNumberOfTuples(); j++)
    {
      if(originalIds->GetValue(j) == query)
      {
        std::cout << "Original point " << query << " is now " << j << std::endl;
      }
    }
  }

  vtkSmartPointer<vtkDataSetMapper> inputMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  inputMapper->SetInputConnection(pointSource->GetOutputPort());
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
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup the renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(selectedActor);

  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractSelectionOriginalId)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractSelectionOriginalId MACOSX_BUNDLE ExtractSelectionOriginalId.cxx)
 
target_link_libraries(ExtractSelectionOriginalId ${VTK_LIBRARIES})
```

**Download and Build ExtractSelectionOriginalId**

Click [here to download ExtractSelectionOriginalId](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractSelectionOriginalId.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractSelectionOriginalId.tar* has been downloaded and extracted,
```
cd ExtractSelectionOriginalId/build 
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
./ExtractSelectionOriginalId
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

