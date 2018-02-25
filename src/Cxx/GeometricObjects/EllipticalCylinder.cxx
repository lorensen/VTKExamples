#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyLine.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int /* argc */, char * /* argv */ [])
{

  double angle = 0;
  double r1, r2;
  double centerX, centerY;
  r1 = 50;
  r2 = 30;
  centerX = 10.0;
  centerY = 5.0;

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  int id = 0;
  while (angle <= 2.0 * vtkMath::Pi() + (vtkMath::Pi() / 60.0))
  {
    points->InsertNextPoint(r1 * cos(angle) + centerX,
                            r2 * sin(angle) + centerY,
                            0.0);
    angle = angle + (vtkMath::Pi() / 60.0);
    ++id;
  }

  vtkSmartPointer<vtkPolyLine> line =
    vtkSmartPointer<vtkPolyLine>::New();
  line->GetPointIds()->SetNumberOfIds(id);
  for(unsigned int i = 0; i < static_cast<unsigned int>(id); ++i)
  {
    line->GetPointIds()->SetId(i,i);
  }

  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line);

  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);
  polyData->SetLines(lines);

  vtkSmartPointer<vtkLinearExtrusionFilter> extrude =
    vtkSmartPointer<vtkLinearExtrusionFilter>::New();
  extrude->SetInputData(polyData);
  extrude->SetExtrusionTypeToNormalExtrusion();
  extrude->SetVector(0, 0, 100.0);
  extrude->Update();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputData(polyData);

  vtkSmartPointer<vtkActor> lineActor =
    vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  lineActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(extrude->GetOutputPort());

  vtkSmartPointer<vtkProperty> back =
    vtkSmartPointer<vtkProperty>::New();
  back->SetColor(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  actor->SetBackfaceProperty(back);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
  ren->AddActor(actor);
  ren->AddActor(lineActor);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetWindowName("Elliptical Cylinder");
  renWin->AddRenderer(ren);
  renWin->SetSize(600, 600);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  iren->SetInteractorStyle(style);

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition (0, 1, 0);
  camera->SetFocalPoint (0, 0, 0);
  camera->SetViewUp (0, 0, 1);
  camera->Azimuth(30);
  camera->Elevation(30);


  ren->SetActiveCamera(camera);
  ren->ResetCamera();
  ren->ResetCameraClippingRange();

  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
