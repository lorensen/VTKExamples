#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkStripper.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>

#include <vtkNamedColors.h>
#include <vtkColor.h>

int main (int, char *[])
{
  // Define colors for example
  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkColor3d lineColor = colors->GetColor3d("peacock");
  vtkColor3d modelColor = colors->GetColor3d("silver");
  vtkColor3d backgroundColor = colors->GetColor3d("wheat");

  auto modelSource =
    vtkSmartPointer<vtkSphereSource>::New();

  auto plane =
    vtkSmartPointer<vtkPlane>::New();

  auto cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetInputConnection(modelSource->GetOutputPort());
  cutter->SetCutFunction(plane);
  cutter->GenerateValues(10, -.5, .5);

  auto modelMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  modelMapper->SetInputConnection(modelSource->GetOutputPort());

  auto model =
    vtkSmartPointer<vtkActor>::New();
  model->SetMapper(modelMapper);
  model->GetProperty()->SetDiffuseColor(modelColor.GetData());
  model->GetProperty()->SetInterpolationToFlat();

  auto stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(cutter->GetOutputPort());
  stripper->JoinContiguousSegmentsOn();

  auto linesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  linesMapper->SetInputConnection(stripper->GetOutputPort());

  auto lines =
    vtkSmartPointer<vtkActor>::New();
  lines->SetMapper(linesMapper);
  lines->GetProperty()->SetDiffuseColor(lineColor.GetData());
  lines->GetProperty()->SetLineWidth(3.0);

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer
  renderer->AddActor(model);
  renderer->AddActor(lines);
  renderer->SetBackground(backgroundColor.GetData());

  // This starts the event loop and as a side effect causes an initial
  // render.
  renderWindow->Render();
  interactor->Start();


  // Extract the lines from the polydata
  vtkIdType numberOfLines = cutter->GetOutput()->GetNumberOfLines();


  std::cout << "-----------Lines without using vtkStripper" << std::endl;
  std::cout << "There are "
            << numberOfLines
            << " lines in the polydata" << std::endl;

  numberOfLines = stripper->GetOutput()->GetNumberOfLines();
  vtkPoints *points = stripper->GetOutput()->GetPoints();
  vtkCellArray *cells = stripper->GetOutput()->GetLines();

  std::cout << "-----------Lines using vtkStripper" << std::endl;
  std::cout << "There are "
            << numberOfLines
            << " lines in the polydata" << std::endl;

  vtkIdType *indices;
  vtkIdType numberOfPoints;
  unsigned int lineCount = 0;
  for (cells->InitTraversal();
       cells->GetNextCell(numberOfPoints, indices);
       lineCount++)
  {
    std::cout << "Line " << lineCount << ": " << std::endl;
    for (vtkIdType i = 0; i < numberOfPoints; i++)
    {
      double point[3];
      points->GetPoint(indices[i], point);
      std::cout << "\t("
                << point[0] << ", "
                << point[1] << ", "
                << point[2] << ")" << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
