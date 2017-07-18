#include <vtkActor.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkScalarBarActor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include <vtkColorSeries.h>
#include <vtkNamedColors.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create a sphere fora some geometry
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetCenter(0,0,0);
  sphere->SetRadius(1);
  sphere->SetPhiResolution(30);
  sphere->SetThetaResolution(60);
  sphere->Update();

  // Create scalar data to associate with the vertices of the sphere
  int numPts = sphere->GetOutput()->GetPoints()->GetNumberOfPoints();
  vtkSmartPointer<vtkFloatArray> scalars =
    vtkSmartPointer<vtkFloatArray>::New();
  scalars->SetNumberOfValues( numPts );
  for( int i = 0; i < numPts; ++i )
  {
    scalars->SetValue(i,static_cast<float>(i)/numPts);
  }
  vtkSmartPointer<vtkPolyData> poly =
    vtkSmartPointer<vtkPolyData>::New();
  poly->DeepCopy(sphere->GetOutput());
  poly->GetPointData()->SetScalars(scalars);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(poly);
  mapper->ScalarVisibilityOn();
  mapper->SetScalarModeToUsePointData();
  mapper->SetColorModeToMapScalars();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetInterpolationToFlat();

  vtkSmartPointer<vtkScalarBarActor> scalarBar =
    vtkSmartPointer<vtkScalarBarActor>::New();
  scalarBar->SetLookupTable(mapper->GetLookupTable());
  scalarBar->SetTitle("Beachball");
  scalarBar->SetNumberOfLabels(4);

  // Create a lookup table to share between the mapper and the scalarbar
  vtkSmartPointer<vtkLookupTable> seriesLut =
    vtkSmartPointer<vtkLookupTable>::New();

  vtkSmartPointer<vtkColorSeries> series =
    vtkSmartPointer<vtkColorSeries>::New();
  int seriesEnum = series->BREWER_QUALITATIVE_SET3;
  series->SetColorScheme(seriesEnum);
  series->BuildLookupTable(seriesLut, series->ORDINAL);

  mapper->SetLookupTable(seriesLut);
  scalarBar->SetLookupTable(seriesLut);

  // Create a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  renderer->GradientBackgroundOn();
  renderer->SetBackground2(colors->GetColor3d("NavajoWhite").GetData());
  renderer->SetBackground(colors->GetColor3d("Crimson").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->AddActor2D(scalarBar);

  // Render the scene (lights and cameras are created automatically)
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
