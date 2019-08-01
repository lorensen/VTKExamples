#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkContourFilter.h>
#include <vtkLabeledDataMapper.h>
#include <vtkLookupTable.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkStripper.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkCellArray.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>

#include <vtkMath.h>

int main(int argc, char* argv[])
{
  int pointThreshold = 10;

  vtkSmartPointer<vtkPolyData> polyData;
  auto contours = vtkSmartPointer<vtkContourFilter>::New();

  // If a file is present, read it, otherwise generate some random
  // scalars on a plane
  if (argc > 1)
  {
    auto reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    double range[2];
    reader->GetOutput()->GetScalarRange(range);
    polyData = reader->GetOutput();

    std::cout << "range: " << range[0] << ", " << range[1] << std::endl;
    contours->SetValue(0, (range[1] + range[0]) / 2.0);

    contours->SetInputConnection(reader->GetOutputPort());
    if (argc == 3)
    {
      contours->SetValue(0, atof(argv[2]));
    }
    else if (argc == 4)
    {
      contours->SetValue(0, atof(argv[2]));
      contours->SetValue(1, atof(argv[3]));
    }
    else if (argc == 5)
    {
      contours->GenerateValues(atoi(argv[2]), atof(argv[3]), atof(argv[4]));
    }
  }
  else
  {
    auto plane =
      vtkSmartPointer<vtkPlaneSource>::New();
    plane->SetXResolution(10);
    plane->SetYResolution(10);
    plane->Update();

    auto randomScalars =
      vtkSmartPointer<vtkDoubleArray>::New();
    randomScalars->SetNumberOfComponents(1);
    randomScalars->SetName("Isovalues");
    for (int i = 0; i < plane->GetOutput()->GetNumberOfPoints(); i++)
    {
      randomScalars->InsertNextTuple1(vtkMath::Random(-100.0, 100.0));
    }
    plane->GetOutput()->GetPointData()->SetScalars(randomScalars);
    polyData = plane->GetOutput();
    contours->SetInputConnection(plane->GetOutputPort());
    contours->GenerateValues(5, -100, 100);
    pointThreshold = 0;
  }

  // Connect the segments of the conours into polylines
  auto contourStripper =
    vtkSmartPointer<vtkStripper>::New();
  contourStripper->SetInputConnection(contours->GetOutputPort());
  contourStripper->Update();

  auto numberOfContourLines = contourStripper->GetOutput()->GetNumberOfLines();

  std::cout << "There are " << numberOfContourLines << " contours lines."
            << std::endl;

  vtkPoints* points = contourStripper->GetOutput()->GetPoints();
  vtkCellArray* cells = contourStripper->GetOutput()->GetLines();
  vtkDataArray* scalars =
      contourStripper->GetOutput()->GetPointData()->GetScalars();

  // Create a polydata that contains point locations for the contour
  // line labels
  auto labelPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  auto labelPoints =
    vtkSmartPointer<vtkPoints>::New();
  auto labelScalars =
    vtkSmartPointer<vtkDoubleArray>::New();
  labelScalars->SetNumberOfComponents(1);
  labelScalars->SetName("Isovalues");

  vtkIdType* indices;
  vtkIdType numberOfPoints;
  unsigned int lineCount = 0;
  for (cells->InitTraversal(); cells->GetNextCell(numberOfPoints, indices);
       lineCount++)
  {
    if (numberOfPoints < pointThreshold)
    {
      continue;
    }
    std::cout << "Line " << lineCount << ": " << std::endl;

    // Compute the point id to hold the label
    // Mid point or a random point
    // auto midPointId = indices[numberOfPoints / 2];
    auto midPointId =
        indices[static_cast<vtkIdType>(vtkMath::Random(0, numberOfPoints))];

    double midPoint[3];
    points->GetPoint(midPointId, midPoint);
    std::cout << "\tmidPoint is " << midPointId << " with coordinate "
              << "(" << midPoint[0] << ", " << midPoint[1] << ", "
              << midPoint[2] << ")"
              << " and value " << scalars->GetTuple1(midPointId) << std::endl;
    labelPoints->InsertNextPoint(midPoint);
    labelScalars->InsertNextTuple1(scalars->GetTuple1(midPointId));
  }
  labelPolyData->SetPoints(labelPoints);
  labelPolyData->GetPointData()->SetScalars(labelScalars);

  auto contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contourStripper->GetOutputPort());
  contourMapper->ScalarVisibilityOff();

  auto isolines =
    vtkSmartPointer<vtkActor>::New();
  isolines->SetMapper(contourMapper);

  auto surfaceLUT =
    vtkSmartPointer<vtkLookupTable>::New();
  surfaceLUT->SetRange(polyData->GetPointData()->GetScalars()->GetRange());
  surfaceLUT->Build();

  auto surfaceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  surfaceMapper->SetInputData(polyData);
  surfaceMapper->ScalarVisibilityOn();
  surfaceMapper->SetScalarRange(
      polyData->GetPointData()->GetScalars()->GetRange());
  surfaceMapper->SetLookupTable(surfaceLUT);

  auto surface =
    vtkSmartPointer<vtkActor>::New();
  surface->SetMapper(surfaceMapper);

  // The labeled data mapper will place labels at the points
  auto labelMapper =
    vtkSmartPointer<vtkLabeledDataMapper>::New();
  labelMapper->SetFieldDataName("Isovalues");
  labelMapper->SetInputData(labelPolyData);
  labelMapper->SetLabelModeToLabelScalars();
  labelMapper->SetLabelFormat("%6.2f");

  auto isolabels =
    vtkSmartPointer<vtkActor2D>::New();
  isolabels->SetMapper(labelMapper);

  // Create a renderer and render window
  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Create an interactor
  auto renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(isolines);
  renderer->AddActor(isolabels);
  //  renderer->AddActor(surface);

  // Render the scene (lights and cameras are created automatically)
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
