#include <vtkSmartPointer.h>

#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>

#include <vtkCoordinate.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>
#include <vtkTimerLog.h>
#include <vtksys/SystemTools.hxx>

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
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create one text property for all
  vtkSmartPointer<vtkTextProperty> textProperty =
    vtkSmartPointer<vtkTextProperty>::New();
  textProperty->SetFontSize(20);
//  textProperty->SetJustificationToCentered();
  textProperty->SetColor(0.3, 0.3, 0.3);

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  std::vector<vtkSmartPointer<vtkRenderer>> renderers;
  for (int i = 1; i < argc; ++i)
  {
    vtkSmartPointer<vtkPolyData> polyData =
      ReadPolyData(argv[i]);
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Light_salmon").GetData());
    actor->GetProperty()->SetSpecular(.6);
    actor->GetProperty()->SetSpecularPower(30);

    // Create textActors
    vtkSmartPointer<vtkTextMapper> textMapper =
      vtkSmartPointer<vtkTextMapper>::New();
    textMapper->SetTextProperty(textProperty);
    textMapper->SetInput(vtksys::SystemTools::GetFilenameName(argv[i]).c_str());

    vtkSmartPointer<vtkActor2D> textActor =
      vtkSmartPointer<vtkActor2D>::New();
    textActor->SetMapper(textMapper);
    textActor->SetPosition(20, 20);

    // Setup renderer
    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->AddActor(textActor);;
    renderer->SetBackground(colors->GetColor3d("mint").GetData());
    renderers.push_back(renderer);
    renderWindow->AddRenderer(renderer);
  }

  // Setup viewports for the renderers
  int rendererSize = 400;
  unsigned int xGridDimensions = 3;
  unsigned int yGridDimensions = 2;
  renderWindow->SetSize(
    rendererSize * xGridDimensions, rendererSize * yGridDimensions);
  int index;
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      int index = row * xGridDimensions + col;
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
                     col == xGridDimensions);
    }
  }
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}


namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> source =
      vtkSmartPointer<vtkSphereSource>::New();
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
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(4);
  points->InsertPoint(0, 1, 1, 0);
  points->InsertPoint(1, 0, 1, 0);
  points->InsertPoint(2, 0, 0, 0);
  points->InsertPoint(3, 1, 0, 0);

  // create cells, and lines
  vtkSmartPointer<vtkCellArray> cells =
    vtkSmartPointer<vtkCellArray>::New();
  cells->Initialize(); 

  vtkSmartPointer<vtkPolyLine> lines =
    vtkSmartPointer<vtkPolyLine>::New();

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
  vtkSmartPointer<vtkPolyData> poly =
    vtkSmartPointer<vtkPolyData>::New();
  poly->Initialize(); 
  poly->SetPoints(points); 
  poly->SetLines(cells); 

  // use normalized viewport coordinates since
  // they are independent of window size
  vtkSmartPointer<vtkCoordinate> coordinate =
    vtkSmartPointer<vtkCoordinate>::New();
  coordinate->SetCoordinateSystemToNormalizedViewport(); 

  vtkSmartPointer<vtkPolyDataMapper2D> mapper =
    vtkSmartPointer<vtkPolyDataMapper2D>::New();
  mapper->SetInputData(poly); 
  mapper->SetTransformCoordinate(coordinate); 

  vtkSmartPointer<vtkActor2D> actor =
    vtkSmartPointer<vtkActor2D>::New();
  actor->SetMapper(mapper); 
  actor->GetProperty()->SetColor(color);
  // line width should be at least 2 to be visible at extremes

  actor->GetProperty()->SetLineWidth(4.0); // Line Width 

  renderer->AddViewProp(actor);
}
}
