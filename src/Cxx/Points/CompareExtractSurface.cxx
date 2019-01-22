#include <vtkSmartPointer.h>

#include <vtkBYUReader.h>
#include <vtkPLYReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>
#include <vtkSTLReader.h>
#include <vtkPointSource.h>

#include <vtkPCANormalEstimation.h>
#include <vtkSignedDistance.h>
#include <vtkExtractSurface.h>
#include <vtkExtractSurface.h>
#include <vtkPoissonReconstruction.h>
#include <vtkPowerCrustSurfaceReconstruction.h>

#include <vtkPointData.h>

#include <vtkCoordinate.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkActor2D.h>

#include <vtkPolyLine.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtkNamedColors.h>
#include <vtkTimerLog.h>
#include <vtksys/SystemTools.hxx>

#include <sstream>
#include <vector>
#include <string>

namespace
{
vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);
vtkSmartPointer<vtkPolyDataAlgorithm> MakeExtractSurface(vtkPolyData *);
vtkSmartPointer<vtkPolyDataAlgorithm> MakePoissonExtractSurface(vtkPolyData *);
vtkSmartPointer<vtkPolyDataAlgorithm> MakePowercrustExtractSurface(vtkPolyData *);
void MakeViewportGrid(
  std::vector<vtkSmartPointer<vtkRenderer> > &renderers,
  unsigned int renderersize,
  unsigned int xGridDimensions,
  unsigned int yGridDimensions);
void ViewportBorder(vtkSmartPointer<vtkRenderer> &renderer,
                    double *color,
                    bool last = false);
}

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;
  std::cout << "# of points: " << polyData->GetNumberOfPoints() << std::endl;

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  std::vector<vtkSmartPointer<vtkPolyDataAlgorithm> > surfaceObjects;
  surfaceObjects.push_back(MakeExtractSurface(polyData.GetPointer()));
  surfaceObjects.push_back(MakePoissonExtractSurface(polyData.GetPointer()));
  surfaceObjects.push_back(MakePowercrustExtractSurface(polyData.GetPointer()));

  std::vector<vtkSmartPointer<vtkRenderer> > renderers;

  // One camera for all
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  for (size_t i = 0; i < surfaceObjects.size(); ++i)
  {
    vtkSmartPointer<vtkTimerLog> timer =
      vtkSmartPointer<vtkTimerLog>::New();
    timer->StartTimer();
    surfaceObjects[i]->Update();
    timer->StopTimer();

    vtkSmartPointer<vtkPolyDataMapper> surfaceMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    surfaceMapper->SetInputConnection(surfaceObjects[i]->GetOutputPort());

    vtkSmartPointer<vtkProperty> back =
      vtkSmartPointer<vtkProperty>::New();
    back->SetDiffuseColor(colors->GetColor3d("banana").GetData());
    back->SetSpecular(.6);
    back->SetSpecularPower(50.0);

    vtkSmartPointer<vtkActor> surfaceActor =
      vtkSmartPointer<vtkActor>::New();
    surfaceActor->SetMapper(surfaceMapper);
    surfaceActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());
    surfaceActor->GetProperty()->SetSpecular(.6);
    surfaceActor->GetProperty()->SetSpecularPower(50.0);
    surfaceActor->SetBackfaceProperty(back);
    // Setup renderer
    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(surfaceActor);
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    renderer->SetActiveCamera(camera);
    renderer->GetActiveCamera()->SetPosition (-1, 0, 0);
    renderer->GetActiveCamera()->SetFocalPoint (0, 1, 0);
    renderer->GetActiveCamera()->SetViewUp (0, 0, 1);
    renderer->GetActiveCamera()->Dolly(5);
    renderer->ResetCamera();
    renderer->ResetCameraClippingRange();
    renderers.push_back(renderer);
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkTextProperty> textProperty =
      vtkSmartPointer<vtkTextProperty>::New();
    textProperty->SetFontSize(15);
    textProperty->SetJustificationToCentered();
    
    std::stringstream ss;
    ss << surfaceObjects[i]->GetClassName() << std::endl;
    ss << "# of Polys: " << surfaceObjects[i]->GetOutput()->GetNumberOfPolys() << std::endl;
    ss << "Time: " << timer->GetElapsedTime() << std::endl;

    vtkSmartPointer<vtkTextMapper> textMapper =
      vtkSmartPointer<vtkTextMapper>::New();
    textMapper->SetInput(ss.str().c_str());
    textMapper->SetTextProperty(textProperty);

    vtkSmartPointer<vtkActor2D> textActor =
      vtkSmartPointer<vtkActor2D>::New();
    textActor->SetMapper(textMapper);
    textActor->SetPosition(200, 0);
    textActor->GetProperty()->SetLineWidth(4.0); // Line Width 

    renderer->AddViewProp(textActor);
  }

  unsigned int rendererSize = 400;
  unsigned int xGridDimensions = 3;
  unsigned int yGridDimensions = 1;
  renderWindow->SetSize(
    rendererSize * xGridDimensions,
    rendererSize * yGridDimensions);

  MakeViewportGrid(renderers,
                   rendererSize, 
                   xGridDimensions,
                   yGridDimensions);
  for (size_t i = 0; i < renderers.size(); ++i)
  {
    ViewportBorder(renderers[i],
                  colors->GetColor3d("Gold").GetData(),
                  i == renderers.size() - 1);
  }
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renderWindow);

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace {
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
  else if (extension == ".g")
  {
    vtkSmartPointer<vtkBYUReader> reader =
      vtkSmartPointer<vtkBYUReader>::New();
    reader->SetGeometryFileName (fileName);
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
    vtkSmartPointer<vtkPointSource> points =
      vtkSmartPointer<vtkPointSource>::New();
 points->SetNumberOfPoints(1000);
    points->SetRadius(1.0);
    points->SetCenter(vtkMath::Random(-1, 1),
                      vtkMath::Random(-1, 1),
                      vtkMath::Random(-1, 1));
    points->SetDistributionToShell();
    points->Update();
    polyData = points->GetOutput();
  }
  return polyData;
}

