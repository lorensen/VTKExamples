#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  // Create the polydata geometry

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Set up the actor to display the untransformed polydata
 
  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(1,0,0);

  // Set up the transform filter

  vtkSmartPointer<vtkTransform> translation =
    vtkSmartPointer<vtkTransform>::New();
  translation->Translate(1.0, 2.0, 3.0);

  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformFilter->SetInputConnection(sphereSource->GetOutputPort());
  transformFilter->SetTransform(translation);
  transformFilter->Update();

  // Set up the actor to display the transformed polydata

  vtkSmartPointer<vtkPolyDataMapper> transformedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  transformedMapper->SetInputConnection(transformFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> transformedActor =
    vtkSmartPointer<vtkActor>::New();
  transformedActor->SetMapper(transformedMapper);
  transformedActor->GetProperty()->SetColor(0,1,0);

  // Set up the rest of the visualization pipeline

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(transformedActor);
  renderer->SetBackground(.3, .6, .3); // Set renderer's background color to green

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
