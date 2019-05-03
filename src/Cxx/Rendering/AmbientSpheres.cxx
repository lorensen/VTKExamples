#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

#include <array>

int main(int, char*[])
{
  vtkNew<vtkNamedColors> colors;

  // Set the background color.
  std::array<unsigned char, 4> bkg{{26, 51, 102, 255}};
  colors->SetColor("bkg", bkg.data());

  // The following lines create a sphere represented by polygons.
  //
  vtkNew<vtkSphereSource> sphere;
  sphere->SetThetaResolution(100);
  sphere->SetPhiResolution(50);

  // The mapper is responsible for pushing the geometry into the graphics
  // library. It may also do color mapping, if scalars or other attributes
  // are defined.
  //
  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphere->GetOutputPort());

  // The actor is a grouping mechanism: besides the geometry (mapper), it
  // also has a property, transformation matrix, and/or texture map.
  // In this example we create eight different spheres (two rows of four
  // spheres) and set the ambient lighting coefficients. A little ambient
  // is turned on so the sphere is not completely black on the back side.
  //
  // Since we are using the same sphere source and mapper for all eight spheres
  // we will use a std::array holding the actors.
  //
  // If you want/need to use std::vector, then you must use
  // std::vector<vtkSmartPointer<vtkActor>> spheres;
  // and then, in a loop, create the object using
  // spheres.push_back(vtkSmartPointer<vtkActor>::New());
  //
  // The reason:
  // vtkNew, in contrast to vtkSmartPointer, has no assignment operator
  // or copy constructor and owns one object for its whole lifetime.
  // Thus vtkNew does not satisfy the CopyAssignable and CopyConstructible
  // requirements needed for other std containers like std::vector or std::list.
  // std::array, on the other hand, is a container encapsulating fixed size
  // arrays so its elements do not need to be CopyAssignable and
  // CopyConstructible.
  //
  // So:
  //    std::array - vtkNew or vtkSmartPointer can be used.
  //    std::vector, std::list - only vtkSmartPointer can be used.
  //
  auto const numberOfSpheres = 8;
  std::array<vtkNew<vtkActor>, numberOfSpheres> spheres;
  auto ambient = 0.125;
  auto diffuse = 0.0;
  auto specular = 0.0;
  std::array<double, 3> position{{0, 0, 0}};
  for (auto i = 0; i < spheres.size(); ++i)
  {
    spheres[i]->SetMapper(sphereMapper);
    spheres[i]->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
    spheres[i]->GetProperty()->SetAmbient(ambient);
    spheres[i]->GetProperty()->SetDiffuse(diffuse);
    spheres[i]->GetProperty()->SetSpecular(specular);
    spheres[i]->AddPosition(position.data());
    ambient += 0.125;
    position[0] += 1.25;
    if (i == 3)
    {
      position[0] = 0;
      position[1] = 1.25;
    }
  }

  // Create the graphics structure. The renderer renders into the
  // render window. The render window interactor captures mouse events
  // and will perform appropriate camera or actor manipulation
  // depending on the nature of the events.
  //
  vtkNew<vtkRenderer> ren;
  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(ren);
  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size.
  //
  for (auto i = 0; i < numberOfSpheres; ++i)
  {
    ren->AddActor(spheres[i]);
  }

  ren->SetBackground(colors->GetColor3d("bkg").GetData());
  renWin->SetSize(640, 480);
  std::cout << "DPI: " << renWin->GetDPI() << std::endl;
  renWin->SetWindowName("Ambient Spheres");

  // Set up the lighting.
  //
  vtkNew<vtkLight> light;
  light->SetFocalPoint(1.875, 0.6125, 0);
  light->SetPosition(0.875, 1.6125, 1);
  ren->AddLight(light);

  // We want to eliminate perspective effects on the apparent lighting.
  // Parallel camera projection will be used. To zoom in parallel projection
  // mode, the ParallelScale is set.
  //
  ren->GetActiveCamera()->SetFocalPoint(0, 0, 0);
  ren->GetActiveCamera()->SetPosition(0, 0, 1);
  ren->GetActiveCamera()->SetViewUp(0, 1, 0);
  ren->GetActiveCamera()->ParallelProjectionOn();
  ren->ResetCamera();
  ren->GetActiveCamera()->SetParallelScale(2.0);
  // This starts the event loop and invokes an initial render.
  //
  iren->Initialize();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
