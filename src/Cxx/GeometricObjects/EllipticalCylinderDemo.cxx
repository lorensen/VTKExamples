#include <vtkActor.h>
#include <vtkArrowSource.h>
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
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTubeFilter.h>

int main(int argc, char *argv[])
{
  double nx = 0.0;
  double ny = 0.0;
  double nz = 100.0;

  if (argc > 3)
  {
    nx = atof(argv[1]);
    ny = atof(argv[2]);
    nz = atof(argv[3]);
  }
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

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
  extrude->SetVector(nx, ny, nz);
  extrude->Update();

  // Create an oriented arrow
  double startPoint[3], endPoint[3];
  startPoint[0] = centerX;
  startPoint[1] = centerY;
  startPoint[2] = 0.0;
  endPoint[0] = startPoint[0] + extrude->GetVector()[0];
  endPoint[1] = startPoint[1] + extrude->GetVector()[1];
  endPoint[2] = startPoint[2] + extrude->GetVector()[2];

  // Compute a basis
  double normalizedX[3];
  double normalizedY[3];
  double normalizedZ[3];

  // The X axis is a vector from start to end
  vtkMath::Subtract(endPoint, startPoint, normalizedX);
  double length = vtkMath::Norm(normalizedX);
  vtkMath::Normalize(normalizedX);

  // The Z axis is an arbitrary vector cross X
  double arbitrary[3];
  arbitrary[0] = vtkMath::Random(-10,10);
  arbitrary[1] = vtkMath::Random(-10,10);
  arbitrary[2] = vtkMath::Random(-10,10);
  vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
  vtkMath::Normalize(normalizedZ);

  // The Y axis is Z cross X
  vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();

  // Create the direction cosine matrix
  matrix->Identity();
  for (unsigned int i = 0; i < 3; i++)
  {
    matrix->SetElement(i, 0, normalizedX[i]);
    matrix->SetElement(i, 1, normalizedY[i]);
    matrix->SetElement(i, 2, normalizedZ[i]);
  }

  // Apply the transforms
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(startPoint);
  transform->Concatenate(matrix);
  transform->Scale(length, length, length);

  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
  arrowSource->SetTipResolution(31);
  arrowSource->SetShaftResolution(21);

  // Transform the polydata
  vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformPD->SetTransform(transform);
  transformPD->SetInputConnection(arrowSource->GetOutputPort());

  //Create a mapper and actor for the arrow
  vtkSmartPointer<vtkPolyDataMapper> arrowMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  arrowMapper->SetInputConnection(transformPD->GetOutputPort());

  vtkSmartPointer<vtkActor> arrowActor =
    vtkSmartPointer<vtkActor>::New();
  arrowActor->SetMapper(arrowMapper);
  arrowActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

  vtkSmartPointer<vtkTubeFilter> tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputData(polyData);
  tubes->SetRadius(2.0);
  tubes->SetNumberOfSides(21);

  vtkSmartPointer<vtkPolyDataMapper> lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputConnection(tubes->GetOutputPort());

  vtkSmartPointer<vtkActor> lineActor =
    vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  lineActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(extrude->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  actor->GetProperty()->SetOpacity(.7);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
  ren->AddActor(actor);
  ren->AddActor(lineActor);
  ren->AddActor(arrowActor);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetWindowName("Elliptical Cylinder Demo");
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
