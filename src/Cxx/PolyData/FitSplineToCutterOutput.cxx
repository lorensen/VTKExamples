#include <vtkSmartPointer.h>
#include <vtkCutter.h>
#include <vtkSplineFilter.h>
#include <vtkSpline.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkStripper.h>
#include <vtkPlane.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkTubeFilter.h>
#include <vtkKochanekSpline.h>

#include <vtkNamedColors.h>

int main (int argc, char *argv[])
{
  auto polyData =
    vtkSmartPointer<vtkPolyData>::New();
  if (argc > 1)
  {
    auto reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName ( argv[1] );
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto modelSource =
      vtkSmartPointer<vtkSphereSource>::New();
    modelSource->Update();
    polyData = modelSource->GetOutput();
  }

  double length = polyData->GetLength();
  
  auto plane =
    vtkSmartPointer<vtkPlane>::New();
  plane->SetNormal(0, 1, 1);
  plane->SetOrigin(polyData->GetCenter());

  auto cutter =
    vtkSmartPointer<vtkCutter>::New();
  cutter->SetInputData(polyData);
  cutter->SetCutFunction(plane);
  cutter->GenerateValues(1, 0.0, 0.0);

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto modelMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  modelMapper->SetInputData(polyData);

  auto model =
    vtkSmartPointer<vtkActor>::New();
  model->SetMapper(modelMapper);
  model->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  model->GetProperty()->SetInterpolationToFlat();

  auto stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(cutter->GetOutputPort());

  auto spline =
    vtkSmartPointer<vtkKochanekSpline>::New();
  spline->SetDefaultTension(.5);

  auto sf =
    vtkSmartPointer<vtkSplineFilter>::New();
  sf->SetInputConnection(stripper->GetOutputPort());
  sf->SetSubdivideToSpecified();
  sf->SetNumberOfSubdivisions(50);
  sf->SetSpline(spline);
  sf->GetSpline()->ClosedOn();

  auto tubes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubes->SetInputConnection( sf->GetOutputPort());
  tubes->SetNumberOfSides(8);
  tubes->SetRadius(length/100.0);

  auto linesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  linesMapper->SetInputConnection(tubes->GetOutputPort());
  linesMapper->ScalarVisibilityOff();

  auto lines =
    vtkSmartPointer<vtkActor>::New();
  lines->SetMapper(linesMapper);
  lines->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer
  renderer->AddActor(model);
  renderer->AddActor(lines);

  renderer->ResetCamera();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderer->GetActiveCamera()->Azimuth(300);
  renderer->GetActiveCamera()->Elevation(30);
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

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
