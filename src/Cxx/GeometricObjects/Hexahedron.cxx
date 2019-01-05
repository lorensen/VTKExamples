#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkHexahedron.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

#include <array>
#include <vector>

int main(int, char* [])
{

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Set the background color.
  std::array<unsigned char , 4> bkg{{51, 77, 102, 255}};
    colors->SetColor("BkgColor", bkg.data());

  // For the hexahedron; setup the coordinates of eight points.
  // The two faces must be in counter clockwise order as viewed from the
  // outside.
  std::vector<std::array<double, 3>> pointCoordinates;
  pointCoordinates.push_back({{0.0, 0.0, 0.0}}); // Face 1
  pointCoordinates.push_back({{1.0, 0.0, 0.0}});
  pointCoordinates.push_back({{1.0, 1.0, 0.0}});
  pointCoordinates.push_back({{0.0, 1.0, 0.0}});
  pointCoordinates.push_back({{0.0, 0.0, 1.0}}); // Face 2
  pointCoordinates.push_back({{1.0, 0.0, 1.0}});
  pointCoordinates.push_back({{1.0, 1.0, 1.0}});
  pointCoordinates.push_back({{0.0, 1.0, 1.0}});

  // Create the points.
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  // Create a hexahedron from the points.
  vtkSmartPointer<vtkHexahedron> hex =
    vtkSmartPointer<vtkHexahedron>::New();

  for (auto i = 0; i < pointCoordinates.size(); ++i)
  {
    points->InsertNextPoint(pointCoordinates[i].data());
    hex->GetPointIds()->SetId(i, i);
  }

  // Add the hexahedron to a cell array.
  vtkSmartPointer<vtkCellArray> hexs =
    vtkSmartPointer<vtkCellArray>::New();
  hexs->InsertNextCell(hex);

  // Add the points and hexahedron to an unstructured grid.
  vtkSmartPointer<vtkUnstructuredGrid> uGrid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  uGrid->SetPoints(points);
  uGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

  // Visualize.
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(uGrid);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->SetColor(colors->GetColor3d("Cornsilk").GetData());
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetWindowName("Hexahedron");
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
