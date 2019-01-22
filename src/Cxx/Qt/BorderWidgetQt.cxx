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

#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  // 8.1.0+
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#else
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
#endif
  this->qvtkWidget->SetRenderWindow(renderWindow);

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

  // Connect VTK with Qt
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  // Add a border widget to the right renderer
#if VTK_MAJOR_VERSION == 8 && VTK_MINOR_VERSION > 0
  vtkNew<vtkBorderWidget> bw;
#else
  vtkSmartPointer<vtkBorderWidget> bw = vtkSmartPointer<vtkBorderWidget>::New();
#endif

  this->BorderWidget = bw;
  this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());
  this->BorderWidget->On();
}
