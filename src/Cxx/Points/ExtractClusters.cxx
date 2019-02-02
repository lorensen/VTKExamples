#include <vtkSmartPointer.h>

#include <vtkEuclideanClusterExtraction.h>
#include <vtkPointSource.h>
#include <vtkAppendPolyData.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>

#include <vtkLookupTable.h>

#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main (int, char *[])
{
  vtkMath::RandomSeed(4355412); // for test result consistency
  double limits = 10;
  double radius = .5;

  vtkSmartPointer<vtkAppendPolyData> append =
    vtkSmartPointer<vtkAppendPolyData>::New();
  for (unsigned i = 0; i < 30; ++i)
  {
    vtkSmartPointer<vtkPointSource> points =
      vtkSmartPointer<vtkPointSource>::New();
    points->SetNumberOfPoints(800);
    points->SetRadius(2.5 * radius);
    points->SetCenter(vtkMath::Random(-limits, limits),
                      vtkMath::Random(-limits, limits),
                      vtkMath::Random(-limits, limits));
    points->SetDistributionToShell();

    append->AddInputConnection(points->GetOutputPort());
  }

  vtkSmartPointer<vtkEuclideanClusterExtraction> cluster =
    vtkSmartPointer<vtkEuclideanClusterExtraction>::New();
  cluster->SetInputConnection(append->GetOutputPort());
  cluster->SetExtractionModeToAllClusters();
  cluster->SetRadius(radius);
  cluster->ColorClustersOn();
  cluster->Update();

  std::cout << "Found " << cluster->GetNumberOfExtractedClusters()
            << " clusters within radius " << radius << std::endl;

  // Create a lookup table to map point data to colors
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  int tableSize = cluster->GetNumberOfExtractedClusters();
  lut->SetNumberOfTableValues(tableSize);
  lut->Build();

  // Fill in the lookup table
  for (unsigned int i = 0; static_cast<int>(i) < tableSize; ++i)
  {
    lut->SetTableValue(i,
                       vtkMath::Random(.25, 1.0),
                       vtkMath::Random(.25, 1.0),
                       vtkMath::Random(.25, 1.0),
                       1.0);
  }

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetRadius(radius / 2.0);

  vtkSmartPointer<vtkGlyph3D> glyphs =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyphs->SetInputConnection(cluster->GetOutputPort());
  glyphs->SetSourceConnection(sphere->GetOutputPort());
  glyphs->ScalingOff();
  glyphs->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphs->GetOutputPort());
  mapper->SetScalarRange(0, tableSize - 1);
  mapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(640, 512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer
  //
  ren1->AddActor(actor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.5);
  ren1->ResetCameraClippingRange();

  renWin->Render();
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
