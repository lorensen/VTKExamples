#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkCutter.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int, char *[]) {
    
  vtkNew<vtkNamedColors> colors;

  vtkSmartPointer<vtkCubeSource> cube =
      vtkSmartPointer<vtkCubeSource>::New();
  cube->SetXLength(40);
  cube->SetYLength(30);
  cube->SetZLength(20);
  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cube->GetOutputPort());

  // Create a plane to cut,here it cuts in the XZ direction (xz
  // normal=(1,0,0);XY =(0,0,1),YZ =(0,1,0)
  vtkSmartPointer<vtkPlane> plane = 
      vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(10, 0, 0);
  plane->SetNormal(1, 0, 0);

  // Create cutter
  vtkSmartPointer<vtkCutter> cutter = 
      vtkSmartPointer<vtkCutter>::New();
  cutter->SetCutFunction(plane);
  cutter->SetInputConnection(cube->GetOutputPort());
  cutter->Update();

  vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection(cutter->GetOutputPort());
  cutterMapper->SetResolveCoincidentTopologyToPolygonOffset();

  // Create plane actor
  vtkSmartPointer<vtkActor> planeActor = 
      vtkSmartPointer<vtkActor>::New();
  planeActor->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
  planeActor->GetProperty()->SetLineWidth(2);
  planeActor->GetProperty()->SetAmbient(1.0);
  planeActor->GetProperty()->SetDiffuse(0.0);
  planeActor->SetMapper(cutterMapper);

  // Create cube actor
  vtkSmartPointer<vtkActor> cubeActor = 
      vtkSmartPointer<vtkActor>::New();
  cubeActor->GetProperty()->SetColor(
      colors->GetColor3d("Aquamarine").GetData());
  cubeActor->GetProperty()->SetOpacity(0.5);
  cubeActor->SetMapper(cubeMapper);

  // Create renderers and add actors of plane and cube
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(planeActor); // display the rectangle resulting from the
                                  // cut
  renderer->AddActor(cubeActor); // display the cube

  // Add renderer to renderwindow and render
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(600, 600);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
