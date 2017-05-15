#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVectorText.h>

int main(int, char *[])
{
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

  // Create text
  vtkSmartPointer<vtkVectorText> textSource =
    vtkSmartPointer<vtkVectorText>::New();
  textSource->SetText("TEXT");
  textSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> textMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  textMapper->SetInputConnection(textSource->GetOutputPort());

  vtkSmartPointer<vtkActor> textActor =
    vtkSmartPointer<vtkActor>::New();
  textActor->SetMapper(textMapper);

  vtkSmartPointer<vtkRenderer> renderer1 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer1->SetLayer(0);

  vtkSmartPointer<vtkRenderer> renderer2 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer2->SetActiveCamera(renderer1->GetActiveCamera());
  renderer2->SetLayer(1);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer1);
  renderWindow->AddRenderer(renderer2);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer1->AddActor(sphereActor);
  renderer2->AddActor(textActor);

  renderWindow->SetNumberOfLayers(2);
  renderer1->ResetCamera();
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
