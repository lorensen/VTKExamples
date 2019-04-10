#include <vtkCommand.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkSphereRepresentation.h>
#include <vtkSphereWidget2.h>

// Callback that displays the sphere widget's spherical handle postion
// in both sphercial (relative to the widget's center) and cartesian global coordinates
class vtkSphereCallback : public vtkCommand
{
public:
  static vtkSphereCallback *New()
  {
    return new vtkSphereCallback;
  }

  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSphereWidget2 *sphereWidget =
      reinterpret_cast<vtkSphereWidget2*>(caller);

    double center[3], handlePosition[3];
    vtkSphereRepresentation* sphereRepresentation =
      dynamic_cast<vtkSphereRepresentation*>( sphereWidget->GetRepresentation() );
    sphereRepresentation->GetHandlePosition( handlePosition );
    sphereRepresentation->GetSphere( this->Sphere );

    this->Sphere->GetCenter( center );

    double radius = sqrt( static_cast<double>(vtkMath::Distance2BetweenPoints( center, handlePosition ) ) );
    radius = (radius <= 0.0 ? 1.0 : radius );
    double theta = vtkMath::DegreesFromRadians( atan2( ( handlePosition[1] - center[1] ), ( handlePosition[0] - center[0] ) ) );
    double phi   = vtkMath::DegreesFromRadians( acos( ( handlePosition[2] - center[2] ) / radius ) );

    std::cout << "r, theta, phi: ("
              << std::setprecision(3)
              << radius << ", " << theta << ", " << phi << ") "
              << "x, y, z: ("
              << handlePosition[0] << ", "
              << handlePosition[1] << ", "
              << handlePosition[2] << ") "
              << std::endl;
  }

  vtkSphereCallback(){ this->Sphere = vtkSphere::New(); }
  ~vtkSphereCallback(){ this->Sphere->Delete(); }

  vtkSphere* Sphere;
};

int main( int, char *[] )
{
  // Create a renderer and a render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create a sphere widget
  vtkSmartPointer<vtkSphereWidget2> sphereWidget =
    vtkSmartPointer<vtkSphereWidget2>::New();
  sphereWidget->SetInteractor(renderWindowInteractor);
  sphereWidget->CreateDefaultRepresentation();

  vtkSphereRepresentation* sphereRepresentation =
    dynamic_cast<vtkSphereRepresentation*>( sphereWidget->GetRepresentation() );
  sphereRepresentation->HandleVisibilityOn();

  vtkSmartPointer<vtkSphereCallback> sphereCallback =
    vtkSmartPointer<vtkSphereCallback>::New();

  sphereWidget->AddObserver( vtkCommand::InteractionEvent, sphereCallback );

  renderWindow->Render();

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  sphereWidget->On();

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
