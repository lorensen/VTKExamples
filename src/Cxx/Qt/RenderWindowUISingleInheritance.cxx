#include "RenderWindowUISingleInheritance.h"

// This is included here because it is forward declared in
// RenderWindowUISingleInheritance.h
#include "ui_RenderWindowUISingleInheritance.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>

// Constructor
RenderWindowUISingleInheritance::RenderWindowUISingleInheritance()
{
  this->ui = new Ui_RenderWindowUISingleInheritance;
  this->ui->setupUi(this);

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->ui->qvtkWidget->SetRenderWindow(renderWindow);


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

  // VTK/Qt wedded
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

}

void RenderWindowUISingleInheritance::slotExit()
{
  qApp->exit();
}
