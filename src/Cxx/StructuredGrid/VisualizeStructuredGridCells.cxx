#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkMath.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShrinkFilter.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  unsigned int numi = 3;
  unsigned int numj = 4;
  unsigned int numk = 5;

  for(unsigned int k = 0; k < numk; k++)
  {
    for(unsigned int j = 0; j < numj; j++)
    {
      for(unsigned int i = 0; i < numi; i++)
      {
        points->InsertNextPoint(i, j, k);
      }
    }
  }

  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(numi, numj, numk);
  structuredGrid->SetPoints(points);

  std::cout << "There are "
            << structuredGrid->GetNumberOfPoints() << " points before shrinking."
            << std::endl;
  std::cout << "There are "
            << structuredGrid->GetNumberOfCells() << " cells before shrinking."
            << std::endl;

  vtkSmartPointer<vtkShrinkFilter> shrinkFilter =
    vtkSmartPointer<vtkShrinkFilter>::New();
  shrinkFilter->SetInputData(structuredGrid);
  shrinkFilter->SetShrinkFactor(.8);
  shrinkFilter->Update();

  std::cout << "There are "
            << shrinkFilter->GetOutput()->GetNumberOfPoints() << " points after shrinking."
            << std::endl;
  std::cout << "There are "
            << shrinkFilter->GetOutput()->GetNumberOfCells() << " cells after shrinking."
            << std::endl;

  // Note: there are more points after shrinking because cells no longer share points.

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(shrinkFilter->GetOutputPort());
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
  renderer->SetBackground(.2, .3, .4);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
