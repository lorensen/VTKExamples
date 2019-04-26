#include "EventQtSlotConnect.h"

#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkEventQtSlotConnect.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

// Constructor
EventQtSlotConnect::EventQtSlotConnect()
{
  this->setupUi(this);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#if VTK890
  this->qvtkWidget->setRenderWindow(renderWindow);
#else
  this->qvtkWidget->SetRenderWindow(renderWindow);
#endif

  vtkNew<vtkEventQtSlotConnect> slotConnector;
  this->Connections = slotConnector;

  // Sphere
  vtkNew<vtkSphereSource> sphereSource;
  sphereSource->Update();
  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

  // VTK Renderer
  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(sphereActor);
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

#if VTK890
  this->qvtkWidget->renderWindow()->AddRenderer(renderer);
#else
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
#endif

#if VTK890
  this->Connections->Connect(
      this->qvtkWidget->renderWindow()->GetInteractor(),
      vtkCommand::LeftButtonPressEvent, this,
      SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)));
#else
  this->Connections->Connect(
      this->qvtkWidget->GetRenderWindow()->GetInteractor(),
      vtkCommand::LeftButtonPressEvent, this,
      SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)));
#endif
};

void EventQtSlotConnect::slot_clicked(vtkObject*, unsigned long, void*, void*)
{
  std::cout << "Clicked." << std::endl;
}
