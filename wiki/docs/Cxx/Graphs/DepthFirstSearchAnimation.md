[VTKExamples](/home/)/[Cxx](/Cxx)/Graphs/DepthFirstSearchAnimation

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Graphs/TestDepthFirstSearchAnimation.png?raw=true" width="256" />

**DepthFirstSearchAnimation.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkCommand.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphLayoutView.h>
#include <vtkIntArray.h>
#include <vtkLookupTable.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRendererCollection.h>
#include <vtkTree.h>
#include <vtkTreeDFSIterator.h>
#include <vtkUnsignedCharArray.h>
#include <vtkViewTheme.h>

class vtkTimerCallback : public vtkCommand
{
public:
  static vtkTimerCallback *New()
  {
    vtkTimerCallback *cb = new vtkTimerCallback;
    return cb;
  }
  virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
                         void *vtkNotUsed(callData))
  {
    if (eventId != vtkCommand::TimerEvent)
    {
      return;
    }

    if(this->DFS->HasNext())
    {
      vtkIdType nextVertex = this->DFS->Next();
      std::cout << "Next vertex: " << nextVertex << std::endl;
      vtkIntArray::SafeDownCast(
        this->Tree->GetVertexData()->GetArray("color"))->SetValue(nextVertex, 10);
      this->Tree->Modified();
      this->GraphLayoutView->AddRepresentationFromInput(this->Tree);
      this->GraphLayoutView->Render();
    }
  }

  void SetDFS(vtkTreeDFSIterator *dfs) {this->DFS = dfs;}
  void SetTree(vtkTree *tree) {this->Tree = tree;}
  void SetGraphLayoutView(vtkGraphLayoutView *view) {this->GraphLayoutView = view;}

private:
  vtkTreeDFSIterator *DFS;
  vtkTree            *Tree;
  vtkGraphLayoutView *GraphLayoutView;
};

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableDirectedGraph> graph =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  // Create a tree
  vtkIdType v1 = graph->AddVertex();
  vtkIdType v2 = graph->AddChild(v1);
  graph->AddChild(v1);
  graph->AddChild(v2);

  vtkSmartPointer<vtkTree> tree =
    vtkSmartPointer<vtkTree>::New();
  tree->CheckedShallowCopy(graph);

  // Create the color array
  vtkSmartPointer<vtkIntArray> vertexColors =
    vtkSmartPointer<vtkIntArray>::New();
  vertexColors->SetNumberOfComponents(1);
  vertexColors->SetName("color");

  vtkSmartPointer<vtkLookupTable> lookupTable =
    vtkSmartPointer<vtkLookupTable>::New();

  lookupTable->SetTableRange(0.0, 10.0);
  lookupTable->Build();

  for(vtkIdType i = 0; i < tree->GetNumberOfVertices(); i++)
  {
    vertexColors->InsertNextValue(0);
  }

  // Add the color array to the tree
  tree->GetVertexData()->AddArray(vertexColors);

  // Create a depth first search iterator
  vtkSmartPointer<vtkTreeDFSIterator> DFS =
    vtkSmartPointer<vtkTreeDFSIterator>::New();
  vtkIdType root = tree->GetRoot();
  DFS->SetStartVertex(root);
  DFS->SetTree(tree);

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(tree);
  graphLayoutView->SetLayoutStrategyToTree();

  graphLayoutView->SetVertexColorArrayName("color");
  graphLayoutView->ColorVerticesOn();

  vtkSmartPointer<vtkViewTheme> theme =
    vtkSmartPointer<vtkViewTheme>::New();
  theme->SetPointLookupTable(lookupTable);
  theme->ScalePointLookupTableOff();

  graphLayoutView->ApplyViewTheme(theme);
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();

  // Sign up to receive TimerEvent
  vtkSmartPointer<vtkTimerCallback> cb =
    vtkSmartPointer<vtkTimerCallback>::New();
  cb->SetDFS(DFS);
  cb->SetTree(tree);
  cb->SetGraphLayoutView(graphLayoutView);

  graphLayoutView->GetInteractor()->CreateRepeatingTimer(1000);
  graphLayoutView->GetInteractor()->AddObserver(vtkCommand::TimerEvent, cb);

  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DepthFirstSearchAnimation)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DepthFirstSearchAnimation MACOSX_BUNDLE DepthFirstSearchAnimation.cxx)
 
target_link_libraries(DepthFirstSearchAnimation ${VTK_LIBRARIES})
```

**Download and Build DepthFirstSearchAnimation**

Click [here to download DepthFirstSearchAnimation](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DepthFirstSearchAnimation.tar) and its *CMakeLists.txt* file.
Once the *tarball DepthFirstSearchAnimation.tar* has been downloaded and extracted,
```
cd DepthFirstSearchAnimation/build 
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
./DepthFirstSearchAnimation
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

