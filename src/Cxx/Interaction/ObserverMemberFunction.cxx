#include <vtkPolyDataMapper.h>
#include <vtkObjectFactory.h>
#include <vtkCommand.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyle.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>

// A class not derived from vtkObjectBase
class MyClass
{
  public:
    void KeypressCallbackFunction(vtkObject*,
                                  long unsigned int vtkNotUsed(eventId),
                                  void* vtkNotUsed(callData))
    {
    std::cout << "Caught event in MyClass" << std::endl;
    }

};

// A class that is derived from vtkObjectBase
class MyInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
  static MyInteractorStyle* New();
  vtkTypeMacro(MyInteractorStyle, vtkInteractorStyleTrackballCamera);

  void KeypressCallbackFunction(vtkObject*,
                                long unsigned int vtkNotUsed(eventId),
                                void* vtkNotUsed(callData) )
  {
    std::cout << "Caught event in MyInteractorStyle" << std::endl;
  }

};
vtkStandardNewMacro(MyInteractorStyle);

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  MyClass myClass;
  renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, &myClass, &MyClass::KeypressCallbackFunction);

  vtkSmartPointer<MyInteractorStyle> style =
    vtkSmartPointer<MyInteractorStyle>::New();
  renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, style, &MyInteractorStyle::KeypressCallbackFunction);

  vtkSmartPointer<MyInteractorStyle> style2 =
    vtkSmartPointer<MyInteractorStyle>::New();
  renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, style2, &MyInteractorStyle::KeypressCallbackFunction);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
