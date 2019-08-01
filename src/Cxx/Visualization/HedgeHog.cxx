#include <vtkHedgeHog.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkFloatArray.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>

namespace {

void CreateData(vtkStructuredGrid* sgrid);
}

int main(int, char*[])
{
  // Create the structured grid.
  auto sgrid =
    vtkSmartPointer<vtkStructuredGrid>::New();
  CreateData(sgrid);

  // We create a simple pipeline to display the data.
  auto hedgehog =
    vtkSmartPointer<vtkHedgeHog>::New();
  hedgehog->SetInputData(sgrid);
  hedgehog->SetScaleFactor(0.1);

  auto sgridMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sgridMapper->SetInputConnection(hedgehog->GetOutputPort());

  auto sgridActor =
    vtkSmartPointer<vtkActor>::New();
  sgridActor->SetMapper(sgridMapper);
  sgridActor->GetProperty()->SetColor(0, 0, 0);

  // Create the usual rendering stuff
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);

  auto iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(sgridActor);

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  renderer->GradientBackgroundOn();
  renderer->SetBackground(colors->GetColor3d("Aqua").GetData());
  renderer->SetBackground2(colors->GetColor3d("CadetBlue").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Zoom(1.25);
  renWin->SetSize(300, 300);

  // interact with data
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace {

void CreateData(vtkStructuredGrid* sgrid)
{
  // int i, j, k, kOffset, jOffset, offset;
  float x[3], v[3], rMin = 0.5, rMax = 1.0;
  // float radius, theta;
  static int dims[3]{13, 11, 11};
  sgrid->SetDimensions(dims);

  // We also create the points and vectors. The points
  // form a hemi-cylinder of data.
  auto vectors =
    vtkSmartPointer<vtkFloatArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetNumberOfTuples(dims[0] * dims[1] * dims[2]);

  auto points =
    vtkSmartPointer<vtkPoints>::New();
  points->Allocate(dims[0] * dims[1] * dims[2]);

  auto deltaZ = 2.0 / (dims[2] - 1);
  auto deltaRad = (rMax - rMin) / (dims[1] - 1);
  v[2] = 0.0;
  for (auto k = 0; k < dims[2]; k++)
  {
    x[2] = -1.0 + k * deltaZ;
    auto kOffset = k * dims[0] * dims[1];
    for (auto j = 0; j < dims[1]; j++)
    {
      auto radius = rMin + j * deltaRad;
      auto jOffset = j * dims[0];
      for (auto i = 0; i < dims[0]; i++)
      {
        auto theta = i * vtkMath::RadiansFromDegrees(15.0);
        x[0] = radius * cos(theta);
        x[1] = radius * sin(theta);
        v[0] = -x[1];
        v[1] = x[0];
        auto offset = i + jOffset + kOffset;
        points->InsertPoint(offset, x);
        vectors->InsertTuple(offset, v);
      }
    }
  }
  sgrid->SetPoints(points);

  sgrid->GetPointData()->SetVectors(vectors);
}
} // namespace
