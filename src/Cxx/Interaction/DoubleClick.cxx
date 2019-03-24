#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkNamedColors.h>

namespace
{
// Define interaction style
class MouseInteractorStyleDoubleClick : public vtkInteractorStyleTrackballCamera
{
public:

  static MouseInteractorStyleDoubleClick* New();
  vtkTypeMacro(MouseInteractorStyleDoubleClick, vtkInteractorStyleTrackballCamera);

  MouseInteractorStyleDoubleClick() : NumberOfClicks(0), ResetPixelDistance(5)
  {
    this->PreviousPosition[0] = 0;
    this->PreviousPosition[1] = 0;
  }

  virtual void OnLeftButtonDown() override
  {
    this->NumberOfClicks++;
    int pickPosition[2];
    this->GetInteractor()->GetEventPosition(pickPosition);

    int xdist = pickPosition[0] - this->PreviousPosition[0];
    int ydist = pickPosition[1] - this->PreviousPosition[1];

    this->PreviousPosition[0] = pickPosition[0];
    this->PreviousPosition[1] = pickPosition[1];

    int moveDistance = (int)sqrt((double)(xdist*xdist + ydist*ydist));

    // Reset numClicks - If mouse moved further than resetPixelDistance
    if(moveDistance > this->ResetPixelDistance)
    {
      this->NumberOfClicks = 1;
    }

    if(this->NumberOfClicks == 2)
    {
      std::cout << "Double clicked." << std::endl;
      this->NumberOfClicks = 0;
    }

    // forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
  }

private:
  unsigned int NumberOfClicks;
  int PreviousPosition[2];
  int ResetPixelDistance;
};
vtkStandardNewMacro(MouseInteractorStyleDoubleClick);
}

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("Slate_grey").GetData());
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );

  vtkSmartPointer<MouseInteractorStyleDoubleClick> style =
    vtkSmartPointer<MouseInteractorStyleDoubleClick>::New();
  renderWindowInteractor->SetInteractorStyle( style );

  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
