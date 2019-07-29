// This example shows how to manually create a structured grid.
// The basic idea is to instantiate vtkStructuredGrid, set its dimensions,
// and then assign points defining the grid coordinate. The number of
// points must equal the number of points implicit in the dimensions
// (i.e., dimX*dimY*dimZ). Also, data attributes (either point or cell)
// can be added to the dataset.
//
//
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDoubleArray.h>
#include <vtkHedgeHog.h>
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

int main(int, char*[])
{
  double x[3], v[3], rMin = 0.5, rMax = 1.0, deltaRad, deltaZ;
  double radius, theta;
  static int dims[3] = {13, 11, 11};

  // Create the structured grid.
  vtkSmartPointer<vtkStructuredGrid> sgrid =
      vtkSmartPointer<vtkStructuredGrid>::New();
  sgrid->SetDimensions(dims);

  // We also create the points and vectors. The points
  // form a hemi-cylinder of data.
  vtkSmartPointer<vtkDoubleArray> vectors =
      vtkSmartPointer<vtkDoubleArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetNumberOfTuples(dims[0] * dims[1] * dims[2]);
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->Allocate(dims[0] * dims[1] * dims[2]);

  deltaZ = 2.0 / (dims[2] - 1);
  deltaRad = (rMax - rMin) / (dims[1] - 1);
  v[2] = 0.0;
  for (auto k = 0; k < dims[2]; k++)
  {
    x[2] = -1.0 + k * deltaZ;
    auto kOffset = k * dims[0] * dims[1];
    for (auto j = 0; j < dims[1]; j++)
    {
      radius = rMin + j * deltaRad;
      auto jOffset = j * dims[0];
      for (auto i = 0; i < dims[0]; i++)
      {
        theta = i * vtkMath::RadiansFromDegrees(15.0);
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

  // We create a simple pipeline to display the data.
  vtkSmartPointer<vtkHedgeHog> hedgehog = vtkSmartPointer<vtkHedgeHog>::New();
  hedgehog->SetInputData(sgrid);
  hedgehog->SetScaleFactor(0.1);

  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> sgridMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sgridMapper->SetInputConnection(hedgehog->GetOutputPort());
  vtkSmartPointer<vtkActor> sgridActor = vtkSmartPointer<vtkActor>::New();
  sgridActor->SetMapper(sgridMapper);
  sgridActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

  // Create the usual rendering stuff
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(sgridActor);
  renderer->SetBackground(colors->GetColor3d("Beige").GetData());
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Dolly(1.25);
  renWin->SetSize(640, 480);

  // interact with data
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}
