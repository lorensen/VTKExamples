#include <vtkSmartPointer.h>
#include <vtkRenderedGraphRepresentation.h>
#include <vtkFloatArray.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphWriter.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetAttributes.h>
#include <vtkGraphToGlyphs.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g =
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();

  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();

  g->AddEdge(v1, v2);
  g->AddEdge(v1, v2);

  vtkSmartPointer<vtkFloatArray> scales =
    vtkSmartPointer<vtkFloatArray>::New();
  scales->SetNumberOfComponents(1);
  scales->SetName("Scales");
  scales->InsertNextValue(1.0);
  scales->InsertNextValue(4.0);

  g->GetVertexData()->AddArray(scales);
 
  vtkSmartPointer<vtkGraphLayoutView> layoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  layoutView->AddRepresentationFromInput(g);
  layoutView->ScaledGlyphsOn();
  layoutView->SetScalingArrayName("Scales");
  dynamic_cast<vtkRenderedGraphRepresentation*>(layoutView->GetRepresentation())
            ->SetGlyphType(vtkGraphToGlyphs::CIRCLE);
  layoutView->ResetCamera();
  layoutView->Render();
  layoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
