//
// Brute force computation of Bessel functions. Might be better to create a
// filter (or source) object. Might also consider vtkSampleFunction.

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkNamedColors.h>
#include <vtkPlaneSource.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkWarpScalar.h>

int main(int, char*[])
{

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto ren =
    vtkSmartPointer<vtkRenderer>::New();
  auto renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);

  auto iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // create plane to warp
  auto plane =
    vtkSmartPointer<vtkPlaneSource>::New();
  plane->SetResolution(300, 300);

  auto transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Scale(10.0, 10.0, 1.0);

  auto transF =
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transF->SetInputConnection(plane->GetOutputPort());
  transF->SetTransform(transform);
  transF->Update();

  // compute Bessel function and derivatives. This portion could be
  // encapsulated into source or filter object.
  //
  auto input = transF->GetOutput();
  auto numPts = input->GetNumberOfPoints();

  auto newPts =
    vtkSmartPointer<vtkPoints>::New();
  newPts->SetNumberOfPoints(numPts);

  auto derivs =
    vtkSmartPointer<vtkDoubleArray>::New();
  derivs->SetNumberOfTuples(numPts);

  auto bessel =
    vtkSmartPointer<vtkPolyData>::New();
  bessel->CopyStructure(input);
  bessel->SetPoints(newPts);
  bessel->GetPointData()->SetScalars(derivs);

  double x[3];

  for (auto i = 0; i < numPts; i++)
  {
    input->GetPoint(i, x);
    auto r = sqrt(static_cast<double>(x[0] * x[0]) + x[1] * x[1]);
    x[2] = exp(-r) * cos(10.0 * r);
    newPts->SetPoint(i, x);
    auto deriv = -exp(-r) * (cos(10.0 * r) + 10.0 * sin(10.0 * r));
    derivs->SetValue(i, deriv);
  }

  // warp plane
  auto warp =
    vtkSmartPointer<vtkWarpScalar>::New();
  warp->SetInputData(bessel);
  warp->XYPlaneOn();
  warp->SetScaleFactor(0.5);

  // mapper and actor
  auto mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(warp->GetOutputPort());
  double tmp[2];
  bessel->GetScalarRange(tmp);
  mapper->SetScalarRange(tmp[0], tmp[1]);

  auto carpet =
    vtkSmartPointer<vtkActor>::New();
  carpet->SetMapper(mapper);

  // assign our actor to the renderer
  ren->AddActor(carpet);
  ren->SetBackground(colors->GetColor3d("Beige").GetData());
  renWin->SetSize(640, 480);

  // draw the resulting scene
  ren->ResetCamera();
  ren->GetActiveCamera()->Zoom(1.4);
  ren->GetActiveCamera()->Elevation(-55);
  ren->GetActiveCamera()->Azimuth(25);
  ren->ResetCameraClippingRange();
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
