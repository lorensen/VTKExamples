#include <vtkActor.h>
#include <vtkCommand.h>
#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkPointHandleRepresentation2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSeedRepresentation.h>
#include <vtkSeedWidget.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

class vtkSeedImageCallback : public vtkCommand
{
public:
  static vtkSeedImageCallback* New()
  {
    return new vtkSeedImageCallback;
  }

  vtkSeedImageCallback() = default;

  virtual void Execute(vtkObject*, unsigned long event, void* calldata)
  {
    if (event == vtkCommand::PlacePointEvent)
    {
      std::cout << "Placing point..." << std::endl;
      std::cout << "There are now "
                << this->SeedRepresentation->GetNumberOfSeeds() << " seeds."
                << std::endl;
      for (unsigned int seedId = 0; static_cast<int>(seedId) <
           this->SeedRepresentation->GetNumberOfSeeds();
           seedId++)
      {
        double pos[3];
        this->SeedRepresentation->GetSeedDisplayPosition(seedId, pos);
        std::cout << "Seed " << seedId << " : (" << pos[0] << " " << pos[1]
                  << " " << pos[2] << ")" << std::endl;
      }
      return;
    }
    if (event == vtkCommand::InteractionEvent)
    {
      std::cout << "Interaction..." << std::endl;
      if (calldata)
      {
        double pos[3];
        this->SeedRepresentation->GetSeedDisplayPosition(0, pos);
        std::cout << "Moved to (" << pos[0] << " " << pos[1] << " " << pos[2]
                  << ")" << std::endl;
      }
      return;
    }
  }

  void SetRepresentation(vtkSmartPointer<vtkSeedRepresentation> rep)
  {
    this->SeedRepresentation = rep;
  }
  void SetWidget(vtkSmartPointer<vtkSeedWidget> widget)
  {
    this->SeedWidget = widget;
  }

private:
  vtkSeedRepresentation* SeedRepresentation = nullptr;
  vtkSeedWidget* SeedWidget = nullptr;
};

int main(int /* argc */, char* /* argv */[])
{
  // Create an image
  auto drawing =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 20, 0, 50, 0, 0);
  // Make a blue background
  drawing->SetDrawColor(0, 0, 255);
  drawing->FillBox(0, 20, 0, 50);
  // Make a red circle
  drawing->SetDrawColor(255, 0, 0, 0);
  drawing->DrawCircle(9, 10, 5);
  drawing->Update();

  auto imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->SetInputData(drawing->GetOutput());

  // Create a renderer and render window
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(imageActor);
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Setup interactor style
  auto interactorStyleImage =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  renderWindowInteractor->SetInteractorStyle(interactorStyleImage);

  // Create the representation
  auto handle =
    vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
  handle->GetProperty()->SetColor(1, 0, 0);
  auto rep =
    vtkSmartPointer<vtkSeedRepresentation>::New();
  rep->SetHandleRepresentation(handle);

  // Seed widget
  auto seedWidget =
    vtkSmartPointer<vtkSeedWidget>::New();
  seedWidget->SetInteractor(renderWindowInteractor);
  seedWidget->SetRepresentation(rep);

  auto seedCallback =
    vtkSmartPointer<vtkSeedImageCallback>::New();
  seedCallback->SetRepresentation(rep);
  seedCallback->SetWidget(seedWidget);
  seedWidget->AddObserver(vtkCommand::PlacePointEvent, seedCallback);
  seedWidget->AddObserver(vtkCommand::InteractionEvent, seedCallback);

  renderWindow->Render();

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  seedWidget->On();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
