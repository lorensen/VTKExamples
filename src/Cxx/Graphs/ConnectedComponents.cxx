#include <vtkSmartPointer.h>

#include <vtkBoostConnectedComponents.h>
#include <vtkDataArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraph.h>
#include <vtkIntArray.h>
#include <vtkMutableUndirectedGraph.h>

int main ( int, char *[] )
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  vtkIdType v4 = g->AddVertex();

  g->AddEdge ( v1, v2 );
  g->AddEdge ( v3, v4 );

  vtkSmartPointer<vtkBoostConnectedComponents> connectedComponents =
    vtkSmartPointer<vtkBoostConnectedComponents>::New();
  connectedComponents->SetInput(g);
  connectedComponents->Update();

  vtkGraph* outputGraph = connectedComponents->GetOutput();

  vtkIntArray* components = dynamic_cast<vtkIntArray*>(
    outputGraph->GetVertexData()->GetArray("component"));

  for(vtkIdType i = 0; i < components->GetNumberOfTuples(); i++)
  {
    int val = components->GetValue(i);
    std::cout << val << std::endl;
  }

  return EXIT_SUCCESS;
}
