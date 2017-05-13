#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkIntArray.h>
#include <vtkLabelPlacementMapper.h>
#include <vtkPointData.h>
#include <vtkPointSetToLabelHierarchy.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

int main(int, char *[])
{
  // Create a point set.
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(6);
  pointSource->Update();

  // Add label array.
  vtkSmartPointer<vtkStringArray> labels =
    vtkSmartPointer<vtkStringArray>::New();
  labels->SetNumberOfValues(6);
  labels->SetName("labels");
  labels->SetValue(0, "Priority 10");
  labels->SetValue(1, "Priority 7");
  labels->SetValue(2, "Priority 6");
  labels->SetValue(3, "Priority 4");
  labels->SetValue(4, "Priority 4");
  labels->SetValue(5, "Priority 4");
  pointSource->GetOutput()->GetPointData()->AddArray(labels);

  // Add priority array.
  vtkSmartPointer<vtkIntArray> sizes =
    vtkSmartPointer<vtkIntArray>::New();
  sizes->SetNumberOfValues(6);
  sizes->SetName("sizes");
  sizes->SetValue(0, 10);
  sizes->SetValue(1, 7);
  sizes->SetValue(2, 6);
  sizes->SetValue(3, 4);
  sizes->SetValue(4, 4);
  sizes->SetValue(5, 4);
  pointSource->GetOutput()->GetPointData()->AddArray(sizes);

  // Create a mapper and actor for the points.
  vtkSmartPointer<vtkPolyDataMapper> pointMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointMapper->SetInputConnection(pointSource->GetOutputPort());

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);

  // Generate the label hierarchy.
  vtkSmartPointer<vtkPointSetToLabelHierarchy> pointSetToLabelHierarchyFilter =
    vtkSmartPointer<vtkPointSetToLabelHierarchy>::New();
  pointSetToLabelHierarchyFilter->SetInputConnection(
    pointSource->GetOutputPort());
  pointSetToLabelHierarchyFilter->SetLabelArrayName("labels");
  pointSetToLabelHierarchyFilter->SetPriorityArrayName("sizes");
  pointSetToLabelHierarchyFilter->Update();

  // Create a mapper and actor for the labels.
  vtkSmartPointer<vtkLabelPlacementMapper> labelMapper =
    vtkSmartPointer<vtkLabelPlacementMapper>::New();
  labelMapper->SetInputConnection(
    pointSetToLabelHierarchyFilter->GetOutputPort());
  vtkSmartPointer<vtkActor2D> labelActor =
    vtkSmartPointer<vtkActor2D>::New();
  labelActor->SetMapper(labelMapper);

  // Create a renderer, render window, and interactor.
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene.
  renderer->AddActor(pointActor);
  renderer->AddActor(labelActor);

  // Render and interact.
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
