#include <vtkSphereSource.h>
#include <vtkObjectFactory.h>
#include <vtkCommand.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkTestFilter.h>

class CustomStyle : public vtkInteractorStyleTrackballCamera
{
  public:
    static CustomStyle* New();
    vtkTypeMacro(CustomStyle, vtkInteractorStyleTrackballCamera);

    CustomStyle()
    {
      this->Actor = vtkSmartPointer<vtkActor>::New();
      this->Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      this->Filter = vtkSmartPointer<vtkTestFilter>::New();
    }

    void CallbackFunction(vtkObject* caller,
                    long unsigned int eventId,
                    void* callData )
    {
      std::cout << "CustomStyle::CallbackFunction called." << std::endl;
      vtkPolyData* intermediate = this->Filter->GetIntermediateOutput();
      intermediate->Modified();
      this->Mapper->SetInput(intermediate);
      this->Renderer->ResetCamera();
      this->Renderer->Render();
      this->Interactor->GetRenderWindow()->Render();
    }

    void OnKeyPress()
    {
      // Get the keypress
      std::string key = this->Interactor->GetKeySym();

      if(key == "s") // 'S'tart
      {
        this->Renderer->AddActor(this->Actor);
        this->Filter->AddObserver(this->Filter->RefreshEvent, this, &CustomStyle::CallbackFunction);
        this->Filter->Update();

        this->Actor->SetMapper(this->Mapper);
      }

      // Forward events
      vtkInteractorStyleTrackballCamera::OnKeyPress();
    }

  vtkRenderer* Renderer;
  vtkSmartPointer<vtkActor> Actor;
  vtkSmartPointer<vtkPolyDataMapper> Mapper;
  vtkSmartPointer<vtkTestFilter> Filter;

};
vtkStandardNewMacro(CustomStyle);

int main(int argc, char *argv[])
{
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->SetBackground(1,1,1); // White

  vtkSmartPointer<CustomStyle> style =
    vtkSmartPointer<CustomStyle>::New();
  style->Renderer = renderer;

  renderWindowInteractor->SetInteractorStyle(style);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
