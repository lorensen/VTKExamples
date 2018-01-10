#include <vtkActor.h>
#include <vtkCullerCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkElevationFilter.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShrinkFilter.h>
#include <vtkSphereSource.h>


int main( int, char *[] )
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->GetCullers()->RemoveAllItems();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetThetaResolution(12); sphere->SetPhiResolution(12);

  vtkSmartPointer<vtkShrinkFilter> shrink =
    vtkSmartPointer<vtkShrinkFilter>::New();
  shrink->SetInputConnection(sphere->GetOutputPort());
  shrink->SetShrinkFactor(0.9);

  vtkSmartPointer<vtkElevationFilter> colorIt =
    vtkSmartPointer<vtkElevationFilter>::New();
  colorIt->SetInputConnection(shrink->GetOutputPort());
  colorIt->SetLowPoint(0,0,-.5);
  colorIt->SetHighPoint(0,0,.5);

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(colorIt->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("White").GetData());
  renWin->SetSize(640, 480);
  
  renWin->Render();

  // interact with data
  iren->Start();

  return EXIT_SUCCESS;
}
