#include <vtkSmartPointer.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>
#include <vtkLineSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>


/*
 * This example creates a tube around a line. 
 * This is helpful because when you zoom the camera, 
 * the thickness of a line remains constant, 
 * while the thickness of a tube varies.
 * */
 
int main(int, char *[])
{
  // Create a line
  vtkSmartPointer<vtkLineSource> lineSource = 
    vtkSmartPointer<vtkLineSource>::New();
  lineSource->SetPoint1(1.0, 0.0, 0.0);
  lineSource->SetPoint2(0.0, 1.0, 0.0);
 
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> lineMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputConnection(lineSource->GetOutputPort());
  vtkSmartPointer<vtkActor> lineActor = 
    vtkSmartPointer<vtkActor>::New();
  lineActor->GetProperty()->SetColor(0.0,0.0,0.1); // Give some color to the line
  lineActor->SetMapper(lineMapper);
 
  // Create a tube (cylinder) around the line
  vtkSmartPointer<vtkTubeFilter> tubeFilter = 
    vtkSmartPointer<vtkTubeFilter>::New();
  tubeFilter->SetInputConnection(lineSource->GetOutputPort());
  tubeFilter->SetRadius(.025); //default is .5
  tubeFilter->SetNumberOfSides(50);
  tubeFilter->Update();
 
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> tubeMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  tubeMapper->SetInputConnection(tubeFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> tubeActor = 
    vtkSmartPointer<vtkActor>::New();
  tubeActor->GetProperty()->SetOpacity(0.5); //Make the tube have some transparency.
  tubeActor->SetMapper(tubeMapper);
   
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
  renderer->AddActor(tubeActor);
  renderer->AddActor(lineActor);
  renderer->SetBackground(0,1,0);
 
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
