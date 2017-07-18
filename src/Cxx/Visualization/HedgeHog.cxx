#include "vtkSmartPointer.h"
#include "vtkHedgeHog.h"

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkFloatArray.h"
#include "vtkMath.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStructuredGrid.h"

#include <vtkNamedColors.h>

static void CreateData(vtkStructuredGrid* sgrid);

int main(int, char*[])
{
  // Create the structured grid.
  vtkSmartPointer<vtkStructuredGrid> sgrid =
    vtkSmartPointer<vtkStructuredGrid>::New();
  CreateData(sgrid);

  // We create a simple pipeline to display the data.
  vtkSmartPointer<vtkHedgeHog> hedgehog =
    vtkSmartPointer<vtkHedgeHog>::New();
  hedgehog->SetInputData(sgrid);
  hedgehog->SetScaleFactor(0.1);

  vtkSmartPointer<vtkPolyDataMapper> sgridMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sgridMapper->SetInputConnection(hedgehog->GetOutputPort());

  vtkSmartPointer<vtkActor> sgridActor =
    vtkSmartPointer<vtkActor>::New();
  sgridActor->SetMapper(sgridMapper);
  sgridActor->GetProperty()->SetColor(0,0,0);

  // Create the usual rendering stuff
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(sgridActor);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  renderer->GradientBackgroundOn();
  renderer->SetBackground(colors->GetColor3d("Aqua").GetData());
  renderer->SetBackground2(colors->GetColor3d("CadetBlue").GetData());

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Zoom(1.25);
  renWin->SetSize(300,300);

  // interact with data
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}

void CreateData(vtkStructuredGrid* sgrid)
{
  int i, j, k, kOffset, jOffset, offset;
  float x[3], v[3], rMin=0.5, rMax=1.0, deltaRad, deltaZ;
  float radius, theta;
  static int dims[3]={13,11,11};
  sgrid->SetDimensions(dims);

  // We also create the points and vectors. The points
  // form a hemi-cylinder of data.
  vtkSmartPointer<vtkFloatArray> vectors =
    vtkSmartPointer<vtkFloatArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetNumberOfTuples(dims[0]*dims[1]*dims[2]);

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->Allocate(dims[0]*dims[1]*dims[2]);

  deltaZ = 2.0 / (dims[2]-1);
  deltaRad = (rMax-rMin) / (dims[1]-1);
  v[2]=0.0;
  for ( k=0; k<dims[2]; k++)
  {
    x[2] = -1.0 + k*deltaZ;
    kOffset = k * dims[0] * dims[1];
    for (j=0; j<dims[1]; j++)
    {
      radius = rMin + j*deltaRad;
      jOffset = j * dims[0];
      for (i=0; i<dims[0]; i++)
      {
        theta = i * vtkMath::RadiansFromDegrees(15.0);
        x[0] = radius * cos(theta);
        x[1] = radius * sin(theta);
        v[0] = -x[1];
        v[1] = x[0];
        offset = i + jOffset + kOffset;
        points->InsertPoint(offset,x);
        vectors->InsertTuple(offset,v);
      }
    }
  }
  sgrid->SetPoints(points);

  sgrid->GetPointData()->SetVectors(vectors);
}
