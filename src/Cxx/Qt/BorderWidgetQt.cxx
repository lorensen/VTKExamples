#include "BorderWidgetQt.h"

#include <vtkBorderWidget.h>
#include <vtkCommand.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

class BorderCallback : public vtkCommand
{
  public:
    BorderCallback(){}

    static BorderCallback *New()
    {
      return new BorderCallback;
    }

  virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long, void*)
  {
//      vtkBorderWidget *borderWidget =
//          reinterpret_cast<vtkBorderWidget*>(caller);
  }

};

// Constructor
BorderWidgetQt::BorderWidgetQt()
{
  this->setupUi(this);

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->qvtkWidget->SetRenderWindow(renderWindow);

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

  // Connect VTK with Qt
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Add a border widget to the right renderer
  vtkNew<vtkBorderWidget> bw;
  this->BorderWidget = bw;
  this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());
  this->BorderWidget->On();
}
