#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkLine.h>
#include <vtkImageData.h>
#include <vtkProbeFilter.h>
#include <vtkDelaunay2D.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkDoubleArray.h>
#include <vtkMath.h>
#include <vtkCellLocator.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkFloatArray.h>
#include <vtkWarpScalar.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main(int, char *[])
{
  // Create a random set of 100 points in the xy-plane in (0,10)x(0,10).
  // If you had instead started with a set of (x,y,z) points, you must copy
  // the zvalues into a FloatArray and set it as the data set's scalars,
  // and then set the z-coordinates to zero
  vtkSmartPointer<vtkPoints> randomPoints =
    vtkSmartPointer<vtkPoints>::New();

  vtkSmartPointer<vtkFloatArray> zvalues =
    vtkSmartPointer<vtkFloatArray>::New();
  zvalues->SetName("ZValues");

  unsigned int gridSize = 10;
  float maxHeight = 5;
  for ( unsigned int i = 0; i < 100; ++i )
  {
    double x = vtkMath::Random(0, gridSize);
    double y = vtkMath::Random(0, gridSize);
    double z = vtkMath::Random(0, maxHeight);

    //randomPoints->InsertNextPoint ( x, y, z);
    randomPoints->InsertNextPoint ( x, y, 0);
    zvalues->InsertNextValue(z);
  }

  // Add the grid points to a polydata object
  vtkSmartPointer<vtkPolyData> randomPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  randomPolyData->SetPoints ( randomPoints );
  randomPolyData->GetPointData()->SetScalars(zvalues);

  // Triangulate the grid points. If you do not have a mesh (points
  // only), the output will not be interpolated!
  vtkSmartPointer<vtkDelaunay2D> randomDelaunay =
    vtkSmartPointer<vtkDelaunay2D>::New();
  randomDelaunay->SetInputData ( randomPolyData );
  randomDelaunay->Update();

  // Create a grid of points to interpolate over
  vtkSmartPointer<vtkPoints> gridPoints =
    vtkSmartPointer<vtkPoints>::New();
  for ( unsigned int x = 0; x < gridSize; x++ )
  {
    for ( unsigned int y = 0; y < gridSize; y++ )
    {
      gridPoints->InsertNextPoint ( x, y, 0);
    }
  }

  // Create a dataset from the grid points
  vtkSmartPointer<vtkPolyData> gridPolyData =
    vtkSmartPointer<vtkPolyData>::New();
  gridPolyData->SetPoints(gridPoints);

  // Perform the interpolation
  vtkSmartPointer<vtkProbeFilter> probeFilter =
    vtkSmartPointer<vtkProbeFilter>::New();
  probeFilter->SetSourceConnection(randomDelaunay->GetOutputPort());
  probeFilter->SetInputData(gridPolyData); //
                                           // Interpolate 'Source' at these points
  probeFilter->Update();

  // Map the output zvalues to the z-coordinates of the data so that
  // we get a surface, rather than a flat grid with interpolated
  // scalars.
  vtkSmartPointer<vtkWarpScalar> gridWarpScalar =
    vtkSmartPointer<vtkWarpScalar>::New();
  gridWarpScalar->SetInputConnection(probeFilter->GetOutputPort());
  gridWarpScalar->Update();

  //////// Setup outputs ////////
  // Output random points
  // Map the output zvalues to the z-coordinates of the data
  vtkSmartPointer<vtkWarpScalar> randomWarpScalar =
    vtkSmartPointer<vtkWarpScalar>::New();
  randomWarpScalar->SetInputConnection(randomDelaunay->GetOutputPort());
  randomWarpScalar->Update();

  vtkSmartPointer<vtkXMLPolyDataWriter> randomWriter =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  randomWriter->SetFileName ( "randomSurface.vtp" );
  randomWriter->SetInputConnection(randomWarpScalar->GetOutputPort());
  randomWriter->Write();

  // Mesh the output grid points
  vtkSmartPointer<vtkDelaunay2D> gridDelaunay =
    vtkSmartPointer<vtkDelaunay2D>::New();
  gridDelaunay->SetInputConnection ( gridWarpScalar->GetOutputPort() );

  vtkSmartPointer<vtkXMLPolyDataWriter> gridWriter =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  gridWriter->SetFileName ( "gridSurface.vtp" );
  gridWriter->SetInputConnection ( gridDelaunay->GetOutputPort() );
  gridWriter->Write();

  ////////// Setup visualization ////////
  vtkSmartPointer<vtkDataSetMapper> randomMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  randomMapper->SetInputConnection(randomWarpScalar->GetOutputPort());
  randomMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> randomActor =
    vtkSmartPointer<vtkActor>::New();
  randomActor->SetMapper(randomMapper);
  randomActor->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
  randomActor->GetProperty()->SetPointSize(3);

  vtkSmartPointer<vtkDataSetMapper> gridMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  gridMapper->SetInputConnection(gridDelaunay->GetOutputPort());
  gridMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> gridActor =
    vtkSmartPointer<vtkActor>::New();
  gridActor->SetMapper(gridMapper);
  gridActor->GetProperty()->SetColor(0.0, 0.0, 1.0); //(R,G,B)
  gridActor->GetProperty()->SetPointSize(3);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle( style );

  renderer->AddActor(randomActor);
  renderer->AddActor(gridActor);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