vtkSmartPointer<vtkPolyDataAlgorithm> MakeExtractSurface(vtkPolyData *polyData)
{
  double bounds[6];
  polyData->GetBounds(bounds);
  double range[3];
  for (int i = 0; i < 3; ++i)
  {
    range[i] = bounds[2*i + 1] - bounds[2*i];
  }

  int sampleSize = polyData->GetNumberOfPoints() * .00005;
  if (sampleSize < 10)
  {
    sampleSize = 50;
  }

  // Do we need to estimate normals?
  vtkSmartPointer<vtkSignedDistance> distance =
    vtkSmartPointer<vtkSignedDistance>::New();
  if (polyData->GetPointData()->GetNormals())
  {
    std::cout << "ExtractSurface: Using normals from input file" << std::endl;
    distance->SetInputData (polyData);
  }
  else
  {
    std::cout <<" ExtractSurface: Estimating normals using PCANormalEstimation" << std::endl;
    vtkSmartPointer<vtkPCANormalEstimation> normals =
      vtkSmartPointer<vtkPCANormalEstimation>::New();
    normals->SetInputData (polyData);
    normals->SetSampleSize(sampleSize);
    normals->SetNormalOrientationToGraphTraversal();
    normals->FlipNormalsOn();
    distance->SetInputConnection (normals->GetOutputPort());
  }
  int dimension = 256;
  double radius;
  radius = std::max(std::max(range[0], range[1]), range[2])
    / static_cast<double>(dimension) * 4; // ~4 voxels

  distance->SetRadius(radius);
  distance->SetDimensions(dimension, dimension, dimension);
  distance->SetBounds(
    bounds[0] - range[0] * .1,
    bounds[1] + range[0] * .1,
    bounds[2] - range[1] * .1,
    bounds[3] + range[1] * .1,
    bounds[4] - range[2] * .1,
    bounds[5] + range[2] * .1);

  vtkSmartPointer<vtkExtractSurface> surface =
    vtkSmartPointer<vtkExtractSurface>::New();
  surface->SetInputConnection (distance->GetOutputPort());
  surface->SetRadius(radius * .99);
  return surface;
}
vtkSmartPointer<vtkPolyDataAlgorithm> MakePoissonExtractSurface(vtkPolyData *polyData)
{
  double bounds[6];
  polyData->GetBounds(bounds);
  double range[3];
  for (int i = 0; i < 3; ++i)
  {
    range[i] = bounds[2*i + 1] - bounds[2*i];
  }

  int sampleSize = polyData->GetNumberOfPoints() * .00005;
  if (sampleSize < 10)
  {
    sampleSize = 10;
  }

  vtkSmartPointer<vtkPoissonReconstruction> surface =
    vtkSmartPointer<vtkPoissonReconstruction>::New();
  surface->SetDepth(12);
  if (polyData->GetPointData()->GetNormals())
  {
    std::cout << "PoissonReconstruction: Using normals from input file" << std::endl;
    surface->SetInputData (polyData);
  }
  else
  {
    std::cout << "ExtractSurface: Estimating normals using PCANormalEstimation" << std::endl;
    vtkSmartPointer<vtkPCANormalEstimation> normals =
      vtkSmartPointer<vtkPCANormalEstimation>::New();
    normals->SetInputData (polyData);
    normals->SetSampleSize(sampleSize);
    normals->SetNormalOrientationToGraphTraversal();
    normals->FlipNormalsOff();
    surface->SetInputConnection(normals->GetOutputPort());
  }
  return surface;
}
vtkSmartPointer<vtkPolyDataAlgorithm> MakePowercrustExtractSurface(vtkPolyData *polyData)
{
  vtkSmartPointer<vtkPowerCrustSurfaceReconstruction> surface =
    vtkSmartPointer<vtkPowerCrustSurfaceReconstruction>::New();
  surface->SetInputData (polyData);
  return surface;
}

void MakeViewportGrid(
  std::vector<vtkSmartPointer<vtkRenderer> > &renderers,
  unsigned int rendererSize,
  unsigned int xGridDimensions,
  unsigned int yGridDimensions)
{
  //
  // Setup viewports for the renderers
  int index = 0;
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
    }
  }
}
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

  // now make the polydata and display it
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
