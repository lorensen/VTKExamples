#include <vtkSmartPointer.h>

#include <vtkDataSetAttributes.h>
#include <vtkGeoAssignCoordinates.h>
#include <vtkDoubleArray.h>
#include <vtkGraphMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMutableDirectedGraph.h>

int main(int, char* [])
{

  vtkSmartPointer<vtkMutableDirectedGraph> g =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  vtkSmartPointer<vtkDoubleArray> latitude =
    vtkSmartPointer<vtkDoubleArray>::New();
  latitude->SetName("latitude");

  vtkSmartPointer<vtkDoubleArray> longitude =
    vtkSmartPointer<vtkDoubleArray>::New();
  longitude->SetName("longitude");

  for(int lat = -90; lat <= 90; lat += 10)
  {
    for(int lon = -180; lon <= 180; lon += 20)
    {
      g->AddVertex();
      latitude->InsertNextValue(lat);
      longitude->InsertNextValue(lon);
    }
  }

  g->GetVertexData()->AddArray(latitude);
  g->GetVertexData()->AddArray(longitude);

  vtkSmartPointer<vtkGeoAssignCoordinates> assign =
    vtkSmartPointer<vtkGeoAssignCoordinates>::New();
  assign->SetInputData(g);
  assign->SetLatitudeArrayName("latitude");
  assign->SetLongitudeArrayName("longitude");
  assign->SetGlobeRadius(1.0);
  assign->Update();

  vtkSmartPointer<vtkGraphMapper> mapper =
    vtkSmartPointer<vtkGraphMapper>::New();
  mapper->SetInputConnection(assign->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->AddActor(actor);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkRenderWindow> win =
    vtkSmartPointer<vtkRenderWindow>::New();
  win->AddRenderer(ren);
  win->SetInteractor(iren);
  ren->ResetCamera();

  win->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
