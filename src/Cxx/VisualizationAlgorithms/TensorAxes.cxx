// Translated from tenAxes.tcl

#include <vtkAxes.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPointLoad.h>
#include <vtkPolyDataMapper.h>
#include <vtkProp3D.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTensorGlyph.h>
#include <vtkTubeFilter.h>

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

  // Generate the tensor axes.
  vtkSmartPointer<vtkAxes> axes = vtkSmartPointer<vtkAxes>::New();
  axes->SetScaleFactor(0.5);

  vtkSmartPointer<vtkTubeFilter> tubeAxes =
    vtkSmartPointer<vtkTubeFilter>::New();
  tubeAxes->SetInputConnection(axes->GetOutputPort());
  tubeAxes->SetRadius(0.1);
  tubeAxes->SetNumberOfSides(6);

  vtkSmartPointer<vtkTensorGlyph> tensorAxes =
    vtkSmartPointer<vtkTensorGlyph>::New();
  tensorAxes->SetInputConnection(ptLoad->GetOutputPort());
  tensorAxes->SetSourceConnection(axes->GetOutputPort());
  tensorAxes->SetScaleFactor(10);
  tensorAxes->ClampScalingOn();

  // Map contour
  vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
  MakeLogLUT(lut);

  vtkSmartPointer<vtkPolyDataMapper> tensorAxesMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  tensorAxesMapper->SetInputConnection(tensorAxes->GetOutputPort());
  tensorAxesMapper->SetLookupTable(lut);
  plane->Update(); // force update for scalar range

  tensorAxesMapper->SetScalarRange(plane->GetOutput()->GetScalarRange());

  vtkSmartPointer<vtkActor> tensorActor = vtkSmartPointer<vtkActor>::New();
  tensorActor->SetMapper(tensorAxesMapper);

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

  //
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
  coneActor->GetProperty()->SetColor(colors->GetColor3d("BurlyWood").GetData());

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
  // Original
  lut->SetScaleToLog10();
  lut->SetHueRange(.6667, 0.0);
  lut->Build();
}
}
