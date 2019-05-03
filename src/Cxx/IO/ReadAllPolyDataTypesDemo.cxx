#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkBYUReader.h>
#include <vtkCamera.h>
#include <vtkCoordinate.h>
#include <vtkNamedColors.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkTimerLog.h>
#include <vtkXMLPolyDataReader.h>

#include <vtksys/SystemTools.hxx>

#include <string>
#include <algorithm>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
}

namespace
{
void ViewportBorder(vtkSmartPointer<vtkRenderer> &renderer,
                    double *color,
                    bool last = false);
}
int main (int argc, char *argv[])
{
  // Visualize
  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // Create one text property for all
  auto textProperty = vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(16);
  textProperty->SetColor(0.3, 0.3, 0.3);

  // Setup render window
  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  for (auto i = 1; i < argc; ++i)
  {
    std::cout << argv[i] << std::endl;
    auto polyData = ReadPolyData(argv[i]);
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Light_salmon").GetData());
    actor->GetProperty()->SetSpecular(.6);
    actor->GetProperty()->SetSpecularPower(30);

    // Create textActors
    auto textMapper = vtkSmartPointer<vtkTextMapper>::New();
    textMapper->SetTextProperty(textProperty);
    textMapper->SetInput(vtksys::SystemTools::GetFilenameName(argv[i]).c_str());

    auto textActor = vtkSmartPointer<vtkActor2D>::New();
    textActor->SetMapper(textMapper);
    textActor->SetPosition(20, 20);

    // Setup renderer
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->AddActor(textActor);
    renderer->SetBackground(colors->GetColor3d("mint").GetData());
    renderers.push_back(renderer);
    renderWindow->AddRenderer(renderer);
  }

  // Setup viewports for the renderers
  auto rendererSize = 400;
  auto xGridDimensions = 3;
  auto yGridDimensions = 2;
  yGridDimensions = argc / xGridDimensions;
  renderWindow->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);
  auto blank = argc - 1 + ((argc - 1) % xGridDimensions);
  for (auto i = argc; i < blank; ++i)
  {
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(colors->GetColor3d("White").GetData());
    renderers.push_back(renderer);
    renderWindow->AddRenderer(renderer);
  }

  for (auto row = 0; row < yGridDimensions; row++)
  {
    for (auto col = 0; col < xGridDimensions; col++)
    {
      auto index = row * xGridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {
        static_cast<double>(col) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - (row + 1)) * rendererSize /
        (yGridDimensions * rendererSize),
        static_cast<double>(col + 1) * rendererSize /
        (xGridDimensions * rendererSize),
        static_cast<double>(yGridDimensions - row) * rendererSize /
        (yGridDimensions * rendererSize)};
      renderers[index]->SetViewport(viewport);
      ViewportBorder(renderers[index],
                     colors->GetColor3d("SlateGray").GetData(),
                     col == static_cast<int>(xGridDimensions));
    }
  }
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}


namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension =
    vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));

  // Drop the case of the extension
  std::transform(extension.begin(), extension.end(),
                 extension.begin(), ::tolower);

  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}
}
#include <vtkRenderer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyLine.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkCoordinate.h>
#include <vtkActor2D.h>
#include <vtkProperty2D.h>
namespace
{
// draw the borders of a renderer's viewport
void ViewportBorder(vtkSmartPointer<vtkRenderer> &renderer,
                    double *color,
                    bool last)
{
  // points start at upper right and proceed anti-clockwise
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(4);
  points->InsertPoint(0, 1, 1, 0);
  points->InsertPoint(1, 0, 1, 0);
  points->InsertPoint(2, 0, 0, 0);
  points->InsertPoint(3, 1, 0, 0);

  // create cells, and lines
  auto cells = vtkSmartPointer<vtkCellArray>::New();
  cells->Initialize();

  auto lines = vtkSmartPointer<vtkPolyLine>::New();

  // only draw last line if this is the last viewport
  // this prevents double vertical lines at right border
  // if different colors are used for each border, then do
  // not specify last
  if (last)
  {
    lines->GetPointIds()->SetNumberOfIds(5);
  }
  else
  {
    lines->GetPointIds()->SetNumberOfIds(4);
  }
  for(unsigned int i = 0; i < 4; ++i)
  {
    lines->GetPointIds()->SetId(i,i);
  }
  if (last)
  {
    lines->GetPointIds()->SetId(4, 0);
  }
  cells->InsertNextCell(lines);

  // now make tge polydata and display it
  auto poly = vtkSmartPointer<vtkPolyData>::New();
  poly->Initialize();
  poly->SetPoints(points);
  poly->SetLines(cells);

  // use normalized viewport coordinates since
  // they are independent of window size
  auto coordinate = vtkSmartPointer<vtkCoordinate>::New();
  coordinate->SetCoordinateSystemToNormalizedViewport();

  auto mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
  mapper->SetInputData(poly);
  mapper->SetTransformCoordinate(coordinate);

  auto actor = vtkSmartPointer<vtkActor2D>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(color);

  // line width should be at least 2 to be visible at extremes
  actor->GetProperty()->SetLineWidth(4.0); // Line Width

  renderer->AddViewProp(actor);
}
}
