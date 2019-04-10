#include <vtkSmartPointer.h>
#include <vtkAnnotationLink.h>
#include <vtkRenderedGraphRepresentation.h>
#include <vtkRenderer.h>
#include <vtkHardwareSelector.h>
#include <vtkDoubleArray.h>
#include <vtkSelectionNode.h>
#include <vtkIdTypeArray.h>
#include <vtkSelection.h>
#include <vtkRenderWindow.h>
#include <vtkUnsignedCharArray.h>
#include <vtkObjectFactory.h>
#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkGraphWriter.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>
#include <vtkInteractorStyleRubberBand2D.h>

class RubberBandStyle : public vtkInteractorStyleRubberBand2D
{
  public:
    static RubberBandStyle* New();
    vtkTypeMacro(RubberBandStyle, vtkInteractorStyleRubberBand2D);

  virtual void OnLeftButtonUp()
  {
    // Forward events
    vtkInteractorStyleRubberBand2D::OnLeftButtonUp();

    vtkSelection* selection = this->View->GetRepresentation()->GetAnnotationLink()->GetCurrentSelection();
    vtkSelectionNode* vertices;
    vtkSelectionNode* edges;
    if(selection->GetNode(0)->GetFieldType() == vtkSelectionNode::VERTEX)
    {
      vertices = selection->GetNode(0);
    }
    else if(selection->GetNode(0)->GetFieldType() == vtkSelectionNode::EDGE)
    {
      edges = selection->GetNode(0);
    }

    if(selection->GetNode(1)->GetFieldType() == vtkSelectionNode::VERTEX)
    {
      vertices = selection->GetNode(1);
    }
    else if(selection->GetNode(1)->GetFieldType() == vtkSelectionNode::EDGE)
    {
      edges = selection->GetNode(1);
    }

    vtkIdTypeArray* vertexList = dynamic_cast<vtkIdTypeArray*>(vertices->GetSelectionList());
    std::cout << "There are " << vertexList->GetNumberOfTuples() << " vertices selected." << std::endl;

    if(vertexList->GetNumberOfTuples() > 0)
    {
      std::cout << "Vertex Ids: ";
    }
    for(vtkIdType i = 0; i < vertexList->GetNumberOfTuples(); i++)
    {
      std::cout << vertexList->GetValue(i) << " ";
    }

    std::cout << std::endl;
    vtkIdTypeArray* edgeList = dynamic_cast<vtkIdTypeArray*>(edges->GetSelectionList());
    std::cout << "There are " << edgeList->GetNumberOfTuples() << " edges selected." << std::endl;
    if(edgeList->GetNumberOfTuples() > 0)
    {
      std::cout << "Edge Ids: ";
    }

    for(vtkIdType i = 0; i < edgeList->GetNumberOfTuples(); i++)
    {
      std::cout << edgeList->GetValue(i) << " ";
    }
    std::cout << std::endl;
  }

  vtkGraphLayoutView* View;
};
vtkStandardNewMacro(RubberBandStyle);


int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v2);

  vtkSmartPointer<vtkGraphLayoutView> view =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  view->AddRepresentationFromInput(g);
  view->SetLayoutStrategy("Simple 2D");

  vtkSmartPointer<RubberBandStyle> style =
    vtkSmartPointer<RubberBandStyle>::New();
  style->View = view;
  view->SetInteractorStyle(style);

  view->ResetCamera();
  view->Render();

  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
