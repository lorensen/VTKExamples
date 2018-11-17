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

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#else
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
#endif
  this->qvtkWidget->SetRenderWindow(renderWindow);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkEventQtSlotConnect> slotConnector;
#else
  vtkSmartPointer<vtkEventQtSlotConnect> slotConnector = vtkSmartPointer<vtkEventQtSlotConnect>::New();
#endif
  this->Connections = slotConnector;

  // Sphere
#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkSphereSource> sphereSource;
#else
  vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
#endif
  sphereSource->Update();

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkPolyDataMapper> sphereMapper;
#else
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#endif
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkActor> sphereActor;
#else
  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
#endif
  sphereActor->SetMapper(sphereMapper);

  // VTK Renderer
#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkRenderer> renderer;
#else
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
#endif
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
