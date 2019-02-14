#include <vtkActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkLogoRepresentation.h>
#include <vtkLogoWidget.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

int main(int, char *[]) {
  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();
  colors->SetColor("Bkg", 0.2, 0.3, 0.4);

  // A sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(4.0);
  sphereSource->SetPhiResolution(4);
  sphereSource->SetThetaResolution(8);
  sphereSource->Update();

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

  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 200, 0, 200, 0, 0);

  // Clear the image
  // Note: SetDrawColour() uses double values of the rgb colors in the
  //       range [0 ... 255]
  //       So SetDrawColour(255, 255, 255) is white.
  drawing->SetDrawColor(255, 127, 100);
  drawing->FillBox(0, 200, 0, 200);
  drawing->SetDrawColor(0, 0, 0);
  drawing->DrawCircle(100, 100, 50);
  drawing->Update();

  vtkSmartPointer<vtkLogoRepresentation> logoRepresentation =
      vtkSmartPointer<vtkLogoRepresentation>::New();
  logoRepresentation->SetImage(drawing->GetOutput());
  logoRepresentation->SetPosition(0, 0);
  logoRepresentation->SetPosition2(0.4, 0.4);
  logoRepresentation->GetImageProperty()->SetOpacity(.7);

  vtkSmartPointer<vtkLogoWidget> logoWidget =
      vtkSmartPointer<vtkLogoWidget>::New();
  logoWidget->SetInteractor(renderWindowInteractor);
  logoWidget->SetRepresentation(logoRepresentation);

  renderWindow->Render();
  logoWidget->On();
  renderer->SetBackground(colors->GetColor3d("Bkg").GetData());
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
