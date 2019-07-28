#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkCoordinate.h>
#include <vtkExtractSurface.h>
#include <vtkNamedColors.h>
#include <vtkPCANormalEstimation.h>
#include <vtkPointData.h>
#include <vtkPoissonReconstruction.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyLine.h>
#include <vtkPowerCrustSurfaceReconstruction.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSignedDistance.h>
#include <vtkSmartPointer.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkTimerLog.h>

// Readers
#include <vtkBYUReader.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkPolyData.h>
#include <vtkSphereSource.h>

#include <algorithm> // For transform()
#include <cctype>    // For to_lower
#include <sstream>
#include <string>
#include <vector>

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName);
vtkSmartPointer<vtkPolyDataAlgorithm> MakeExtractSurface(vtkPolyData*);
vtkSmartPointer<vtkPolyDataAlgorithm> MakePoissonExtractSurface(vtkPolyData*);
vtkSmartPointer<vtkPolyDataAlgorithm>
MakePowercrustExtractSurface(vtkPolyData*);
void MakeViewportGrid(std::vector<vtkSmartPointer<vtkRenderer>>& renderers,
                      unsigned int renderersize, unsigned int xGridDimensions,
                      unsigned int yGridDimensions);
void ViewportBorder(vtkSmartPointer<vtkRenderer>& renderer, double* color,
                    bool last = false);
} // namespace

