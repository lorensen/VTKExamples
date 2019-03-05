#include <vtkSmartPointer.h>
#include <vtkPlaneSource.h>
#include <vtkSphereSource.h>
#include <vtkArrowSource.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkNamedColors.h>
#include <vtkColor.h>
#include <vtkLegendBoxActor.h>

#include <vtkMinimalStandardRandomSequence.h>

#include <array>

namespace
{
vtkSmartPointer<vtkPolyData> CreateArrow(
  double &length,
  std::array<double,3> &startPoint,
  std::array<double,3> &endPoint);
}

int main(int, char *argv[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");
  vtkColor3d legendBackgroundColor = colors->GetColor3d("Black");
  vtkColor3d originColor = colors->GetColor3d("Tomato");
  vtkColor3d centerColor = colors->GetColor3d("Banana");
  vtkColor3d point1Color = colors->GetColor3d("Peru");
  vtkColor3d point2Color = colors->GetColor3d("Bisque");
  vtkColor3d xAxisColor = colors->GetColor3d("lime");
  vtkColor3d yAxisColor = colors->GetColor3d("orange");
  vtkColor3d normalColor = colors->GetColor3d("Raspberry");

// Create actors
  vtkSmartPointer<vtkPlaneSource> planeSource =
    vtkSmartPointer<vtkPlaneSource>::New();
  planeSource->SetOrigin(0.0, 0.0, 0.0);
  planeSource->SetPoint1(1,0, 0);
  planeSource->SetPoint2(0,1.0, 0);
  planeSource->Update();

  std::array<double, 6> bounds;
  planeSource->GetOutput()->GetBounds(bounds.data());
  double length = std::max(bounds[1] - bounds[0], bounds[3] - bounds[2]);

  vtkSmartPointer<vtkPolyDataMapper> planeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(planeSource->GetOutputPort());
  vtkSmartPointer<vtkActor> planeActor =
    vtkSmartPointer<vtkActor>::New();
  planeActor->SetMapper(planeMapper);

  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(length * .04);
  vtkSmartPointer<vtkPolyDataMapper> originMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> originActor =
    vtkSmartPointer<vtkActor>::New();
  originActor->SetPosition(planeSource->GetOrigin());
  originActor->SetMapper(originMapper);
  originActor->GetProperty()->SetDiffuseColor(originColor.GetData());

  vtkSmartPointer<vtkPolyDataMapper> centerMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  centerMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> centerActor =
    vtkSmartPointer<vtkActor>::New();
  centerActor->SetPosition(planeSource->GetCenter());
  centerActor->SetMapper(centerMapper);
  centerActor->GetProperty()->SetDiffuseColor(centerColor.GetData());

  vtkSmartPointer<vtkPolyDataMapper> point1Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  point1Mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> point1Actor =
    vtkSmartPointer<vtkActor>::New();
  point1Actor->SetPosition(planeSource->GetPoint1());
  point1Actor->SetMapper(point1Mapper);
  point1Actor->GetProperty()->SetDiffuseColor(point1Color.GetData());

  vtkSmartPointer<vtkPolyDataMapper> point2Mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  point2Mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> point2Actor =
    vtkSmartPointer<vtkActor>::New();
  point2Actor->SetPosition(planeSource->GetPoint2());
  point2Actor->SetMapper(point2Mapper);
  point2Actor->GetProperty()->SetDiffuseColor(point2Color.GetData());

  std::array<double, 3> center;
  std::array<double, 3> origin;
  std::array<double, 3> normal;
  std::array<double, 3> point1;
  std::array<double, 3> point2;
  for (auto i = 0; i < 3; ++i)
  {
    point1[i] = planeSource->GetPoint1()[i];
    point2[i] = planeSource->GetPoint2()[i];
    origin[i] = planeSource->GetOrigin()[i];
    center[i] = planeSource->GetCenter()[i];
    normal[i] = planeSource->GetNormal()[i] * length;
  }
  vtkSmartPointer<vtkPolyData> xAxisPolyData =
    CreateArrow(length, origin, point1);
  vtkSmartPointer<vtkPolyDataMapper> xAxisMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  xAxisMapper->SetInputData(xAxisPolyData);
  vtkSmartPointer<vtkActor> xAxisActor =
    vtkSmartPointer<vtkActor>::New();
  xAxisActor->SetMapper(xAxisMapper);
  xAxisActor->GetProperty()->SetDiffuseColor(xAxisColor.GetData());

  vtkSmartPointer<vtkPolyData> yAxisPolyData =
    CreateArrow(length, origin, point2);
  vtkSmartPointer<vtkPolyDataMapper> yAxisMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  yAxisMapper->SetInputData(yAxisPolyData);
  vtkSmartPointer<vtkActor> yAxisActor =
    vtkSmartPointer<vtkActor>::New();
  yAxisActor->SetMapper(yAxisMapper);
  yAxisActor->GetProperty()->SetDiffuseColor(yAxisColor.GetData());

  vtkSmartPointer<vtkPolyData> normalPolyData =
    CreateArrow(length, origin, normal);
  vtkSmartPointer<vtkPolyDataMapper> normalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  normalMapper->SetInputData(normalPolyData);
  vtkSmartPointer<vtkActor> normalActor =
    vtkSmartPointer<vtkActor>::New();
  normalActor->SetMapper(normalMapper);
  normalActor->GetProperty()->SetDiffuseColor(normalColor.GetData());

// Create the RenderWindow, Renderer
//
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkLegendBoxActor> legend =
      vtkSmartPointer<vtkLegendBoxActor>::New();
  legend->SetNumberOfEntries(7);
  legend->UseBackgroundOn();
  legend->SetBackgroundColor(legendBackgroundColor.GetData());
  legend->GetPositionCoordinate()->SetValue(.7, .7);
  legend->GetPosition2Coordinate()->SetValue(.3, .3);
  int entry = 0;
  legend->SetEntry(entry++, sphereSource->GetOutput(), "center",
                   centerColor.GetData());
  legend->SetEntry(entry++, sphereSource->GetOutput(), "origin",
                   originColor.GetData());
  legend->SetEntry(entry++, sphereSource->GetOutput(), "point1",
                   point1Color.GetData());
  legend->SetEntry(entry++, sphereSource->GetOutput(), "point2",
                   point2Color.GetData());
  legend->SetEntry(entry++, xAxisPolyData, "xAxis",
                   xAxisColor.GetData());
  legend->SetEntry(entry++, xAxisPolyData, "yAxis",
                   yAxisColor.GetData());
  legend->SetEntry(entry++, xAxisPolyData, "normal",
                   normalColor.GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->SetBackground(backgroundColor.GetData());
  renderer->AddActor(planeActor);
  renderer->AddActor(originActor);
  renderer->AddActor(centerActor);
  renderer->AddActor(point1Actor);
  renderer->AddActor(point2Actor);
  renderer->AddActor(xAxisActor);
  renderer->AddActor(yAxisActor);
  renderer->AddActor(normalActor);
  renderer->AddActor(legend);

  renderWindow->Render();
  renderer->GetActiveCamera()->SetPosition(1, 0, 0);
  renderer->GetActiveCamera()->SetFocalPoint(0, 1, 0);
  renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
vtkSmartPointer<vtkPolyData> CreateArrow(
  double &pdLength,
  std::array<double,3> &startPoint,
  std::array<double,3> &endPoint)
{
  vtkSmartPointer<vtkPolyData> polyData;

  //Create an arrow.
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
  arrowSource->SetShaftRadius(pdLength * .01);
  arrowSource->SetShaftResolution(20);
  arrowSource->SetTipLength(pdLength * .1);
  arrowSource->SetTipRadius(pdLength * .05);
  arrowSource->SetTipResolution(20);

  // Compute a basis
  std::array<double, 3> normalizedX;
  std::array<double, 3> normalizedY;
  std::array<double, 3> normalizedZ;

  // The X axis is a vector from start to end
  vtkMath::Subtract(endPoint.data(), startPoint.data(), normalizedX.data());
  double length = vtkMath::Norm(normalizedX.data());
  vtkMath::Normalize(normalizedX.data());

  // The Z axis is an arbitrary vector cross X
  vtkSmartPointer<vtkMinimalStandardRandomSequence> rng =
    vtkSmartPointer<vtkMinimalStandardRandomSequence>::New();
  rng->SetSeed(8775070); // For testing.

  std::array<double, 3> arbitrary;
  for (auto i = 0; i < 3; ++i)
  {
    rng->Next();
    arbitrary[i] = rng->GetRangeValue(-10, 10);
  }
  vtkMath::Cross(normalizedX.data(), arbitrary.data(), normalizedZ.data());
  vtkMath::Normalize(normalizedZ.data());

  // The Y axis is Z cross X
  vtkMath::Cross(normalizedZ.data(), normalizedX.data(), normalizedY.data());
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();

  // Create the direction cosine matrix
  matrix->Identity();
  for (auto i = 0; i < 3; i++)
  {
    matrix->SetElement(i, 0, normalizedX[i]);
    matrix->SetElement(i, 1, normalizedY[i]);
    matrix->SetElement(i, 2, normalizedZ[i]);
  }

  // Apply the transforms
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(startPoint.data());
  transform->Concatenate(matrix);
  transform->Scale(length, length, length);

  // Transform the polydata
  vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformPD->SetTransform(transform);
  transformPD->SetInputConnection(arrowSource->GetOutputPort());
  transformPD->Update();
  polyData = transformPD->GetOutput();
  return polyData;
}
}
