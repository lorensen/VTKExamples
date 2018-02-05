#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSeedRepresentation.h>
#include <vtkSeedWidget.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

class vtkSeedCallback : public vtkCommand
{
  public:
    static vtkSeedCallback *New()
    {
      return new vtkSeedCallback;
    }

    vtkSeedCallback() {}

    virtual void Execute(vtkObject*, unsigned long event, void *calldata)
    {
      if(event == vtkCommand::PlacePointEvent)
      {
        std::cout << "Point placed, total of: "
            << this->SeedRepresentation->GetNumberOfSeeds() << std::endl;
      }
      if(event == vtkCommand::InteractionEvent)
      {
        if(calldata)
        {
          std::cout << "Interacting with seed : "
              << *(static_cast< int * >(calldata)) << std::endl;
        }
      }


      std::cout << "List of seeds (Display coordinates):" << std::endl;
      for(vtkIdType i = 0; i < this->SeedRepresentation->GetNumberOfSeeds(); i++)
      {
        double pos[3];
        this->SeedRepresentation->GetSeedDisplayPosition(i, pos);
        std::cout << "(" << pos[0] << " " << pos[1] << " " << pos[2] << ")" << std::endl;
      }

    }

    void SetRepresentation(vtkSmartPointer<vtkSeedRepresentation> rep) {this->SeedRepresentation = rep;}
  private:
    vtkSmartPointer<vtkSeedRepresentation> SeedRepresentation;
};

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create the representation
  vtkSmartPointer<vtkPointHandleRepresentation2D> handle =
    vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
  handle->GetProperty()->SetColor(1,0,0);
  vtkSmartPointer<vtkSeedRepresentation> rep =
    vtkSmartPointer<vtkSeedRepresentation>::New();
  rep->SetHandleRepresentation(handle);

  // Seed widget
  vtkSmartPointer<vtkSeedWidget> seedWidget =
    vtkSmartPointer<vtkSeedWidget>::New();
  seedWidget->SetInteractor(renderWindowInteractor);
  seedWidget->SetRepresentation(rep);

  vtkSmartPointer<vtkSeedCallback> seedCallback =
    vtkSmartPointer<vtkSeedCallback>::New();
  seedCallback->SetRepresentation(rep);
  seedWidget->AddObserver(vtkCommand::PlacePointEvent,seedCallback);
  seedWidget->AddObserver(vtkCommand::InteractionEvent,seedCallback);

  renderWindow->Render();

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  seedWidget->On();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
