// Translated from tenEllip.tcl

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkColorSeries.h>
#include <vtkConeSource.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPointLoad.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProp3D.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTensorGlyph.h>

namespace
{
void MakeLogLUT(vtkLookupTable* lut);
}

int main(int, char*[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  // Create the RenderWindow, Renderer and interactive renderer.
  //
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Generate the tensors.
  vtkSmartPointer<vtkPointLoad> ptLoad = vtkSmartPointer<vtkPointLoad>::New();
  ptLoad->SetLoadValue(100.0);
  ptLoad->SetSampleDimensions(6, 6, 6);
  ptLoad->ComputeEffectiveStressOn();
  ptLoad->SetModelBounds(-10, 10, -10, 10, -10, 10);

  // Extract a plane of data.
  vtkSmartPointer<vtkImageDataGeometryFilter> plane =
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
  plane->SetInputConnection(ptLoad->GetOutputPort());
  plane->SetExtent(2, 2, 0, 99, 0, 99);

  // Generate the ellipsoids.
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetThetaResolution(8);
  sphere->SetPhiResolution(8);
  vtkSmartPointer<vtkTensorGlyph> tensorEllipsoids =
    vtkSmartPointer<vtkTensorGlyph>::New();
  tensorEllipsoids->SetInputConnection(ptLoad->GetOutputPort());
  tensorEllipsoids->SetSourceConnection(sphere->GetOutputPort());
  tensorEllipsoids->SetScaleFactor(10);
  tensorEllipsoids->ClampScalingOn();

  vtkSmartPointer<vtkPolyDataNormals> ellipNormals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  ellipNormals->SetInputConnection(tensorEllipsoids->GetOutputPort());

  // Map contour.
  vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
  MakeLogLUT(lut);
  vtkSmartPointer<vtkPolyDataMapper> tensorEllipsoidsMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  tensorEllipsoidsMapper->SetInputConnection(ellipNormals->GetOutputPort());
  tensorEllipsoidsMapper->SetLookupTable(lut);
  plane->Update(); // force update for scalar range
  tensorEllipsoidsMapper->SetScalarRange(plane->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> tensorActor = vtkSmartPointer<vtkActor>::New();
  tensorActor->SetMapper(tensorEllipsoidsMapper);

  // Create an outline around the data.
  //
  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(ptLoad->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor = vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

  // Create a cone whose apex indicates the application of load.
  //
  vtkSmartPointer<vtkConeSource> coneSrc =
    vtkSmartPointer<vtkConeSource>::New();
  coneSrc->SetRadius(0.5);
  coneSrc->SetHeight(2);
  vtkSmartPointer<vtkPolyDataMapper> coneMap =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMap->SetInputConnection(coneSrc->GetOutputPort());
  vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMap);
  coneActor->SetPosition(0, 0, 11);
  coneActor->RotateY(90);
  coneActor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());

  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetFocalPoint(0.113766, -1.13665, -1.01919);
  camera->SetPosition(-29.4886, -63.1488, 26.5807);
  camera->SetViewAngle(24.4617);
  camera->SetViewUp(0.17138, 0.331163, 0.927879);
  camera->SetClippingRange(1, 100);

  ren->AddActor(tensorActor);
  ren->AddActor(outlineActor);
  ren->AddActor(coneActor);
  ren->SetBackground(colors->GetColor3d("WhiteSmoke").GetData());
  ren->SetActiveCamera(camera);

  renWin->SetSize(512, 512);

  iren->Initialize();
  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}

namespace
{
void MakeLogLUT(vtkLookupTable* lut)
{
  // Make the lookup using a Brewer palette.
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetNumberOfColors(8);
  int colorSeriesEnum = colorSeries->BREWER_DIVERGING_SPECTRAL_8;
  colorSeries->SetColorScheme(colorSeriesEnum);
  lut->SetScaleToLog10();
  colorSeries->BuildLookupTable(lut, colorSeries->ORDINAL);
  lut->SetNanColor(1, 0, 0, 1);
  // Original
  // lut->SetScaleToLog10();
  // lut->SetHueRange(.6667, 0.0);
  // lut->Build();
}
}
