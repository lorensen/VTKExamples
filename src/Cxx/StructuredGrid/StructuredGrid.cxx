#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid =
    vtkSmartPointer<vtkStructuredGrid>::New();

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  double x, y, z;

  x = 0.0;
  y = 0.0;
  z = 0.0;

  for(unsigned int k = 0; k < 2; k++)
  {
    z += 2.0;
    for(unsigned int j = 0; j < 3; j++)
    {
      y += 1.0;
      for(unsigned int i = 0; i < 2; i++)
      {
        x += .5;
        points->InsertNextPoint(x, y, z);
      }
    }
  }

  // Specify the dimensions of the grid
  structuredGrid->SetDimensions(2,3,2);
  structuredGrid->SetPoints(points);

  int* dims = structuredGrid->GetDimensions();

  // Retrieve the entries from the grid and print them to the screen
  unsigned int counter = 0;

  for (int k = 0; k < dims[2]; k++)
  {
    for (int j = 0; j < dims[1]; j++)
    {
      for (int i = 0; i < dims[0]; i++)
      {
        double p[3];
        structuredGrid->GetPoint(counter, p);

        double pNew[3];
        structuredGrid->GetPoint(i, j, k, pNew);

        std::cout << "P   : "
                  << p[0] << " "
                  << p[1] << " "
                  << p[2] << std::endl;
        std::cout << "PNew: "
                  << pNew[0] << " "
                  << pNew[1] << " "
                  << pNew[2] << std::endl;

        counter++;
      }
    }
  }

  // Create a mapper and actor
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(structuredGrid);

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
  renderer->SetBackground(.3, .6, .3); // Background color green

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
