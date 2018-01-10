#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkElevationFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetThetaResolution(12); sphere->SetPhiResolution(12);

  vtkSmartPointer<vtkTransform> aTransform =
    vtkSmartPointer<vtkTransform>::New();
  aTransform->Scale(1,1.5,2);

  vtkSmartPointer<vtkTransformFilter> transFilter =
    vtkSmartPointer<vtkTransformFilter>::New();
  transFilter->SetInputConnection(sphere->GetOutputPort());
  transFilter->SetTransform(aTransform);  

  vtkSmartPointer<vtkElevationFilter> colorIt =
    vtkSmartPointer<vtkElevationFilter>::New();
  colorIt->SetInputConnection(transFilter->GetOutputPort());
  colorIt->SetLowPoint(0,0,-1);
  colorIt->SetHighPoint(0,0,1);

  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(0.667, 0);
  lut->SetSaturationRange(1,1);
  lut->SetValueRange(1,1);

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetLookupTable(lut);
  mapper->SetInputConnection(colorIt->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer->AddActor(actor);
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->ResetCameraClippingRange();

  renWin->SetSize(640, 480);

  renWin->Render();

  // interact with data
  iren->Start();

  return EXIT_SUCCESS;
}

