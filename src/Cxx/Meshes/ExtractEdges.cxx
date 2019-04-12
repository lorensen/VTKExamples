#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkExtractEdges.h>
#include <vtkSphereSource.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLine.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  std::cout << "Sphere" << endl << "----------" << endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfCells() << " cells." << std::endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfPoints() << " points." << std::endl;

  vtkSmartPointer<vtkExtractEdges> extractEdges =
    vtkSmartPointer<vtkExtractEdges>::New();
  extractEdges->SetInputConnection(sphereSource->GetOutputPort());
  extractEdges->Update();

  vtkCellArray* lines= extractEdges->GetOutput()->GetLines();
  vtkPoints* points = extractEdges->GetOutput()->GetPoints();

  std::cout << std::endl << "Edges" << endl << "----------" << std::endl;
  std::cout << "There are " << lines->GetNumberOfCells() << " cells." << std::endl;
  std::cout << "There are " << points->GetNumberOfPoints() << " points." << std::endl;

  // Traverse all of the edges
  for(vtkIdType i = 0; i < extractEdges->GetOutput()->GetNumberOfCells(); i++)
  {
    //std::cout << "Type: " << extractEdges->GetOutput()->GetCell(i)->GetClassName() << std::endl;
    vtkSmartPointer<vtkLine> line = dynamic_cast<vtkLine*>(extractEdges->GetOutput()->GetCell(i));
    std::cout << "Line " << i << " : " << *line << std::endl;
  }

  // Visualize the edges

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(extractEdges->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
