#include <vtkSmartPointer.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkWarpTo.h>

int main(int, char*[])
{
  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create a line
  vtkSmartPointer<vtkLineSource> lineSource = 
    vtkSmartPointer<vtkLineSource>::New();
  lineSource->SetPoint1(0.0, 0.0, 0.0);
  lineSource->SetPoint2(0.0, 1.0, 0.0);
  lineSource->SetResolution(20);
  lineSource->Update();

  // Create a tube (cylinder) around the line
  vtkSmartPointer<vtkTubeFilter> tubeFilter = 
    vtkSmartPointer<vtkTubeFilter>::New();
  tubeFilter->SetInputConnection(lineSource->GetOutputPort());
  tubeFilter->SetRadius(.01); //default is .5
  tubeFilter->SetNumberOfSides(50);
  tubeFilter->Update();
  
  vtkSmartPointer<vtkWarpTo> warpTo = 
    vtkSmartPointer<vtkWarpTo>::New();
  warpTo->SetInputConnection(tubeFilter->GetOutputPort());
  warpTo->SetPosition(10, 1, 0);
  warpTo->SetScaleFactor(5);
  warpTo->AbsoluteOn();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(warpTo->GetOutputPort());
  mapper->ScalarVisibilityOff();
  
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  renderer->AddActor(actor);

  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
