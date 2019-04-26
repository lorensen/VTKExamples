#include "RenderWindowUISingleInheritance.h"

// This is included here because it is forward declared in
// RenderWindowUISingleInheritance.h
#include "ui_RenderWindowUISingleInheritance.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

// Constructor
RenderWindowUISingleInheritance::RenderWindowUISingleInheritance()
{
  this->ui = new Ui_RenderWindowUISingleInheritance;
  this->ui->setupUi(this);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#if VTK890
  this->ui->qvtkWidget->setRenderWindow(renderWindow);
#else
  this->ui->qvtkWidget->SetRenderWindow(renderWindow);
#endif

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

  // VTK/Qt wedded
#if VTK890
  this->ui->qvtkWidget->renderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->renderWindow()->SetWindowName(
      "RenderWindowUISingleInheritance");
#else
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->GetRenderWindow()->SetWindowName(
      "RenderWindowUISingleInheritance");
#endif
  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void RenderWindowUISingleInheritance::slotExit()
{
  qApp->exit();
}
