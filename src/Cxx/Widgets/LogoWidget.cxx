#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkLogoRepresentation.h>
#include <vtkLogoWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
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
  drawing->SetExtent(0,200,0,200,0,0);

  // Clear the image
  drawing->SetDrawColor(255, 127, 100);
  drawing->FillBox(0,200,0,200);
  drawing->SetDrawColor(0, 0, 0);
  drawing->DrawCircle(100, 100, 50);
  drawing->Update();

  vtkSmartPointer<vtkLogoRepresentation> logoRepresentation = 
    vtkSmartPointer<vtkLogoRepresentation>::New();
  logoRepresentation->SetImage(drawing->GetOutput());
  logoRepresentation->SetPosition(0,0);
  logoRepresentation->SetPosition2(.4, .4);
  logoRepresentation->GetImageProperty()->SetOpacity(.7);
  
  vtkSmartPointer<vtkLogoWidget> logoWidget = 
    vtkSmartPointer<vtkLogoWidget>::New();
  logoWidget->SetInteractor(renderWindowInteractor);
  logoWidget->SetRepresentation(logoRepresentation);
  
  renderWindow->Render();
  logoWidget->On();
  renderer->SetBackground(.2, .3, .4);
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
