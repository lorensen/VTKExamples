#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkClipPolyData.h>
#include <vtkCylinder.h>
#include <vtkImplicitBoolean.h>
#include <vtkNamedColors.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphere.h>
#include <vtkTransform.h>

int main (int, char *[])
{
// Demonstrate the use of clipping on polygonal data
//
  
// create pipeline
//
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPlaneSource> plane =
    vtkSmartPointer<vtkPlaneSource>::New();
  plane->SetXResolution(25);
  plane->SetYResolution(25);
  plane->SetOrigin(-1, -1, 0);
  plane->SetPoint1(1, -1, 0);
  plane->SetPoint2(-1, 1, 0);

  vtkSmartPointer<vtkTransform> transformSphere =
    vtkSmartPointer<vtkTransform>::New();
  transformSphere->Identity();
  transformSphere->Translate(.4, -.4, 0);
  transformSphere->Inverse();

  vtkSmartPointer<vtkSphere> sphere =
    vtkSmartPointer<vtkSphere>::New();
  sphere->SetTransform(transformSphere);
  sphere->SetRadius(.5);

  vtkSmartPointer<vtkTransform> transformCylinder =
    vtkSmartPointer<vtkTransform>::New();
  transformCylinder->Identity();
  transformCylinder->Translate(-.4, .4, 0);
  transformCylinder->RotateZ(30);
  transformCylinder->RotateY(60);
  transformCylinder->RotateX(90);
  transformCylinder->Inverse();

  vtkSmartPointer<vtkCylinder> cylinder =
    vtkSmartPointer<vtkCylinder>::New();
  cylinder->SetTransform(transformCylinder);
  cylinder->SetRadius(.3);

  vtkSmartPointer<vtkImplicitBoolean> boolean =
    vtkSmartPointer<vtkImplicitBoolean>::New();
  boolean->AddFunction(cylinder);
  boolean->AddFunction(sphere);

  vtkSmartPointer<vtkClipPolyData> clipper =
    vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetInputConnection(plane->GetOutputPort());
  clipper->SetClipFunction(boolean);
  clipper->GenerateClippedOutputOn();
  clipper->GenerateClipScalarsOn();
  clipper->SetValue(0);

  vtkSmartPointer<vtkPolyDataMapper> clipMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  clipMapper->SetInputConnection(clipper->GetOutputPort());
  clipMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> clipActor =
    vtkSmartPointer<vtkActor>::New();
  clipActor->SetMapper(clipMapper);
  clipActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Black").GetData());
  clipActor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkPolyDataMapper> clipInsideMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  clipInsideMapper->SetInputData(clipper->GetClippedOutput());
  clipInsideMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> clipInsideActor =
    vtkSmartPointer<vtkActor>::New();
  clipInsideActor->SetMapper(clipInsideMapper);
  clipInsideActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Dim_Gray").GetData());

// Create graphics stuff
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
  ren1->AddActor(clipActor);

  ren1->AddActor(clipInsideActor);
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Dolly(1.4);
  ren1->ResetCameraClippingRange();

  renWin->SetSize(640, 480);

// render the image
//
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
