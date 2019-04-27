#include "BorderWidgetQt.h"

#include <vtkBorderWidget.h>
#include <vtkCommand.h>
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

class BorderCallback : public vtkCommand
{
public:
  BorderCallback()
  {
  }

  static BorderCallback* New()
  {
    return new BorderCallback;
  }

  virtual void Execute(vtkObject* vtkNotUsed(caller), unsigned long, void*)
  {
    //      vtkBorderWidget *borderWidget =
    //          reinterpret_cast<vtkBorderWidget*>(caller);
  }
};

// Constructor
BorderWidgetQt::BorderWidgetQt()
{
  this->setupUi(this);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#if VTK890
  this->qvtkWidget->setRenderWindow(renderWindow);
#else
  this->qvtkWidget->SetRenderWindow(renderWindow);
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

  // Connect VTK with Qt
#if VTK890
  this->qvtkWidget->renderWindow()->AddRenderer(renderer);
#else
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
#endif

  // Add a border widget to the right renderer
  vtkNew<vtkBorderWidget> bw;
  this->BorderWidget = bw;
#if VTK890
  this->BorderWidget->SetInteractor(this->qvtkWidget->interactor());
#else
  this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());
#endif
  this->BorderWidget->On();
}
