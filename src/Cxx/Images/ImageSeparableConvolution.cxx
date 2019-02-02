#include <vtkImageActor.h>
#include <vtkFloatArray.h>
#include <vtkImageCast.h>
#include <vtkImageMapper3D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageSeparableConvolution.h>
#include <vtkImageThreshold.h>

int main(int argc, char *argv[])
{
  // Handle the arguments
  if( argc < 2 )
  {
    std::cout << "Required arguments: BinaryImage.png" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the image
  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkFloatArray> xKernel =
    vtkSmartPointer<vtkFloatArray>::New();
  xKernel->SetNumberOfTuples(5);
  xKernel->SetNumberOfComponents(1);
  xKernel->SetValue(0,1);
  xKernel->SetValue(1,1);
  xKernel->SetValue(2,1);
  xKernel->SetValue(3,1);
  xKernel->SetValue(4,1);

  vtkSmartPointer<vtkImageSeparableConvolution> convolutionFilter =
    vtkSmartPointer<vtkImageSeparableConvolution>::New();
  convolutionFilter->SetInputConnection(reader->GetOutputPort());
  convolutionFilter->SetXKernel(xKernel);
  convolutionFilter->Update();

  vtkSmartPointer<vtkImageActor> originalActor =
    vtkSmartPointer<vtkImageActor>::New();
  originalActor->GetMapper()->SetInputConnection(
    reader->GetOutputPort());

  vtkSmartPointer<vtkImageCast> convolutionCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  convolutionCastFilter->SetInputConnection(convolutionFilter->GetOutputPort());
  convolutionCastFilter->SetOutputScalarTypeToUnsignedChar();
  convolutionCastFilter->Update();

  vtkSmartPointer<vtkImageActor> convolutionActor =
    vtkSmartPointer<vtkImageActor>::New();
  convolutionActor->GetMapper()->SetInputConnection(
    convolutionCastFilter->GetOutputPort());

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double convolutionViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> originalRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  originalRenderer->SetViewport(originalViewport);
  originalRenderer->AddActor(originalActor);
  originalRenderer->ResetCamera();
  originalRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> convolutionRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  convolutionRenderer->SetViewport(convolutionViewport);
  convolutionRenderer->AddActor(convolutionActor);
  convolutionRenderer->ResetCamera();
  convolutionRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(originalRenderer);
  renderWindow->AddRenderer(convolutionRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return  EXIT_SUCCESS;
}
