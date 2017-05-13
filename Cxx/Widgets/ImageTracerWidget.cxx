#include <vtkSmartPointer.h>
#include <vtkCallbackCommand.h>
#include <vtkImageActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkImageTracerWidget.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkProperty.h>

namespace
{
void CallbackFunction (vtkObject* caller, long unsigned int eventId,
                        void* clientData, void* callData );
}

int main(int, char *[])
{
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetExtent(0, 20, 0, 50, 0, 0);
  imageSource->SetDrawColor(0,0,0);
  imageSource->FillBox(0,20,0,50);
  imageSource->SetDrawColor(255,0,0);
  imageSource->FillBox(0,10,0,30);
  imageSource->Update();

  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(imageSource->GetOutputPort());

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(style);

  vtkSmartPointer<vtkImageTracerWidget> tracer =
    vtkSmartPointer<vtkImageTracerWidget>::New();
  tracer->GetLineProperty()->SetLineWidth(5);
  tracer->SetInteractor(interactor);
  tracer->SetViewProp(actor);
  renderWindow->Render();

  // The observer must be added BEFORE the On() call.
  vtkSmartPointer<vtkCallbackCommand> callback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  callback->SetCallback(CallbackFunction);
  tracer->AddObserver(vtkCommand::EndInteractionEvent, callback);
  
  tracer->On();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
void CallbackFunction (vtkObject* caller,
                       long unsigned int vtkNotUsed(eventId),
                       void* vtkNotUsed(clientData),
                       void* vtkNotUsed(callData) )
{
  vtkImageTracerWidget* tracerWidget =
    static_cast<vtkImageTracerWidget*>(caller);

  vtkSmartPointer<vtkPolyData> path =
    vtkSmartPointer<vtkPolyData>::New();

  tracerWidget->GetPath(path);
  std::cout << "There are " << path->GetNumberOfPoints() << " points in the path." << std::endl;
}
} // end anonymous namespace
