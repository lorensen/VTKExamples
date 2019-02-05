#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkConnectivityFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendFilter.h>
#include <vtkDelaunay3D.h>

int main(int, char*[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();

  vtkSmartPointer<vtkDelaunay3D> delaunay1 =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay1->SetInputConnection(sphereSource1->GetOutputPort());
  delaunay1->Update();
  
  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(5,0,0);
  sphereSource2->Update();

  vtkSmartPointer<vtkDelaunay3D> delaunay2 =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay2->SetInputConnection(sphereSource2->GetOutputPort());
  delaunay2->Update();
  
  vtkSmartPointer<vtkAppendFilter> appendFilter =
    vtkSmartPointer<vtkAppendFilter>::New();
  appendFilter->AddInputConnection(delaunay1->GetOutputPort());
  appendFilter->AddInputConnection(delaunay2->GetOutputPort());
  appendFilter->Update();

  vtkSmartPointer<vtkConnectivityFilter> connectivityFilter =
    vtkSmartPointer<vtkConnectivityFilter>::New();
  connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
  connectivityFilter->SetExtractionModeToAllRegions();
  connectivityFilter->ColorRegionsOn();
  connectivityFilter->Update();

  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(connectivityFilter->GetOutputPort());
  mapper->Update();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);
  renwin->Render();

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
