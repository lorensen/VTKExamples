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

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#else
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
#endif
  this->ui->qvtkWidget->SetRenderWindow(renderWindow);

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

  // VTK/Qt wedded
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

}

void RenderWindowUISingleInheritance::slotExit()
{
  qApp->exit();
}
