#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkBrownianPoints.h>
#include <vtkCamera.h>
#include <vtkGlyph3D.h>
#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

#include <vtkNamedColors.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  
  // Generate random vectors
  vtkMath::RandomSeed(5070); // for testing
  vtkSmartPointer<vtkBrownianPoints> brownianPoints =
    vtkSmartPointer<vtkBrownianPoints>::New();
  brownianPoints->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
  
  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
  glyph3D->SetInputConnection(brownianPoints->GetOutputPort());
  glyph3D->SetScaleFactor(.3);
  
  // Create a mapper and actor for sphere
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->EdgeVisibilityOn();
  actor->GetProperty()->SetInterpolationToFlat();
  actor->SetMapper(mapper);

  // Create a mapper and actor for glyphs
  vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyphMapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> glyphActor =
    vtkSmartPointer<vtkActor>::New();
  glyphActor->GetProperty()->SetColor(colors->GetColor3d("banana").GetData());
  glyphActor->SetMapper(glyphMapper);

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(glyphActor);

  // Create a nice view
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.4);
  renderer->ResetCameraClippingRange();

  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  
  //Render and interact
  renderWindow->SetSize(640, 480);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
