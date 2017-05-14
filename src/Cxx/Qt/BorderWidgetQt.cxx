#include "BorderWidgetQt.h"

#include <vtkBorderWidget.h>
#include <vtkCommand.h>
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

  // Connect VTK with Qt
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Add a border widget to the right renderer
  this->BorderWidget = vtkSmartPointer<vtkBorderWidget>::New();
  this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());
  this->BorderWidget->On();
}
