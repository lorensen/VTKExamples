#include <vtkSmartPointer.h>
#include <vtkCubeAxesActor.h>

#include <vtkPolyDataMapper.h>
#include <vtkTextProperty.h>
#include <vtkActorCollection.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkSuperquadricSource.h>
#include <vtkActor.h>

#include <vtkNamedColors.h>
#include <vtkColor.h>

int main(int, char *[])
{
  // Define colors for this example
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkColor3d backgroundColor = colors->GetColor3d("Indigo");
  vtkColor3d actorColor = colors->GetColor3d("Tomato");
  vtkColor3d axis1Color = colors->GetColor3d("Salmon");
  vtkColor3d axis2Color = colors->GetColor3d("PaleGreen");
  vtkColor3d axis3Color = colors->GetColor3d("DodgerBlue");

  // Create a superquadric
  vtkSmartPointer<vtkSuperquadricSource> superquadricSource = 
    vtkSmartPointer<vtkSuperquadricSource>::New();
  superquadricSource->SetPhiRoundness(3.1);
  superquadricSource->SetThetaRoundness(1.0);
  superquadricSource->Update(); // needed to GetBounds later

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(superquadricSource->GetOutputPort());

  vtkSmartPointer<vtkActor> superquadricActor =
    vtkSmartPointer<vtkActor>::New();
  superquadricActor->SetMapper(mapper);
  superquadricActor->GetProperty()->SetDiffuseColor(actorColor.GetData());
  superquadricActor->GetProperty()->SetDiffuse(.7);
  superquadricActor->GetProperty()->SetSpecular(.7);
  superquadricActor->GetProperty()->SetSpecularPower(50.0);
  
  vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor =
    vtkSmartPointer<vtkCubeAxesActor>::New();
  cubeAxesActor->SetUseTextActor3D(1);
  cubeAxesActor->SetBounds(superquadricSource->GetOutput()->GetBounds());
  cubeAxesActor->SetCamera(renderer->GetActiveCamera());
  cubeAxesActor->GetTitleTextProperty(0)->SetColor(axis1Color.GetData());
  cubeAxesActor->GetTitleTextProperty(0)->SetFontSize(48);
  cubeAxesActor->GetLabelTextProperty(0)->SetColor(axis1Color.GetData());

  cubeAxesActor->GetTitleTextProperty(1)->SetColor(axis2Color.GetData());
  cubeAxesActor->GetLabelTextProperty(1)->SetColor(axis2Color.GetData());

  cubeAxesActor->GetTitleTextProperty(2)->SetColor(axis3Color.GetData());
  cubeAxesActor->GetLabelTextProperty(2)->SetColor(axis3Color.GetData());

  cubeAxesActor->DrawXGridlinesOn();
  cubeAxesActor->DrawYGridlinesOn();
  cubeAxesActor->DrawZGridlinesOn();
#if VTK_MAJOR_VERSION == 6
  cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
#endif
#if VTK_MAJOR_VERSION > 6
  cubeAxesActor->SetGridLineLocation(
    cubeAxesActor->VTK_GRID_LINES_FURTHEST);
#endif
  
  cubeAxesActor->XAxisMinorTickVisibilityOff();
  cubeAxesActor->YAxisMinorTickVisibilityOff();
  cubeAxesActor->ZAxisMinorTickVisibilityOff();

  cubeAxesActor->SetFlyModeToStaticEdges();
  renderer->AddActor(cubeAxesActor);
  renderer->AddActor(superquadricActor);
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);

  renderer->ResetCamera();
  renderer->SetBackground(backgroundColor.GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->SetWindowName("CubeAxesActor");

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
