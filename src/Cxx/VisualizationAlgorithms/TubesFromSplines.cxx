#include <vtkSmartPointer.h>

#include <vtkParametricFunctionSource.h>
#include <vtkTupleInterpolator.h>
#include <vtkTubeFilter.h>
#include <vtkParametricSpline.h>

#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>

int main(int, char *[])
{
  auto points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertPoint(0,1,0,0);
  points->InsertPoint(1,2,0,0);
  points->InsertPoint(2,3,1,0);
  points->InsertPoint(3,4,1,0);
  points->InsertPoint(4,5,0,0);
  points->InsertPoint(5,6,0,0);

  // Fit a spline to the points
  auto spline =
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetPoints(points);
  auto functionSource =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->SetUResolution(10 * points->GetNumberOfPoints());
  functionSource->Update();

  // Interpolate the scalars
  double rad;
  auto interpolatedRadius =
    vtkSmartPointer<vtkTupleInterpolator> ::New();
  interpolatedRadius->SetInterpolationTypeToLinear();
  interpolatedRadius->SetNumberOfComponents(1);
  rad = .2; interpolatedRadius->AddTuple(0,&rad);
  rad = .2; interpolatedRadius->AddTuple(1,&rad);
  rad = .2; interpolatedRadius->AddTuple(2,&rad);
  rad = .1; interpolatedRadius->AddTuple(3,&rad);
  rad = .1; interpolatedRadius->AddTuple(4,&rad);
  rad = .1; interpolatedRadius->AddTuple(5,&rad);

  // Generate the radius scalars
  auto tubeRadius =
    vtkSmartPointer<vtkDoubleArray>::New();
  unsigned int n = functionSource->GetOutput()->GetNumberOfPoints();
  tubeRadius->SetNumberOfTuples(n);
  tubeRadius->SetName("TubeRadius");
  auto tMin = interpolatedRadius->GetMinimumT();
  auto tMax = interpolatedRadius->GetMaximumT();
  double r;
  for (unsigned int i = 0; i < n; ++i)
  {
    auto t = (tMax - tMin) / (n - 1) * i + tMin;
    interpolatedRadius->InterpolateTuple(t, &r);
    tubeRadius->SetTuple1(i, r);
  }

  // Add the scalars to the polydata
  auto tubePolyData = functionSource->GetOutput();
  tubePolyData->GetPointData()->AddArray(tubeRadius);
  tubePolyData->GetPointData()->SetActiveScalars("TubeRadius");

  // Create the tubes
  auto tuber =
    vtkSmartPointer<vtkTubeFilter>::New();
  tuber->SetInputData(tubePolyData);
  tuber->SetNumberOfSides(20);
  tuber->SetVaryRadiusToVaryRadiusByAbsoluteScalar();

  //--------------
  // Setup actors and mappers
  auto lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputData(tubePolyData);
  lineMapper->SetScalarRange(tubePolyData->GetScalarRange());

  auto tubeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  tubeMapper->SetInputConnection(tuber->GetOutputPort());
  tubeMapper->SetScalarRange(tubePolyData->GetScalarRange());

  auto lineActor =
    vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  lineActor->GetProperty()->SetLineWidth(3);
  auto tubeActor =
    vtkSmartPointer<vtkActor>::New();
  tubeActor->SetMapper(tubeMapper);
  tubeActor->GetProperty()->SetOpacity(.6);

  // Setup render window, renderer, and interactor
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(lineActor);
  renderer->AddActor(tubeActor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
