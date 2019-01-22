#include "RenderWindowUIMultipleInheritance.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>

// Constructor
RenderWindowUIMultipleInheritance::RenderWindowUIMultipleInheritance()
{
  this->setupUi(this);

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#else
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
#endif
  qvtkWidget->SetRenderWindow(renderWindow);

  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);

  // VTK Renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(sphereActor);

  // VTK/Qt wedded
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Set up action signals and slots
  connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

};

void RenderWindowUIMultipleInheritance::slotExit()
{
  qApp->exit();
}
