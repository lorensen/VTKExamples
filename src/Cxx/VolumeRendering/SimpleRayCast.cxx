#include <vtkCamera.h>
#include <vtkColorTransferFunction.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkNamedColors.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " ironProt.vtk" << std::endl;
    return EXIT_FAILURE;
  }

// This is a simple volume rendering example that
// uses a vtkFixedPointVolumeRayCastMapper

// Create the standard renderer, render window
// and interactor
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

// Create the reader for the data
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

// Create transfer mapping scalar value to opacity
  vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  opacityTransferFunction->AddPoint(20, 0.0);
  opacityTransferFunction->AddPoint(255, 0.2);

// Create transfer mapping scalar value to color
  vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
  colorTransferFunction->AddRGBPoint(64.0, 1.0, 0.0, 0.0);
  colorTransferFunction->AddRGBPoint(128.0, 0.0, 0.0, 1.0);
  colorTransferFunction->AddRGBPoint(192.0, 0.0, 1.0, 0.0);
  colorTransferFunction->AddRGBPoint(255.0, 0.0, 0.2, 0.0);

// The property describes how the data will look
  vtkSmartPointer<vtkVolumeProperty> volumeProperty =
    vtkSmartPointer<vtkVolumeProperty>::New();
  volumeProperty->SetColor(colorTransferFunction);
  volumeProperty->SetScalarOpacity(opacityTransferFunction);
  volumeProperty->ShadeOn();
  volumeProperty->SetInterpolationTypeToLinear();

// The mapper / ray cast function know how to render the data
  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  volumeMapper->SetInputConnection(reader->GetOutputPort());
  
// The volume holds the mapper and the property and
// can be used to position/orient the volume
  vtkSmartPointer<vtkVolume> volume =
    vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(volumeMapper);
  volume->SetProperty(volumeProperty);

  ren1->AddVolume(volume);
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
  ren1->GetActiveCamera()->Azimuth(45);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->ResetCameraClippingRange();
  ren1->ResetCamera();

  renWin->SetSize(600, 600);
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
