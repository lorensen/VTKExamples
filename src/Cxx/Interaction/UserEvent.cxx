#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include "vtkTestFilter.h"

static void CallbackFunction(vtkObject* caller,
                long unsigned int eventId,
                void* clientData,
                void* callData );

int main(int, char *[])
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

  vtkSmartPointer<vtkTestFilter> filter =
    vtkSmartPointer<vtkTestFilter>::New();

  vtkSmartPointer<vtkCallbackCommand> callback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  callback->SetCallback(CallbackFunction );
  filter->AddObserver(filter->RefreshEvent, callback);

  filter->Update();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void CallbackFunction(vtkObject* /* caller */,
                long unsigned int /* eventId */,
                void* /* clientData */, void* /* callData */)
{
  std::cout << "CallbackFunction called." << std::endl;
}
