#include <vtkSmartPointer.h>

#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>
#include <vtkAreaPicker.h>
#include <vtkCallbackCommand.h>
#include <vtkProp3DCollection.h>

#include <vtkNamedColors.h>

namespace
{
void PickCallbackFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData );
}

int main(int, char *[])
{
  // Create a set of points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> vertices =
    vtkSmartPointer<vtkCellArray>::New();
  vtkIdType pid[1];
  pid[0] = points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );
  pid[0] = points->InsertNextPoint ( 0.0, 0.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );
  pid[0] = points->InsertNextPoint ( 0.0, 1.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );

  // Create a polydata
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints ( points );
  polydata->SetVerts ( vertices );

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polydata);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetPointSize(5);
  actor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkAreaPicker> areaPicker =
    vtkSmartPointer<vtkAreaPicker>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->SetPicker(areaPicker);

  renderer->AddActor(actor);

  renderer->SetBackground(colors->GetColor3d("Gold").GetData());

  renderWindow->Render();

  // For vtkInteractorStyleRubberBandPick - use 'r' and left-mouse to draw a selection box used to pick
  vtkSmartPointer<vtkInteractorStyleRubberBandPick> style =
    vtkSmartPointer<vtkInteractorStyleRubberBandPick>::New();

  // For vtkInteractorStyleTrackballCamera - use 'p' to pick at the current mouse position
//  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
//    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
  style->SetCurrentRenderer(renderer);
  renderWindowInteractor->SetInteractorStyle( style );

  vtkSmartPointer<vtkCallbackCommand> pickCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  pickCallback->SetCallback ( PickCallbackFunction );

  areaPicker->AddObserver ( vtkCommand::EndPickEvent, pickCallback );

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace
{
void PickCallbackFunction(vtkObject* caller,
                          long unsigned int vtkNotUsed(eventId),
                          void* vtkNotUsed(clientData),
                          void* vtkNotUsed(callData))
{
  std::cout << "Pick." << std::endl;
  vtkAreaPicker* areaPicker = static_cast<vtkAreaPicker*>(caller);
  vtkProp3DCollection* props = areaPicker->GetProp3Ds();
  props->InitTraversal();

  for(vtkIdType i = 0; i < props->GetNumberOfItems(); i++)
  {
    vtkProp3D* prop = props->GetNextProp3D();
    std::cout << "Picked prop: " << prop << std::endl;
  }
}
}
