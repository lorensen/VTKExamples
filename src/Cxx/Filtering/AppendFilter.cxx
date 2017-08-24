#include <vtkSmartPointer.h>
#include <vtkAppendFilter.h>

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkNamedColors.h>

int main(int, char *[])
{
  // Create 5 points (vtkPolyData)
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(5);
  pointSource->Update();

  vtkSmartPointer<vtkPolyData> polydata = pointSource->GetOutput();

  std::cout << "There are " << polydata->GetNumberOfPoints()
            << " points in the polydata." << std::endl;

  // Create 2 points in a vtkUnstructuredGrid

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(0,0,1);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);

  std::cout << "There are " << ug->GetNumberOfPoints()
            << " points in the unstructured grid." << std::endl;

  // Combine the two data sets
  vtkSmartPointer<vtkAppendFilter> appendFilter =
    vtkSmartPointer<vtkAppendFilter>::New();
  appendFilter->AddInputData(polydata);
  appendFilter->AddInputData(ug);
  appendFilter->Update();

  vtkSmartPointer<vtkUnstructuredGrid> combined =
    appendFilter->GetOutput();
  std::cout << "There are " << combined->GetNumberOfPoints()
            << " points combined." << std::endl;

  // Create a mapper and actor
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(appendFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(5);

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
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
