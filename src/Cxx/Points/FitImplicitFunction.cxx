#include <vtkSmartPointer.h>
#include <vtkFitImplicitFunction.h>
#include <vtkBoundedPointSource.h>

#include <vtkSphere.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
#include <vtkMath.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main (int, char *[])
{
  vtkMath::RandomSeed(4355412); // for test result consistency

  double radius = 1.0;
  vtkSmartPointer<vtkBoundedPointSource> points =
    vtkSmartPointer<vtkBoundedPointSource>::New();
  points->SetNumberOfPoints(1000000);
  points->SetBounds(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

  vtkSmartPointer<vtkSphere> sphere =
    vtkSmartPointer<vtkSphere>::New();
  sphere->SetRadius(radius);

  vtkSmartPointer<vtkFitImplicitFunction> fit =
    vtkSmartPointer<vtkFitImplicitFunction>::New();
  fit->SetInputConnection(points->GetOutputPort());
  fit->SetImplicitFunction(sphere);
  fit->SetThreshold(.01);
  fit->Update();
  std::cout << fit->GetOutput()->GetNumberOfPoints() << " out of "
            << points->GetNumberOfPoints() << " points are within "
            << fit->GetThreshold() << " of the implicit function" << std::endl;

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(radius * .05);

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetInputConnection(fit->GetOutputPort());
  glyph3D->SetSourceConnection(sphereSource->GetOutputPort());
  glyph3D->ScalingOff();
  glyph3D->Update();

  vtkSmartPointer<vtkPolyDataMapper> glyph3DMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkActor> glyph3DActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor->SetMapper(glyph3DMapper);
  glyph3DActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(glyph3DActor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.0);
  ren1->ResetCameraClippingRange();

  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
