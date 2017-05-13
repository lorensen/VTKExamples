#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSuperquadricSource.h>
#include <vtkClipPolyData.h>
#include <vtkPlane.h>
#include <vtkProperty.h>

int main(int, char *[])
{
  // Create a superquadric
  vtkSmartPointer<vtkSuperquadricSource> superquadricSource = 
    vtkSmartPointer<vtkSuperquadricSource>::New();
  superquadricSource->SetPhiRoundness(3.1);
  superquadricSource->SetThetaRoundness(2.2);

  // Define a clipping plane
  vtkSmartPointer<vtkPlane> clipPlane = 
    vtkSmartPointer<vtkPlane>::New();
  clipPlane->SetNormal(1.0, -1.0, -1.0);
  clipPlane->SetOrigin(0.0, 0.0, 0.0);

  // Clip the source with the plane
  vtkSmartPointer<vtkClipPolyData> clipper = 
    vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetInputConnection(superquadricSource->GetOutputPort());
  clipper->SetClipFunction(clipPlane);  

  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> superquadricMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  superquadricMapper->SetInputConnection(clipper->GetOutputPort());
 
  vtkSmartPointer<vtkActor> superquadricActor = 
    vtkSmartPointer<vtkActor>::New();
  superquadricActor->SetMapper(superquadricMapper);

  // Create a property to be used for the back faces. Turn off all
  // shading by specifying 0 weights for specular and diffuse. Max the
  // ambient.
  vtkSmartPointer<vtkProperty> backFaces =
    vtkSmartPointer<vtkProperty>::New();
  backFaces->SetSpecular(0.0);
  backFaces->SetDiffuse(0.0);
  backFaces->SetAmbient(1.0);
  backFaces->SetAmbientColor(1.0000, 0.3882, 0.2784);

  superquadricActor->SetBackfaceProperty(backFaces);
 
  // Create a renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
   renderWindow->SetWindowName("SolidClip");

  renderWindow->AddRenderer(renderer);
 
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  //Add actors to the renderers
  renderer->AddActor(superquadricActor);
  renderWindow->Render();

  //Interact with the window
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
