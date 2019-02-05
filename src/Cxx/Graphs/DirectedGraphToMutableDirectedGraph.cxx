#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkDirectedGraph.h>

int main (int, char *[])
{

  //create a graph
  vtkSmartPointer<vtkMutableDirectedGraph> mdg =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  //add 4 vertices to the graph
  vtkIdType v1 = mdg->AddVertex();
  vtkIdType v2 = mdg->AddVertex();
  vtkIdType v3 = mdg->AddVertex();
  vtkIdType v4 = mdg->AddVertex();

  //add 3 edges to the graph
  mdg->AddEdge ( v1, v2 );
  mdg->AddEdge ( v1, v3 );
  mdg->AddEdge ( v1, v4 );

  //create 4 points - one for each vertex
  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 2.0);

  //add the coordinates of the points to the graph
  mdg->SetPoints(points);

  std::cout << "MDG: " << std::endl;
  std::cout << "Type: " << mdg->GetClassName() << std::endl;
  std::cout << "Vertices: " << mdg->GetNumberOfVertices() << std::endl;
  std::cout << "Edges: " << mdg->GetNumberOfEdges() << std::endl;

  vtkSmartPointer<vtkDirectedGraph> dg =
      vtkSmartPointer<vtkDirectedGraph>::New();
  if(!dg->CheckedShallowCopy(mdg))
  {
    std::cerr << "Could not convert graph to tree!" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "DG: " << std::endl;
  std::cout << "Type: " << dg->GetClassName() << std::endl;
  std::cout << "Vertices: " << dg->GetNumberOfVertices() << std::endl;
  std::cout << "Edges: " << dg->GetNumberOfEdges() << std::endl;

  vtkSmartPointer<vtkMutableDirectedGraph> mdg2 =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  if(!mdg2->CheckedShallowCopy(dg))
  {
    std::cerr << "Could not convert graph to tree!" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "MDG2: " << std::endl;
  std::cout << "Type: " << mdg2->GetClassName() << std::endl;
  std::cout << "Vertices: " << mdg2->GetNumberOfVertices() << std::endl;
  std::cout << "Edges: " << mdg2->GetNumberOfEdges() << std::endl;

  return EXIT_SUCCESS;
}
