#include <vtkSmartPointer.h>
#include <vtkPCANormalEstimation.h>
#include <vtkPointSource.h>

#include <vtkSphereSource.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkMath.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>

namespace
{
void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph);
}

int main (int, char *[])
{
  vtkMath::RandomSeed(4355412); // for test result consistency

  double radius = 1.0;
  vtkSmartPointer<vtkPointSource> points =
    vtkSmartPointer<vtkPointSource>::New();
  points->SetNumberOfPoints(1000);
  points->SetRadius(radius);
  points->SetCenter(0.0, 0.0, 0.0);
  points->SetDistributionToShell();

  int sampleSize = 10;
  vtkSmartPointer<vtkPCANormalEstimation> normals =
    vtkSmartPointer<vtkPCANormalEstimation>::New();
  normals->SetInputConnection (points->GetOutputPort());
  normals->SetSampleSize(sampleSize);
  normals->SetNormalOrientationToGraphTraversal();
  normals->Update();

  vtkSmartPointer<vtkNamedColors>colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  MakeGlyphs(normals->GetOutput(), radius * .2, glyph3D.GetPointer());

  vtkSmartPointer<vtkPolyDataMapper> glyph3DMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkActor> glyph3DActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor->SetMapper(glyph3DMapper);
  glyph3DActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Banana").GetData());

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetRadius(1.0);
  sphere->SetThetaResolution(41);
  sphere->SetPhiResolution(21);

  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> sphereActor =
    vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Tomato").GetData());

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  // Add the actors to the renderer, set the background and size
  //
  renderer->AddActor(glyph3DActor);
  renderer->AddActor(sphereActor);

  // Generate an interesting view
  //
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(120);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->GetActiveCamera()->Dolly(1.0);
  renderer->ResetCameraClippingRange();

  renderWindow->Render();
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
namespace
{
void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph)
{
  // Source for the glyph filter
  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();
  arrow->SetTipResolution(16);
  arrow->SetTipLength(.3);
  arrow->SetTipRadius(.1);

  glyph->SetSourceConnection(arrow->GetOutputPort());
  glyph->SetInputData(src);
  glyph->SetVectorModeToUseNormal();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(size);
  glyph->OrientOn();
  glyph->Update();
}
}
