#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkFiniteDifferenceGradientEstimator.h>
#include <vtkImageClip.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    std::cerr << "Required arguments: vtkFile" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1]; //  "/Data/ironProt.vtk";

  // Create the renderers, render window, and interactor
  vtkSmartPointer<vtkRenderWindow> renWin = 
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  renWin->AddRenderer(ren);
   
  // Read the data from a vtk file
  vtkSmartPointer<vtkStructuredPointsReader> reader = 
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();
 
  // Create a transfer function mapping scalar value to opacity
  vtkSmartPointer<vtkPiecewiseFunction> oTFun = 
    vtkSmartPointer<vtkPiecewiseFunction>::New();
  oTFun->AddSegment(0, 1.0, 256, 0.1);
 
  vtkSmartPointer<vtkColorTransferFunction> cTFun = 
    vtkSmartPointer<vtkColorTransferFunction>::New();
  cTFun->AddRGBPoint(   0, 1.0, 1.0, 1.0 );
  cTFun->AddRGBPoint( 255, 1.0, 1.0, 1.0 );
 
  // Need to crop to actually see minimum intensity
  vtkSmartPointer<vtkImageClip> clip = 
    vtkSmartPointer<vtkImageClip>::New();
  clip->SetInputConnection( reader->GetOutputPort() );
  clip->SetOutputWholeExtent(0,66,0,66,30,37);
  clip->ClipDataOn();
 
  vtkSmartPointer<vtkVolumeProperty> property = 
    vtkSmartPointer<vtkVolumeProperty>::New();
  property->SetScalarOpacity(oTFun);
  property->SetColor(cTFun);
  property->SetInterpolationTypeToLinear();
 
  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> mapper = 
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  mapper->SetBlendModeToMinimumIntensity();
  mapper->SetInputConnection( clip->GetOutputPort() );
 
  vtkSmartPointer<vtkVolume> volume = 
    vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(mapper);
  volume->SetProperty(property);
 
  ren->AddViewProp(volume);
  renWin->Render();
  iren->Start();
 
  return EXIT_SUCCESS;
}
