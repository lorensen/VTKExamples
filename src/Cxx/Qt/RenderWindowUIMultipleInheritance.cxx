#include "RenderWindowUIMultipleInheritance.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

// Constructor
RenderWindowUIMultipleInheritance::RenderWindowUIMultipleInheritance()
{
  this->setupUi(this);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#if VTK890
  qvtkWidget->setRenderWindow(renderWindow);
#else
  qvtkWidget->SetRenderWindow(renderWindow);
#endif

  // Sphere
  auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  auto sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  auto sphereActor = vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());

  // VTK Renderer
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(sphereActor);
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

  // VTK/Qt wedded
#if VTK890
  this->qvtkWidget->renderWindow()->AddRenderer(renderer);
  this->qvtkWidget->renderWindow()->SetWindowName(
      "RenderWindowUIMultipleInheritance");
#else
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
  this->qvtkWidget->GetRenderWindow()->SetWindowName(
      "RenderWindowUIMultipleInheritance");
#endif

  // Set up action signals and slots
  connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
};

void RenderWindowUIMultipleInheritance::slotExit()
{
  qApp->exit();
}
