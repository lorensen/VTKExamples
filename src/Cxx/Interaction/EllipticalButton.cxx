#include <vtkEllipticalButtonSource.h>
#include <vtkSmartPointer.h>

#include <vtkSuperquadricSource.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkImageData.h>

#include <vtkTexture.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkProp3DButtonRepresentation.h>
#include <vtkButtonWidget.h>
#include <vtkCoordinate.h>
#include <vtkCommand.h>

#include <vtkNamedColors.h>

// Callback for the interaction
namespace
{
class vtkButtonCallback : public vtkCommand
{
public:
  static vtkButtonCallback *New()
    { return new vtkButtonCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
      vtkButtonWidget *buttonWidget =
        reinterpret_cast<vtkButtonWidget*>(caller);
      vtkProp3DButtonRepresentation *rep =
        reinterpret_cast<vtkProp3DButtonRepresentation *>
        (buttonWidget->GetRepresentation());
      int state = rep->GetState();
      this->Actor->GetProperty()->SetColor(reinterpret_cast<vtkActor *>(rep->GetButtonProp(state))->GetProperty()->GetColor());
      std::cout << "State: " << state << "\n";
  }
  vtkButtonCallback():Actor(0) {}
  vtkActor *Actor;
};
}

static vtkSmartPointer<vtkActor> CreateButtonActor(const char *textureFile);

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " imageFilename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> color =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkSuperquadricSource> source =
    vtkSmartPointer<vtkSuperquadricSource>::New();
  source->SetPhiResolution(64);
  source->SetThetaResolution(64);
  source->SetThetaRoundness(1.5);
  source->SetThickness(1.5);
  source->SetSize(2);
  source->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(source->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(color->GetColor3d("Burlywood").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(200, 200);
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create the widget and its representation
  vtkSmartPointer<vtkActor> buttonActor1 = CreateButtonActor(argv[1]);
  buttonActor1->GetProperty()->SetColor(color->GetColor3d("Tomato").GetData());
  vtkSmartPointer<vtkActor> buttonActor2 = CreateButtonActor(argv[1]);
  buttonActor2->GetProperty()->SetColor(color->GetColor3d("Banana").GetData());

  vtkSmartPointer<vtkProp3DButtonRepresentation> buttonRepresentation =
    vtkSmartPointer<vtkProp3DButtonRepresentation>::New();
  buttonRepresentation->SetNumberOfStates(2);
  buttonRepresentation->SetButtonProp(0, buttonActor1);
  buttonRepresentation->SetButtonProp(1, buttonActor2);
  buttonRepresentation->FollowCameraOn();

  vtkSmartPointer<vtkButtonCallback> callback =
    vtkSmartPointer<vtkButtonCallback>::New();
  callback->Actor = actor;
  actor->GetProperty()->SetColor(reinterpret_cast<vtkActor *>(buttonRepresentation->GetButtonProp(0))->GetProperty()->GetColor());

  renderWindowInteractor->Initialize();

  vtkSmartPointer<vtkButtonWidget> buttonWidget =
    vtkSmartPointer<vtkButtonWidget>::New();
  buttonWidget->SetInteractor(renderWindowInteractor);
  buttonWidget->SetRepresentation(buttonRepresentation);
  buttonWidget->AddObserver(vtkCommand::StateChangedEvent,callback);
  buttonWidget->SetEnabled(1);

  renderer->ResetCamera();
  renderer->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
vtkSmartPointer<vtkActor> CreateButtonActor(const char *textureFile)
{
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> imageReader;
  imageReader.TakeReference(
    readerFactory->CreateImageReader2(textureFile));
  imageReader->SetFileName(textureFile);
  imageReader->Update();

  // Aspect ratio of image
  int dims[3];
  imageReader->GetOutput()->GetDimensions(dims);
  double aspect = static_cast<double>(dims[0])/ static_cast<double>(dims[1]);

  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(imageReader->GetOutputPort());

  vtkSmartPointer<vtkEllipticalButtonSource> ellipticalButtonSource
    = vtkSmartPointer<vtkEllipticalButtonSource>::New();
  ellipticalButtonSource->SetCircumferentialResolution(50);
  ellipticalButtonSource->SetShoulderResolution(10);
  ellipticalButtonSource->SetTextureResolution(10);
  ellipticalButtonSource->SetRadialRatio(1.05);
  ellipticalButtonSource->SetShoulderTextureCoordinate(0.0, 0.0);
  ellipticalButtonSource->SetTextureDimensions(dims[0], dims[1]);
  ellipticalButtonSource->SetTextureStyleToProportional();
  ellipticalButtonSource->TwoSidedOn();
  ellipticalButtonSource->SetWidth(aspect);
  ellipticalButtonSource->SetHeight(1.0);
  ellipticalButtonSource->SetDepth(.15);
  ellipticalButtonSource->SetCenter(2, 2, 0);

  ellipticalButtonSource->SetOutputPointsPrecision(vtkAlgorithm::SINGLE_PRECISION);

  vtkSmartPointer<vtkPolyDataMapper> buttonMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  buttonMapper->SetInputConnection(ellipticalButtonSource->GetOutputPort());

  vtkSmartPointer<vtkActor> buttonActor =
    vtkSmartPointer<vtkActor>::New();
  buttonActor->SetMapper(buttonMapper);
  buttonActor->SetTexture(texture);

  return buttonActor;
}

