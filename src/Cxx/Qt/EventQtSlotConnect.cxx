#include "EventQtSlotConnect.h"

#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkInteractorStyleTrackballActor.h>

// Constructor
EventQtSlotConnect::EventQtSlotConnect()
{
  this->setupUi(this);
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->qvtkWidget->SetRenderWindow(renderWindow);

  vtkNew<vtkEventQtSlotConnect> slotConnector;
  this->Connections = slotConnector;

  // Sphere
  vtkNew<vtkSphereSource> sphereSource;
  sphereSource->Update();
  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);

  // VTK Renderer
  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(sphereActor);

  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  this->Connections->Connect(this->qvtkWidget->GetRenderWindow()->GetInteractor(),
  vtkCommand::LeftButtonPressEvent,
  this,
  SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)));

};

void EventQtSlotConnect::slot_clicked(vtkObject*, unsigned long, void*, void*)
{
  std::cout << "Clicked." << std::endl;
}
