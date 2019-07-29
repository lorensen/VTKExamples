#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRibbonFilter.h>

int main(int, char*[])
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // Spiral parameters
  unsigned int nV = 256; // No. of vertices
  double rS = 2;         // Spiral radius
  unsigned int nCyc = 3; // No. of spiral cycles
  double h = 10;         // Height

  unsigned int i;

  // Create points and cells for a spiral
  auto points = vtkSmartPointer<vtkPoints>::New();
  for (i = 0; i < nV; i++)
  {
    // Spiral coordinates
    auto vX = rS * cos(2 * vtkMath::Pi() * nCyc * i / (nV - 1));
    auto vY = rS * sin(2 * vtkMath::Pi() * nCyc * i / (nV - 1));
    auto vZ = h * i / nV;
    points->InsertPoint(i, vX, vY, vZ);
  }

  auto lines = vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(nV);
  for (i = 0; i < nV; i++)
  {
    lines->InsertCellPoint(i);
  }

  auto polyData = vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);
  polyData->SetLines(lines);

  // Create a mapper and actor
  auto lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputData(polyData);

  auto lineActor = vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  lineActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  lineActor->GetProperty()->SetLineWidth(3);

  // Create a ribbon around the line
  auto ribbonFilter = vtkSmartPointer<vtkRibbonFilter>::New();
  ribbonFilter->SetInputData(polyData);
  ribbonFilter->SetWidth(.4);

  // Create a mapper and actor
  auto ribbonMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  ribbonMapper->SetInputConnection(ribbonFilter->GetOutputPort());

  auto ribbonActor = vtkSmartPointer<vtkActor>::New();
  ribbonActor->SetMapper(ribbonMapper);

  // Create a renderer, render window, and interactor
  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(ribbonActor);
  renderer->AddActor(lineActor);

  // Render and interact
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

  // Generate an interesting view
  renderer->GetActiveCamera()->Azimuth(40);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