int main(int argc, char* argv[])
{
  auto polyData = ReadPolyData(argc > 1 ? argv[1] : "");

  std::cout << "# of points: " << polyData->GetNumberOfPoints() << std::endl;

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

  std::vector<vtkSmartPointer<vtkPolyDataAlgorithm>> surfaceObjects;
  surfaceObjects.push_back(MakeExtractSurface(polyData.GetPointer()));
  surfaceObjects.push_back(MakePoissonExtractSurface(polyData.GetPointer()));
  surfaceObjects.push_back(MakePowercrustExtractSurface(polyData.GetPointer()));

  std::vector<vtkSmartPointer<vtkRenderer>> renderers;

  // One camera for all
  auto camera = vtkSmartPointer<vtkCamera>::New();
  for (size_t i = 0; i < surfaceObjects.size(); ++i)
  {
    auto timer = vtkSmartPointer<vtkTimerLog>::New();
    timer->StartTimer();
    surfaceObjects[i]->Update();
    timer->StopTimer();

    auto surfaceMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    surfaceMapper->SetInputConnection(surfaceObjects[i]->GetOutputPort());

    auto back = vtkSmartPointer<vtkProperty>::New();
    back->SetDiffuseColor(colors->GetColor3d("Banana").GetData());
    back->SetSpecular(.6);
    back->SetSpecularPower(50.0);

    auto surfaceActor = vtkSmartPointer<vtkActor>::New();
    surfaceActor->SetMapper(surfaceMapper);
    surfaceActor->GetProperty()->SetDiffuseColor(
        colors->GetColor3d("Tomato").GetData());
    surfaceActor->GetProperty()->SetSpecular(.6);
    surfaceActor->GetProperty()->SetSpecularPower(50.0);
    surfaceActor->SetBackfaceProperty(back);
    // Setup renderer
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(surfaceActor);
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    renderer->SetActiveCamera(camera);
    renderer->GetActiveCamera()->SetPosition(-1, 0, 0);
    renderer->GetActiveCamera()->SetFocalPoint(0, 1, 0);
    renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
    renderer->GetActiveCamera()->Dolly(5);
    renderer->ResetCamera();
    renderer->ResetCameraClippingRange();
    renderers.push_back(renderer);
    renderWindow->AddRenderer(renderer);

    auto textProperty = vtkSmartPointer<vtkTextProperty>::New();
    textProperty->SetFontSize(15);
    textProperty->SetJustificationToCentered();

    std::stringstream ss;
    ss << surfaceObjects[i]->GetClassName() << std::endl;
    ss << "# of Polys: " << surfaceObjects[i]->GetOutput()->GetNumberOfPolys()
       << std::endl;
    ss << "Time: " << timer->GetElapsedTime() << std::endl;

    auto textMapper = vtkSmartPointer<vtkTextMapper>::New();
    textMapper->SetInput(ss.str().c_str());
    textMapper->SetTextProperty(textProperty);

    auto textActor = vtkSmartPointer<vtkActor2D>::New();
    textActor->SetMapper(textMapper);
    textActor->SetPosition(200, 0);
    textActor->GetProperty()->SetLineWidth(4.0); // Line Width

    renderer->AddViewProp(textActor);
  }

  unsigned int rendererSize = 400;
  unsigned int xGridDimensions = 3;
  unsigned int yGridDimensions = 1;
  renderWindow->SetSize(rendererSize * xGridDimensions,
                        rendererSize * yGridDimensions);

  MakeViewportGrid(renderers, rendererSize, xGridDimensions, yGridDimensions);
  for (size_t i = 0; i < renderers.size(); ++i)
  {
    ViewportBorder(renderers[i], colors->GetColor3d("Gold").GetData(),
                   i == renderers.size() - 1);
  }
  auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  renderWindow->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace {
vtkSmartPointer<vtkPolyData> ReadPolyData(std::string const& fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = "";
  if (fileName.find_last_of(".") != std::string::npos)
  {
    extension = fileName.substr(fileName.find_last_of("."));
  }
  // Make the extension lowercase
  std::transform(extension.begin(), extension.end(), extension.begin(),
                 ::tolower);
  if (extension == ".ply")
  {
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    auto reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    auto reader = vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtk")
  {
    auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".g")
  {
    auto reader = vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName(fileName.c_str());
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    // Return a polydata sphere if the extension is unknown.
    auto source = vtkSmartPointer<vtkSphereSource>::New();
    source->SetThetaResolution(20);
    source->SetPhiResolution(11);
    source->Update();
    polyData = source->GetOutput();
  }
  return polyData;
}

vtkSmartPointer<vtkPolyDataAlgorithm> MakeExtractSurface(vtkPolyData* polyData)
{
  double bounds[6];
  polyData->GetBounds(bounds);
  double range[3];
  for (int i = 0; i < 3; ++i)
  {
    range[i] = bounds[2 * i + 1] - bounds[2 * i];
  }

  int sampleSize = polyData->GetNumberOfPoints() * .00005;
  if (sampleSize < 10)
  {
    sampleSize = 50;
  }

  // Do we need to estimate normals?
  auto distance = vtkSmartPointer<vtkSignedDistance>::New();
  if (polyData->GetPointData()->GetNormals())
  {
    std::cout << "ExtractSurface: Using normals from input file" << std::endl;
    distance->SetInputData(polyData);
  }
  else
  {
    std::cout << " ExtractSurface: Estimating normals using PCANormalEstimation"
              << std::endl;
    auto normals = vtkSmartPointer<vtkPCANormalEstimation>::New();
    normals->SetInputData(polyData);
    normals->SetSampleSize(sampleSize);
    normals->SetNormalOrientationToGraphTraversal();
    normals->FlipNormalsOn();
    distance->SetInputConnection(normals->GetOutputPort());
  }
  int dimension = 256;
  double radius;
  radius = std::max(std::max(range[0], range[1]), range[2]) /
      static_cast<double>(dimension) * 4; // ~4 voxels

  distance->SetRadius(radius);
  distance->SetDimensions(dimension, dimension, dimension);
  distance->SetBounds(bounds[0] - range[0] * .1, bounds[1] + range[0] * .1,
                      bounds[2] - range[1] * .1, bounds[3] + range[1] * .1,
                      bounds[4] - range[2] * .1, bounds[5] + range[2] * .1);

  auto surface = vtkSmartPointer<vtkExtractSurface>::New();
  surface->SetInputConnection(distance->GetOutputPort());
  surface->SetRadius(radius * .99);
  return surface;
}
vtkSmartPointer<vtkPolyDataAlgorithm>
MakePoissonExtractSurface(vtkPolyData* polyData)
{
  double bounds[6];
  polyData->GetBounds(bounds);
  double range[3];
  for (int i = 0; i < 3; ++i)
  {
    range[i] = bounds[2 * i + 1] - bounds[2 * i];
  }

  int sampleSize = polyData->GetNumberOfPoints() * .00005;
  if (sampleSize < 10)
  {
    sampleSize = 10;
  }

  auto surface = vtkSmartPointer<vtkPoissonReconstruction>::New();
  surface->SetDepth(12);
  if (polyData->GetPointData()->GetNormals())
  {
    std::cout << "PoissonReconstruction: Using normals from input file"
              << std::endl;
    surface->SetInputData(polyData);
  }
  else
  {
    std::cout << "ExtractSurface: Estimating normals using PCANormalEstimation"
              << std::endl;
    auto normals = vtkSmartPointer<vtkPCANormalEstimation>::New();
    normals->SetInputData(polyData);
    normals->SetSampleSize(sampleSize);
    normals->SetNormalOrientationToGraphTraversal();
    normals->FlipNormalsOff();
    surface->SetInputConnection(normals->GetOutputPort());
  }
  return surface;
}
vtkSmartPointer<vtkPolyDataAlgorithm>
MakePowercrustExtractSurface(vtkPolyData* polyData)
{
  auto surface = vtkSmartPointer<vtkPowerCrustSurfaceReconstruction>::New();
  surface->SetInputData(polyData);
  return surface;
}

void MakeViewportGrid(std::vector<vtkSmartPointer<vtkRenderer>>& renderers,
                      unsigned int rendererSize, unsigned int xGridDimensions,
                      unsigned int yGridDimensions)
{
  //
  // Setup viewports for the renderers
  for (int row = 0; row < static_cast<int>(yGridDimensions); row++)
  {
    for (int col = 0; col < static_cast<int>(xGridDimensions); col++)
    {
      auto index = row * xGridDimensions + col;

      // (xmin, ymin, xmax, ymax)
      double viewport[4] = {static_cast<double>(col) * rendererSize /
                                (xGridDimensions * rendererSize),
                            static_cast<double>(yGridDimensions - (row + 1)) *
                                rendererSize / (yGridDimensions * rendererSize),
                            static_cast<double>(col + 1) * rendererSize /
                                (xGridDimensions * rendererSize),
                            static_cast<double>(yGridDimensions - row) *
                                rendererSize /
                                (yGridDimensions * rendererSize)};
      renderers[index]->SetViewport(viewport);
    }
  }
}
// draw the borders of a renderer's viewport
void ViewportBorder(vtkSmartPointer<vtkRenderer>& renderer, double* color,
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
  for (unsigned int i = 0; i < 4; ++i)
  {
    lines->GetPointIds()->SetId(i, i);
  }
  if (last)
  {
    lines->GetPointIds()->SetId(4, 0);
  }
  cells->InsertNextCell(lines);

  // now make the polydata and display it
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

} // namespace
