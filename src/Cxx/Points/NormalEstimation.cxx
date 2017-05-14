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

static void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph);

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

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  MakeGlyphs(normals->GetOutput(), radius * .2, glyph3D.GetPointer());

  vtkSmartPointer<vtkPolyDataMapper> glyph3DMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkActor> glyph3DActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor->SetMapper(glyph3DMapper);
  glyph3DActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

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
  sphereActor->GetProperty()->SetColor(1.0000, 0.4900, 0.2500);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(glyph3DActor);
  ren1->AddActor(sphereActor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.0);
  ren1->ResetCameraClippingRange();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

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
//  glyph->SetColorModeToColorByVector();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(size);
  glyph->OrientOn();
  glyph->Update();
}
