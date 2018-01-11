#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCone.h>
#include <vtkContourFilter.h>
#include <vtkImplicitBoolean.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSampleFunction.h>
#include <vtkSphere.h>

int main (int, char *[])
{
// This example demonstrates how to use boolean combinations of implicit
// functions to create a model of an ice cream cone.

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

// Create implicit function primitives. These have been carefully placed to
// give the effect that we want. We are going to use various combinations of
// these functions to create the shape we want; for example, we use planes
// intersected with a cone (which is infinite in extent) to get a finite
// cone.
//
  vtkSmartPointer<vtkCone> cone =
    vtkSmartPointer<vtkCone>::New();
  cone->SetAngle(20);

  vtkSmartPointer<vtkPlane> vertPlane =
    vtkSmartPointer<vtkPlane>::New();
  vertPlane->SetOrigin(.1, 0, 0);
  vertPlane->SetNormal(-1, 0, 0);

  vtkSmartPointer<vtkPlane> basePlane =
    vtkSmartPointer<vtkPlane>::New();
  basePlane->SetOrigin(1.2, 0, 0);
  basePlane->SetNormal(1, 0, 0);

  vtkSmartPointer<vtkSphere> iceCream =
    vtkSmartPointer<vtkSphere>::New();
  iceCream->SetCenter(1.333, 0, 0);
  iceCream->SetRadius(0.5);

  vtkSmartPointer<vtkSphere> bite =
    vtkSmartPointer<vtkSphere>::New();
  bite->SetCenter(1.5, 0, 0.5);
  bite->SetRadius(0.25);

// Combine primitives to build ice-cream cone. Clip the cone with planes.
  vtkSmartPointer<vtkImplicitBoolean> theCone =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  theCone->SetOperationTypeToIntersection();
  theCone->AddFunction(cone);
  theCone->AddFunction(vertPlane);
  theCone->AddFunction(basePlane);

// Take a bite out of the ice cream.
  vtkSmartPointer<vtkImplicitBoolean> theCream =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  theCream->SetOperationTypeToDifference();
  theCream->AddFunction(iceCream);
  theCream->AddFunction(bite);

// The sample function generates a distance function from the
// implicit function (which in this case is the cone). This is
// then contoured to get a polygonal surface.
//
  vtkSmartPointer<vtkSampleFunction> theConeSample =
    vtkSmartPointer<vtkSampleFunction>::New();
  theConeSample->SetImplicitFunction(theCone);
  theConeSample->SetModelBounds(-1, 1.5, -1.25, 1.25, -1.25, 1.25);
  theConeSample->SetSampleDimensions(128, 128, 128);
  theConeSample->ComputeNormalsOff();

  vtkSmartPointer<vtkContourFilter> theConeSurface =
    vtkSmartPointer<vtkContourFilter>::New();
  theConeSurface->SetInputConnection(theConeSample->GetOutputPort());
  theConeSurface->SetValue(0, 0.0);

  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(theConeSurface->GetOutputPort());
  coneMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(colors->GetColor3d("chocolate").GetData());

// The same here for the ice cream.
//
  vtkSmartPointer<vtkSampleFunction> theCreamSample =
    vtkSmartPointer<vtkSampleFunction>::New();
  theCreamSample->SetImplicitFunction(theCream);
  theCreamSample->SetModelBounds(0, 2.5, -1.25, 1.25, -1.25, 1.25);
  theCreamSample->SetSampleDimensions(128, 128, 128);
  theCreamSample->ComputeNormalsOff();

  vtkSmartPointer<vtkContourFilter> theCreamSurface =
    vtkSmartPointer<vtkContourFilter>::New();
  theCreamSurface->SetInputConnection(theCreamSample->GetOutputPort());
  theCreamSurface->SetValue(0, 0.0);

  vtkSmartPointer<vtkPolyDataMapper> creamMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  creamMapper->SetInputConnection(theCreamSurface->GetOutputPort());
  creamMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> creamActor =
    vtkSmartPointer<vtkActor>::New();
  creamActor->SetMapper(creamMapper);
  creamActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("mint").GetData());
  creamActor->GetProperty()->SetSpecular(.6);
  creamActor->GetProperty()->SetSpecularPower(50);

// Create the usual rendering stuff
//
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(coneActor);
  ren1->AddActor(creamActor);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(640, 480);
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Roll(90);
  ren1->GetActiveCamera()->Dolly(1.25);
  ren1->ResetCameraClippingRange();
  iren->Initialize();

// render the image
//
  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}
