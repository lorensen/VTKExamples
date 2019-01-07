#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkMath.h>
#include <vtkLine.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRibbonFilter.h>

int main(int, char *[])
{
  // Spiral parameters
  unsigned int nV = 256;      // No. of vertices
  double vX, vY, vZ;
  double rS = 2;              // Spiral radius
  unsigned int nCyc = 3;      // No. of spiral cycles
  double h = 10;              // Height

  unsigned int i;

  // Create points and cells for a spiral
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  for(i = 0; i < nV; i++)
  {
    // Spiral coordinates
    vX = rS * cos(2 * vtkMath::Pi() * nCyc * i / (nV - 1));
    vY = rS * sin(2 * vtkMath::Pi() * nCyc * i / (nV - 1));
    vZ = h * i / nV;
    points->InsertPoint(i, vX, vY, vZ);
  }

  vtkSmartPointer<vtkCellArray> lines =
    vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(nV);
  for (i = 0; i < nV; i++)
  {
    lines->InsertCellPoint(i);
  }

  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);
  polyData->SetLines(lines);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputData(polyData);

  vtkSmartPointer<vtkActor> lineActor =
    vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  lineActor->GetProperty()->SetColor(.8, .4, .2);
  lineActor->GetProperty()->SetLineWidth(3);

  // Create a ribbon around the line
  vtkSmartPointer<vtkRibbonFilter> ribbonFilter =
    vtkSmartPointer<vtkRibbonFilter>::New();
  ribbonFilter->SetInputData(polyData);
  ribbonFilter->SetWidth(.4);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> ribbonMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  ribbonMapper->SetInputConnection(ribbonFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> ribbonActor =
    vtkSmartPointer<vtkActor>::New();
  ribbonActor->SetMapper(ribbonMapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(ribbonActor);
  renderer->AddActor(lineActor);

  // Render and interact
  renderer->SetBackground(.2, .3, .4);

  // Generate an interesting view
  renderer->GetActiveCamera()->Azimuth(40);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
