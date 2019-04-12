#include <vtkSmartPointer.h>
#include <vtkAssembly.h>

#include <vtkTransform.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkPropAssembly.h>

#include <vtkNamedColors.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(
    namedColors->GetColor3d("Banana").GetData());


  // Create a cube
  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->SetCenter(5.0, 0.0, 0.0);
  cubeSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> cubeActor =
    vtkSmartPointer<vtkActor>::New();
  cubeActor->SetMapper(cubeMapper);
  cubeActor->GetProperty()->SetColor(
    namedColors->GetColor3d("Tomato").GetData());
  // Combine the sphere and cube into an assembly
  vtkSmartPointer<vtkAssembly> assembly =
    vtkSmartPointer<vtkAssembly>::New();
  assembly->AddPart(sphereActor);
  assembly->AddPart(cubeActor);

  // Apply a transform to the whole assembly
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->PostMultiply(); //this is the key line
  transform->Translate(5.0, 0, 0);

  assembly->SetUserTransform(transform);

  // Extract each actor from the assembly and change its opacity
  vtkSmartPointer<vtkPropCollection> collection =
    vtkSmartPointer<vtkPropCollection>::New();

  assembly->GetActors(collection);
  collection->InitTraversal();
  for(vtkIdType i = 0; i < collection->GetNumberOfItems(); i++)
  {
    dynamic_cast<vtkActor*>(collection->GetNextProp())->GetProperty()->SetOpacity(0.5);
  }

  // Visualization
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(assembly);
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

  renderer->ResetCamera();
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
