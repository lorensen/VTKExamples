/* converted from:
 *
https://github.com/Kitware/VTK/blob/49fbbe479dfdf47c86c02d6cae48c41b9c844b04/Examples/VolumeRendering/Tcl/IntermixedUnstructuredGrid.tcl
*
*/

#include <vtkActor.h>
#include <vtkColorTransferFunction.h>
#include <vtkContourFilter.h>
#include <vtkDataSetTriangleFilter.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSLCReader.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkThreshold.h>
#include <vtkUnstructuredGridVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>

int main(int argc, char *argv[])
{
  if (argc < 3)
    {
    std::cerr << "Usage: " << argv[0] << " file.vtk file.slc" << std::endl;
    return EXIT_FAILURE;
    }

  // Create the reader for the data
  // This is the data the will be volume rendered
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

  // create a reader for the other data that will
  // be contoured and displayed as a polygonal mesh
  vtkSmartPointer<vtkSLCReader> reader2 =
    vtkSmartPointer<vtkSLCReader>::New();
  reader2->SetFileName(argv[2]);

  // convert from vtkImageData to vtkUnstructuredGrid, remove
  // any cells where all values are below 80
  vtkSmartPointer<vtkThreshold> thresh =
    vtkSmartPointer<vtkThreshold>::New();
  thresh->ThresholdByUpper(80);
  thresh->AllScalarsOff();
  thresh->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkDataSetTriangleFilter> trifilter =
    vtkSmartPointer<vtkDataSetTriangleFilter>::New();
  trifilter->SetInputConnection(thresh->GetOutputPort());

  // Create transfer mapping scalar value to opacity
  vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  opacityTransferFunction->AddPoint(80,  0.0);
  opacityTransferFunction->AddPoint(120, 0.2);
  opacityTransferFunction->AddPoint(255, 0.2);

  // Create transfer mapping scalar value to color
  vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  colorTransferFunction->AddRGBPoint( 80.0,0.0,0.0,0.0);
  colorTransferFunction->AddRGBPoint(120.0,0.0,0.0,1.0);
  colorTransferFunction->AddRGBPoint(160.0,1.0,0.0,0.0);
  colorTransferFunction->AddRGBPoint(200.0,0.0,1.0,0.0);
  colorTransferFunction->AddRGBPoint(255.0,0.0,1.0,1.0);

  // The property describes how the data will look
  vtkSmartPointer<vtkVolumeProperty> volumeProperty =
    vtkSmartPointer<vtkVolumeProperty>::New();
  volumeProperty->SetColor(colorTransferFunction);
  volumeProperty->SetScalarOpacity(opacityTransferFunction);
  volumeProperty->ShadeOff();
  volumeProperty->SetInterpolationTypeToLinear();

  // The mapper / ray cast function know how to render the data
  vtkSmartPointer<vtkUnstructuredGridVolumeRayCastMapper> volumeMapper =
    vtkSmartPointer<vtkUnstructuredGridVolumeRayCastMapper>::New();
  volumeMapper->SetInputConnection(trifilter->GetOutputPort());

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetSize(640,512);
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();

  // contour the second dataset
  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetValue(0, 80);
  contour->SetInputConnection(reader2->GetOutputPort());

  // create a mapper for the polygonal data
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(contour->GetOutputPort());
  mapper->ScalarVisibilityOff();

  // create an actor for the polygonal data
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  ren1->AddViewProp(actor);

  ren1->SetBackground(0.1,0.4,0.2);

  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkVolume> volume =
    vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(volumeMapper);
  volume->SetProperty(volumeProperty);

  ren1->AddVolume(volume);

  ren1->ResetCamera();

  // Render composite. In default mode. For coverage.
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
