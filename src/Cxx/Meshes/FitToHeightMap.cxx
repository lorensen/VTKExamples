#include <vtkSmartPointer.h>
#include <vtkFitToHeightMapFilter.h>
#include <vtkDEMReader.h>
#include <vtkProbeFilter.h>

#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkImageData.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkLookupTable.h>
#include <vtkPlaneSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTriangleFilter.h>
#include <vtkWarpScalar.h>

#include <vtkNamedColors.h>

int main (int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cout << "Uagse: " << argv[0] << " file.dem" << std::endl;
    return EXIT_FAILURE;
  }
// Create the RenderWindow, Renderer
//
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> ren0 =
    vtkSmartPointer<vtkRenderer>::New();
  ren0->SetViewport(0, 0, 1.0/3.0 ,1);
  ren0->SetBackground(colors->GetColor3d("Wheat").GetData());

  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetViewport(1.0/3.0, 0, 2.0/3.0, 1);
  ren1->SetBackground(colors->GetColor3d("BurlyWood").GetData());

  vtkSmartPointer<vtkRenderer> ren2 =
    vtkSmartPointer<vtkRenderer>::New();
  ren2->SetViewport(2.0/3.0, 0, 1, 1);
  ren2->SetBackground(colors->GetColor3d("Tan").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize (1200, 400);
  renderWindow->AddRenderer(ren0);
  renderWindow->AddRenderer(ren1);
  renderWindow->AddRenderer(ren2);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

// Create pipeline. Load terrain data.
//
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(0.6, 0);
  lut->SetSaturationRange(1.0, 0);
  lut->SetValueRange(0.5, 1.0);

// Read the data: a height field results
  vtkSmartPointer<vtkDEMReader> demReader =
    vtkSmartPointer<vtkDEMReader>::New();
  demReader->SetFileName(argv[1]);
  demReader->Update(); // Update so we can get bounds

  vtkSmartPointer<vtkImageDataGeometryFilter> surface =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  surface->SetInputConnection(demReader->GetOutputPort());

  // Warp the surface in the vertical direction
  vtkSmartPointer<vtkWarpScalar> warp =
    vtkSmartPointer<vtkWarpScalar>::New();
  warp->SetInputConnection(surface->GetOutputPort());
  warp->SetScaleFactor(1);
  warp->UseNormalOn();
  warp->SetNormal(0, 0, 1);
  warp->Update();

// Show the terrain
  double lo = demReader->GetOutput()->GetScalarRange()[0];
  double hi = demReader->GetOutput()->GetScalarRange()[1];

  vtkSmartPointer<vtkPolyDataMapper> demMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  demMapper->SetInputConnection(warp->GetOutputPort());
  demMapper->ScalarVisibilityOn();
  demMapper->SetScalarRange(lo, hi);
  demMapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> demActor =
    vtkSmartPointer<vtkActor>::New();
  demActor->SetMapper(demMapper);

  // Create polygon(s) to fit. z-values should be height of DEM
  // to accomodate ProbeFilter
  double zLevel = demReader->GetOutput()->GetBounds()[5];
  double *demBounds;
  demBounds = demReader->GetOutput()->GetBounds();

  vtkSmartPointer<vtkPlaneSource> plane =
    vtkSmartPointer<vtkPlaneSource>::New();
  plane->SetOrigin(demBounds[0], demBounds[2], zLevel);
  plane->SetPoint1(demBounds[1], demBounds[2], zLevel);
  plane->SetPoint2(demBounds[0], demBounds[3], zLevel);
  plane->SetResolution(128, 128);
  plane->Update();

  // Get the scalrs from the DEM
  vtkSmartPointer<vtkProbeFilter> probeDem =
    vtkSmartPointer<vtkProbeFilter>::New();
  probeDem->SetSourceData(demReader->GetOutput());
  probeDem->SetInputConnection(plane->GetOutputPort());
  probeDem->Update();

  // Fit polygons to surface using two strategies
  // Both will share the same lookup tables
  vtkSmartPointer<vtkFitToHeightMapFilter> pointFit =
    vtkSmartPointer<vtkFitToHeightMapFilter>::New();
  pointFit->SetInputConnection(probeDem->GetOutputPort());
  pointFit->SetHeightMapConnection(demReader->GetOutputPort());
  pointFit->SetFittingStrategyToPointProjection();
  pointFit->UseHeightMapOffsetOn();

  vtkSmartPointer<vtkPolyDataMapper> pointMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  pointMapper->SetInputConnection(pointFit->GetOutputPort());
  pointMapper->ScalarVisibilityOn();
  pointMapper->SetScalarRange(lo, hi);
  pointMapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> pointActor =
    vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);

  // Fit polygons to surface (cell strategy)
  vtkSmartPointer<vtkFitToHeightMapFilter> cellFit =
    vtkSmartPointer<vtkFitToHeightMapFilter>::New();
  cellFit->SetInputConnection(probeDem->GetOutputPort());
  cellFit->SetHeightMapConnection(demReader->GetOutputPort());
  cellFit->SetFittingStrategyToCellAverageHeight();
  cellFit->UseHeightMapOffsetOn();

  vtkSmartPointer<vtkPolyDataMapper> cellMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cellMapper->SetInputConnection(cellFit->GetOutputPort());
  cellMapper->ScalarVisibilityOn();
  cellMapper->SetScalarRange(lo, hi);
  cellMapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> cellActor =
    vtkSmartPointer<vtkActor>::New();
  cellActor->SetMapper(cellMapper);

  // Render the three representations
  ren0->AddActor(demActor);
  ren1->AddActor(pointActor);
  ren2->AddActor(cellActor);

  // Look down the x axis
  ren0->GetActiveCamera()->SetPosition( 1, 0, 0);
  ren0->GetActiveCamera()->SetFocalPoint( 0, 1, 0);
  ren0->GetActiveCamera()->SetViewUp( 0, 0, 1);
  ren0->ResetCamera();

  // Rotate to an oblique view
  ren0->GetActiveCamera()->Azimuth(30.0);
  ren0->GetActiveCamera()->Elevation(60.0);

  // Share the cameras
  ren1->SetActiveCamera(ren0->GetActiveCamera());
  ren2->SetActiveCamera(ren0->GetActiveCamera());

  renderWindow->Render();
  interactor->Start();
  return EXIT_SUCCESS;
}
