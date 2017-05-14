#include <vtkSmartPointer.h>
#include <vtkFeatureEdges.h>
#include <vtkPolyData.h>
#include <vtkDiskSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDiskSource> diskSource =
    vtkSmartPointer<vtkDiskSource>::New();
  diskSource->Update();

  vtkSmartPointer<vtkFeatureEdges> featureEdges =
    vtkSmartPointer<vtkFeatureEdges>::New();
  featureEdges->SetInputConnection(diskSource->GetOutputPort());
  featureEdges->BoundaryEdgesOn();
  featureEdges->FeatureEdgesOff();
  featureEdges->ManifoldEdgesOff();
  featureEdges->NonManifoldEdgesOff();
  featureEdges->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> edgeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  edgeMapper->SetInputConnection(featureEdges->GetOutputPort());
  vtkSmartPointer<vtkActor> edgeActor =
    vtkSmartPointer<vtkActor>::New();
  edgeActor->SetMapper(edgeMapper);

  vtkSmartPointer<vtkPolyDataMapper> diskMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  diskMapper->SetInputConnection(diskSource->GetOutputPort());
  vtkSmartPointer<vtkActor> diskActor =
    vtkSmartPointer<vtkActor>::New();
  diskActor->SetMapper(diskMapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(edgeActor);
  renderer->AddActor(diskActor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
