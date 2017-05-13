[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/VertexConnectivity

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestVertexConnectivity.png?raw=true" width="256" />

### Description
The input must be only edges (i.e. vtkExtractEdges must be run).

**VertexConnectivity.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkIdList.h>
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkDataSet.h>
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>
#include <vtkExtractEdges.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkProperty.h>
#include <vtkVertexGlyphFilter.h>

vtkSmartPointer<vtkIdList> GetConnectedVertices(vtkSmartPointer<vtkPolyData> mesh, int id);

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
      vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(sphereSource->GetOutputPort());
  triangleFilter->Update();

  vtkSmartPointer<vtkExtractEdges> extractEdges =
    vtkSmartPointer<vtkExtractEdges>::New();
  extractEdges->SetInputConnection(triangleFilter->GetOutputPort());
  extractEdges->Update();

  vtkSmartPointer<vtkPolyData> mesh = extractEdges->GetOutput();

  vtkSmartPointer<vtkIdList> connectedVertices = GetConnectedVertices(mesh, 0);

  vtkSmartPointer<vtkIdTypeArray> ids =
    vtkSmartPointer<vtkIdTypeArray>::New();
  ids->SetNumberOfComponents(1);

  std::cout << "Connected vertices: ";
  for(vtkIdType i = 0; i < connectedVertices->GetNumberOfIds(); i++)
  {
    std::cout << connectedVertices->GetId(i) << " ";
    ids->InsertNextValue(connectedVertices->GetId(i));
  }
  std::cout << std::endl;

  vtkSmartPointer<vtkDataSetMapper> connectedVertexMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();

  {
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

    extractSelection->SetInputConnection(0, extractEdges->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
    extractSelection->SetInput(1, selection);
#else
    extractSelection->SetInputData(1, selection);
#endif
    extractSelection->Update();

    vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
      vtkSmartPointer<vtkVertexGlyphFilter>::New();
    glyphFilter->SetInputConnection(extractSelection->GetOutputPort());
    glyphFilter->Update();

    connectedVertexMapper->SetInputConnection(glyphFilter->GetOutputPort());
  }

  vtkSmartPointer<vtkActor> connectedVertexActor =
    vtkSmartPointer<vtkActor>::New();
  connectedVertexActor->SetMapper(connectedVertexMapper);
  connectedVertexActor->GetProperty()->SetColor(1,0,0);
  connectedVertexActor->GetProperty()->SetPointSize(5);

  vtkSmartPointer<vtkDataSetMapper> queryVertexMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();

  {
    vtkSmartPointer<vtkIdTypeArray> ids2 =
      vtkSmartPointer<vtkIdTypeArray>::New();
    ids2->SetNumberOfComponents(1);
    ids2->InsertNextValue(0);

    vtkSmartPointer<vtkSelectionNode> selectionNode =
      vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::POINT);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(ids2);

    vtkSmartPointer<vtkSelection> selection =
        vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    vtkSmartPointer<vtkExtractSelection> extractSelection =
        vtkSmartPointer<vtkExtractSelection>::New();

    extractSelection->SetInputConnection(0, extractEdges->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
    extractSelection->SetInput(1, selection);
#else
    extractSelection->SetInputData(1, selection);
#endif
    extractSelection->Update();

    vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
      vtkSmartPointer<vtkVertexGlyphFilter>::New();
    glyphFilter->SetInputConnection(extractSelection->GetOutputPort());
    glyphFilter->Update();

    queryVertexMapper->SetInputConnection(glyphFilter->GetOutputPort());
  }

  vtkSmartPointer<vtkActor> queryVertexActor =
    vtkSmartPointer<vtkActor>::New();
  queryVertexActor->SetMapper(queryVertexMapper);
  queryVertexActor->GetProperty()->SetColor(0,1,0);
  queryVertexActor->GetProperty()->SetPointSize(5);

  vtkSmartPointer<vtkDataSetMapper> sphereMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  sphereMapper->SetInputConnection(extractEdges->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

    //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actors to the scene
  renderer->AddActor(sphereActor);
  renderer->AddActor(queryVertexActor);
  renderer->AddActor(connectedVertexActor);
  renderer->SetBackground(.3, .2, .1); // Background color dark red

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

vtkSmartPointer<vtkIdList> GetConnectedVertices(vtkSmartPointer<vtkPolyData> mesh, int id)
{
  vtkSmartPointer<vtkIdList> connectedVertices =
      vtkSmartPointer<vtkIdList>::New();

  //get all cells that vertex 'id' is a part of
  vtkSmartPointer<vtkIdList> cellIdList =
      vtkSmartPointer<vtkIdList>::New();
  mesh->GetPointCells(id, cellIdList);

  /*
  cout << "Vertex 0 is used in cells ";
  for(vtkIdType i = 0; i < cellIdList->GetNumberOfIds(); i++)
    {
    cout << cellIdList->GetId(i) << ", ";
    }
  cout << endl;
  */

  for(vtkIdType i = 0; i < cellIdList->GetNumberOfIds(); i++)
  {
    //cout << "id " << i << " : " << cellIdList->GetId(i) << endl;

    vtkSmartPointer<vtkIdList> pointIdList =
      vtkSmartPointer<vtkIdList>::New();
    mesh->GetCellPoints(cellIdList->GetId(i), pointIdList);

    //cout << "End points are " << pointIdList->GetId(0) << " and " << pointIdList->GetId(1) << endl;

    if(pointIdList->GetId(0) != id)
    {
      //cout << "Connected to " << pointIdList->GetId(0) << endl;
      connectedVertices->InsertNextId(pointIdList->GetId(0));
    }
    else
    {
      //cout << "Connected to " << pointIdList->GetId(1) << endl;
      connectedVertices->InsertNextId(pointIdList->GetId(1));
    }
  }

  return connectedVertices;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VertexConnectivity)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VertexConnectivity MACOSX_BUNDLE VertexConnectivity.cxx)
 
target_link_libraries(VertexConnectivity ${VTK_LIBRARIES})
```

**Download and Build VertexConnectivity**

Click [here to download VertexConnectivity](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VertexConnectivity.tar) and its *CMakeLists.txt* file.
Once the *tarball VertexConnectivity.tar* has been downloaded and extracted,
```
cd VertexConnectivity/build 
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
./VertexConnectivity
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

