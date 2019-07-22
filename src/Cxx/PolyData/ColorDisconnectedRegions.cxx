#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkNamedColors.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create some spheres
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(5,0,0);
  sphereSource2->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource3 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource3->SetCenter(10,0,0);
  sphereSource3->Update();

  vtkSmartPointer<vtkAppendPolyData> appendFilter =
    vtkSmartPointer<vtkAppendPolyData>::New();
  appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
  appendFilter->AddInputConnection(sphereSource3->GetOutputPort());
  appendFilter->Update();

  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToAllRegions();
  connectivityFilter->ColorRegionsOn();
  connectivityFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(connectivityFilter->GetOutputPort());
  mapper->SetScalarRange(connectivityFilter->GetOutput()->GetPointData()->GetArray("RegionId")->GetRange());
  mapper->Update();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
