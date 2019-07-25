#include <vtkActor.h>
#include <vtkBox.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkDataSetMapper.h>
#include <vtkIdList.h>
#include <vtkImageData.h>
#include <vtkIntArray.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShrinkFilter.h>
#include <vtkSmartPointer.h>
#include <vtkThreshold.h>
#include <vtkUnstructuredGrid.h>

#include <algorithm>
#include <cmath>

namespace {
vtkIdType FindCell(vtkImageData* grid, double point[3]);

std::vector<vtkIdType> IntersectImage(vtkImageData* image, double p0[3],
                                      double p1[3]);
} // namespace

int main(int, char*[])
{
  auto colors = vtkSmartPointer<vtkNamedColors>::New();
  colors->SetColor("Bkg", 0.2, 0.3, 0.4);

  // Create a 3x4x5 grid of points (60), which will define a 2x3x4
  // (24) grid of cubes
  auto grid = vtkSmartPointer<vtkImageData>::New();

  // Create the grid data structure
  grid->SetDimensions(3, 4, 5);

  std::cout << "There are " << grid->GetNumberOfPoints()
            << " points before shrinking." << std::endl;
  std::cout << "There are " << grid->GetNumberOfCells()
            << " cells before shrinking." << std::endl;

  // Define a ray
  double rayOrigin[3] = {-5.0, 0, 0};
  double rayDirection[3] = {1.0, 0, 0};
  double rayEndPoint[3];
  for (size_t i = 0; i < 3; ++i)
  {
    rayEndPoint[i] = rayOrigin[i] +
        rayDirection[i] *
            1000; // 1000 is an arbitrary constant that should be much larger
                  // than the size of the scene (to create an "infinite" ray)
  }
  std::vector<vtkIdType> intersectedCells =
      IntersectImage(grid, rayOrigin, rayEndPoint);

  auto shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
  shrinkFilter->SetInputData(grid);
  shrinkFilter->SetShrinkFactor(.8);
  shrinkFilter->Update();

  // Setup visibility array. Cells with visibility > 1 will be
  // visible, and < 1 will be invisible.
  auto visibilityArray = vtkSmartPointer<vtkIntArray>::New();
  visibilityArray->SetNumberOfComponents(1);
  visibilityArray->SetName("Visibility");

  // Initially, set all cells to visible
  for (vtkIdType cellId = 0;
       cellId < shrinkFilter->GetOutput()->GetNumberOfCells(); ++cellId)
  {
    visibilityArray->InsertNextValue(10);
  }

  // Set the intersected cells to invisible
  for (size_t i = 0; i < intersectedCells.size(); ++i)
  {
    visibilityArray->SetTuple1(intersectedCells[i], 0);
  }

  shrinkFilter->GetOutput()->GetCellData()->AddArray(visibilityArray);

  // Threshold
  auto threshold = vtkSmartPointer<vtkThreshold>::New();
  threshold->SetInputData(shrinkFilter->GetOutput());
  threshold->ThresholdByUpper(
      1); // Criterion is cells whose scalars are greater or equal to threshold.

  threshold->SetInputArrayToProcess(
      0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, "Visibility");
  threshold->Update();

  vtkUnstructuredGrid* thresholdedPolydata = threshold->GetOutput();
  std::cout << "There are " << thresholdedPolydata->GetNumberOfCells()
            << " cells after thresholding." << std::endl;

  /////////// Standard visualization setup //////////////
  // Create a mapper and actor
  auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(threshold->GetOutputPort());
  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Peru").GetData());

  // Create a renderer, render window, and interactor
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetMultiSamples(0);
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);
  auto renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("Bkg").GetData());

  renderer->GetActiveCamera()->SetPosition(-6, 7, 6);
  renderer->GetActiveCamera()->SetFocalPoint(1, 1.5, 2);
  renderer->GetActiveCamera()->SetViewUp(0.4, 8, -0.4);
  renderer->ResetCameraClippingRange();

  // Render and interact
  renderWindow->Render();
  renderWindow->SetWindowName("Space Carving");
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

namespace {

vtkIdType FindCell(vtkImageData* grid, double point[3])
{
  double pcoords[3];
  double weights[8];

  int subId;

  // The third parameter is an "initial guess" of the cellId
  vtkIdType cellId =
      grid->FindCell(point, NULL, 0, .1, subId, pcoords, weights);
  return cellId;
}

// Intersect a finite line (with end points p0 and p1) with all of the
// cells of a vtkImageData
std::vector<vtkIdType> IntersectImage(vtkImageData* image, double p0[3],
                                      double p1[3])
{
  // Intersect a ray with the bounding box of the grid. There should
  // be two points (an entrance and an exit)

  // Define a box
  double bounds[6];
  image->GetBounds(bounds);

  // The two points of intersection of the bounding box with the line
  // will be stored here
  double entrancePoint[3];
  double exitPoint[3];

  // We do not need the results stored in these variables, but they
  // are required for the function call.
  int entryPlane[6]{0, 0, 0, 0, 0, 0};
  int exitPlane[6]{0, 0, 0, 0, 0, 0};

  double t0,
      t1; // the [0,1] normalized distances to the intersections along the ray

  int hit = vtkBox::IntersectWithLine(bounds, p0, p1, t0, t1, entrancePoint,
                                      exitPoint, *entryPlane, *exitPlane);

  std::vector<vtkIdType> intersectedCells;

  if (!hit)
  {
    std::cout << "Not hit!" << std::endl;
    return intersectedCells;
  }
  else
  {
    std::cout << "Entry point: " << entrancePoint[0] << " " << entrancePoint[1]
              << " " << entrancePoint[2] << std::endl;
    std::cout << "Exit point: " << exitPoint[0] << " " << exitPoint[1] << " "
              << exitPoint[2] << std::endl;
  }

  // This simple algorithm was adapted from
  // http://www.cb.uu.se/~cris/blog/index.php/archives/400

  int dim[3];
  image->GetDimensions(dim);

  // Make sure to include the first cell that the line hits
  vtkIdType startCellId = FindCell(image, entrancePoint);
  intersectedCells.push_back(startCellId);

  double p[3];
  p[0] = entrancePoint[0];
  p[1] = entrancePoint[1];
  p[2] = entrancePoint[2];

  double d[3];
  d[0] = exitPoint[0] - entrancePoint[0];
  d[1] = exitPoint[1] - entrancePoint[1];
  d[2] = exitPoint[2] - entrancePoint[2];

  double N = std::max(std::max(std::abs(d[0]), std::abs(d[1])), std::abs(d[2]));

  double s[3];
  s[0] = d[0] / N;
  s[1] = d[1] / N;
  s[2] = d[2] / N;

  for (size_t i = 0; i < N; ++i)
  {
    int ijk[3];
    ijk[0] = vtkMath::Round(p[0]);
    ijk[1] = vtkMath::Round(p[1]);
    ijk[2] = vtkMath::Round(p[2]);

    for (unsigned int index = 0; index < 3; ++index)
    {
      if (ijk[index] > dim[index] - 2)
      {
        ijk[index] = dim[index] - 2;
      }
    }

    vtkIdType cellId = vtkStructuredData::ComputeCellId(dim, ijk);
    intersectedCells.push_back(cellId);
    p[0] += s[0];
    p[1] += s[1];
    p[2] += s[2];
  }

  // Make sure to include the last cell that the line hits
  vtkIdType endCellId = FindCell(image, exitPoint);
  intersectedCells.push_back(endCellId);

  return intersectedCells;
}

} // namespace
