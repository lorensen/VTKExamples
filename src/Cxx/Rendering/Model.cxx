#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include <array>

int main(int, char* [])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> cubeColor{{230, 230, 230, 255}};
    colors->SetColor("CubeColor", cubeColor.data());
  std::array<unsigned char , 4> bkg{{230, 230, 230, 255}};
    colors->SetColor("BkgColor", bkg.data());

  // create rendering windows and three renderers
  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderer> ren2 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWindow1 =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWindow1->AddRenderer(ren1);
  renWindow1->AddRenderer(ren2);
  vtkSmartPointer<vtkRenderWindowInteractor> iren1 =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren1->SetRenderWindow(renWindow1);
  vtkSmartPointer<vtkRenderer> ren3 = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWindow2 =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWindow2->AddRenderer(ren3);
  vtkSmartPointer<vtkRenderWindowInteractor> iren2 =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren2->SetRenderWindow(renWindow2);

  // create an actor and give it cone geometry
  vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(8);

  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(cone->GetOutputPort());

  vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

  // create an actor and give it cube geometry
  vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cube->GetOutputPort());

  vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetColor(colors->GetColor3d("CubeColor").GetData());

  // create an actor and give it sphere geometry
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetThetaResolution(16);
  sphere->SetPhiResolution(16);

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor3d("Melon").GetData());

  // assign our actor to both renderers
  ren1->AddActor(coneActor);
  ren2->AddActor(sphereActor);
  ren3->AddActor(cubeActor);

  // set the size of our window
  renWindow1->SetSize(300, 150);
  renWindow1->SetPosition(0, 50);
  renWindow2->SetSize(300, 300);
  renWindow2->SetPosition(0, 300);

  // set the viewports and background of the renderers
  ren1->SetViewport(0, 0, 0.5, 1);
  ren1->SetBackground(colors->GetColor3d("BkgColor").GetData());
  ren2->SetViewport(0.5, 0, 1, 1);
  ren2->SetBackground(colors->GetColor3d("White").GetData());
  ren3->SetBackground(colors->GetColor3d("White").GetData());

  // draw the resulting scene
  renWindow1->Render();
  renWindow2->Render();

  iren1->Start();

  return EXIT_SUCCESS;
}
