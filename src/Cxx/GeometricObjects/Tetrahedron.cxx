#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkTetra.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkCellType.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char*[])
{
  vtkSmartPointer< vtkPoints > points =
    vtkSmartPointer< vtkPoints > :: New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(1, 1, 0);
  points->InsertNextPoint(0, 1, 1);
  points->InsertNextPoint(5, 5, 5);
  points->InsertNextPoint(6, 5, 5);
  points->InsertNextPoint(6, 6, 5);
  points->InsertNextPoint(5, 6, 6);
  
  // Method 1
  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid1 =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid1->SetPoints(points);
  
  vtkIdType ptIds[] = {0, 1, 2, 3};
  unstructuredGrid1->InsertNextCell( VTK_TETRA, 4, ptIds );
  
  // Method 2
  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid2 =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid2->SetPoints(points);
  
  vtkSmartPointer<vtkTetra> tetra =
    vtkSmartPointer<vtkTetra>::New();

  tetra->GetPointIds()->SetId(0, 4);
  tetra->GetPointIds()->SetId(1, 5);
  tetra->GetPointIds()->SetId(2, 6);
  tetra->GetPointIds()->SetId(3, 7);
  
  vtkSmartPointer<vtkCellArray> cellArray =
    vtkSmartPointer<vtkCellArray>::New();
  cellArray->InsertNextCell(tetra);
  unstructuredGrid2->SetCells(VTK_TETRA, cellArray);

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper1 = 
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper1->SetInputConnection(unstructuredGrid1->GetProducerPort());
#else
  mapper1->SetInputData(unstructuredGrid1);
#endif
 
  vtkSmartPointer<vtkActor> actor1 = 
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);
  
  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper2 = 
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper2->SetInputConnection(unstructuredGrid2->GetProducerPort());
#else
  mapper2->SetInputData(unstructuredGrid2);
#endif
 
  vtkSmartPointer<vtkActor> actor2 = 
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
 
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actor to the scene
  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
   
  return EXIT_SUCCESS;
}
