[VTKExamples](Home)/[Cxx](Cxx)/Meshes/FillHoles

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Meshes/TestFillHoles.png" width="256" />

### Description
This filter finds holes in a mesh and closes them. 

**FillHoles.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkSelectionNode.h>
#include <vtkInformation.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkPointData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkIdTypeArray.h>
#include <vtkExtractSelection.h>
#include <vtkDataSetSurfaceFilter.h>

#include <vtkFillHolesFilter.h>

static void GenerateData(vtkPolyData*);

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> input =
    vtkSmartPointer<vtkPolyData>::New();
  if(argc == 1)
  {
    GenerateData(input);
  }
  else
  {
    std::string inputFilename = argv[1];

    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    input->ShallowCopy(reader->GetOutput());
  }

  vtkSmartPointer<vtkFillHolesFilter> fillHolesFilter =
    vtkSmartPointer<vtkFillHolesFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  fillHolesFilter->SetInputConnection(input->GetProducerPort());
#else
  fillHolesFilter->SetInputData(input);
#endif
  fillHolesFilter->SetHoleSize(1000.0);

  // Make the triangle windong order consistent
  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(fillHolesFilter->GetOutputPort());
  normals->ConsistencyOn();
  normals->SplittingOff();
  normals->Update();

  // Restore the original normals
  normals->GetOutput()->GetPointData()->
    SetNormals(input->GetPointData()->GetNormals());

  // Visualize
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  originalMapper->SetInputConnection(input->GetProducerPort());
#else
  originalMapper->SetInputData(input);
#endif

  vtkSmartPointer<vtkProperty> backfaceProp =
    vtkSmartPointer<vtkProperty>::New();
  backfaceProp->SetDiffuseColor(0.89,0.81,0.34);

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->SetBackfaceProperty(backfaceProp);
  originalActor->GetProperty()->SetDiffuseColor(1.0, 0.3882, 0.2784);

  vtkSmartPointer<vtkPolyDataMapper> filledMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  filledMapper->SetInputConnection(normals->GetOutputPort());

  vtkSmartPointer<vtkActor> filledActor =
    vtkSmartPointer<vtkActor>::New();
  filledActor->SetMapper(filledMapper);
  filledActor->GetProperty()->SetDiffuseColor(1.0, 0.3882, 0.2784);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  leftRenderer->SetViewport(leftViewport);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  rightRenderer->SetViewport(rightViewport);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600,300);

  renderWindow->AddRenderer(leftRenderer);
  renderWindow->AddRenderer(rightRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  leftRenderer->AddActor(originalActor);
  rightRenderer->AddActor(filledActor);
  leftRenderer->SetBackground(.3, .6, .3); // Background color green

  leftRenderer->GetActiveCamera()->SetPosition(0, -1, 0);
  leftRenderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  leftRenderer->GetActiveCamera()->SetViewUp(0, 0, 1);
  leftRenderer->GetActiveCamera()->Azimuth(30);
  leftRenderer->GetActiveCamera()->Elevation(30);

  leftRenderer->ResetCamera();

  rightRenderer->SetBackground(.5, .6, .1); // Background color green

  // Share the camera

  rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());
  // Render and interact
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void GenerateData(vtkPolyData* input)
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Remove some cells
  vtkSmartPointer<vtkIdTypeArray> ids =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids->SetNumberOfComponents(1);

  // Set values
  ids->InsertNextValue(2);
  ids->InsertNextValue(10);

  vtkSmartPointer<vtkSelectionNode> selectionNode =
    vtkSmartPointer<vtkSelectionNode>::New();
  selectionNode->SetFieldType(vtkSelectionNode::CELL);
  selectionNode->SetContentType(vtkSelectionNode::INDICES);
  selectionNode->SetSelectionList(ids);
  selectionNode->GetProperties()->Set(vtkSelectionNode::INVERSE(), 1); //invert the selection

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
  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(extractSelection->GetOutputPort());
  surfaceFilter->Update();

  input->ShallowCopy(surfaceFilter->GetOutput());
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FillHoles)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FillHoles MACOSX_BUNDLE FillHoles.cxx)
 
target_link_libraries(FillHoles ${VTK_LIBRARIES})
```

**Download and Build FillHoles**

Click [here to download FillHoles](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FillHoles.tar) and its *CMakeLists.txt* file.
Once the *tarball FillHoles.tar* has been downloaded and extracted,
```
cd FillHoles/build 
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
./FillHoles
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

