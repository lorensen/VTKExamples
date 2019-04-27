#include "vtkSmartPointer.h"
#include "vtkOpenGLGPUVolumeRayCastMapper.h"

#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkContourValues.h"

#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkMetaImageReader.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"

#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkNamedColors.h"

int main (int argc, char *argv[])
{
  double iso1 = 500.0;
  double iso2 = 1150.0;

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " file.mnd [iso1=500] [iso2=1150]" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(argv[1]);

  auto colors =
    vtkSmartPointer<vtkNamedColors>::New();

  auto mapper =
    vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());
  mapper->AutoAdjustSampleDistancesOff();
  mapper->SetSampleDistance(0.5);
  mapper->SetBlendModeToIsoSurface();

  if (argc > 3)
  {
    iso1 = atof(argv[2]);
    iso2 = atof(argv[3]);
  }
  auto colorTransferFunction =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  colorTransferFunction->RemoveAllPoints();
  colorTransferFunction->AddRGBPoint(
    iso2,
    colors->GetColor3d("ivory").GetData()[0],
    colors->GetColor3d("ivory").GetData()[1],
    colors->GetColor3d("ivory").GetData()[2]);
  colorTransferFunction->AddRGBPoint(
    iso1,
    colors->GetColor3d("flesh").GetData()[0],
    colors->GetColor3d("flesh").GetData()[1],
    colors->GetColor3d("flesh").GetData()[2]);

  auto scalarOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  scalarOpacity->AddPoint(iso1, .3);
  scalarOpacity->AddPoint(iso2, 0.6);

  auto volumeProperty =
    vtkSmartPointer<vtkVolumeProperty>::New();
  volumeProperty->ShadeOn();
  volumeProperty->SetInterpolationTypeToLinear();
  volumeProperty->SetColor(colorTransferFunction);
  volumeProperty->SetScalarOpacity(scalarOpacity);

  auto volume =
    vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(mapper);
  volume->SetProperty(volumeProperty);

  auto renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddVolume(volume);
  renderer->SetBackground(colors->GetColor3d("cornflower").GetData());
  renderer->ResetCamera();

  auto renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(800, 600);
  renderWindow->AddRenderer(renderer);

  auto style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

  auto interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  interactor->SetInteractorStyle(style);

  // Add some contour values to draw iso surfaces
  volumeProperty->GetIsoSurfaceValues()->SetValue(0, iso1);
  volumeProperty->GetIsoSurfaceValues()->SetValue(1, iso2);

  // Generate a good view
  vtkSmartPointer<vtkCamera> aCamera =
    vtkSmartPointer<vtkCamera>::New();
  aCamera->SetViewUp (0, 0, -1);
  aCamera->SetPosition (0, -1, 0);
  aCamera->SetFocalPoint (0, 0, 0);
  
  renderer->SetActiveCamera(aCamera);
  renderer->ResetCamera();

  aCamera->Azimuth(30.0);
  aCamera->Elevation(30.0);
  aCamera->Dolly(1.5);
  renderer->ResetCameraClippingRange ();

  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
