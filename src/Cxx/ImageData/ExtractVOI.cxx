#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkExtractVOI.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>
#include <vtkImageMandelbrotSource.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageMandelbrotSource> source =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  int* inputDims = source->GetOutput()->GetDimensions();
  std::cout << "Dims: " << " x: " << inputDims[0]
                        << " y: " << inputDims[1]
                        << " z: " << inputDims[2] << std::endl;
  std::cout << "Number of points: " << source->GetOutput()->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << source->GetOutput()->GetNumberOfCells() << std::endl;
  
  vtkSmartPointer<vtkExtractVOI> extractVOI =
      vtkSmartPointer<vtkExtractVOI>::New();
  extractVOI->SetInputConnection(source->GetOutputPort());
  extractVOI->SetVOI(inputDims[0]/4.,3.*inputDims[0]/4.,inputDims[1]/4.,3.*inputDims[1]/4., 0, 0);
  extractVOI->Update();

  vtkImageData* extracted = extractVOI->GetOutput();

  int* extractedDims = extracted->GetDimensions();
  std::cout << "Dims: " << " x: " << extractedDims[0]
                        << " y: " << extractedDims[1]
                        << " z: " << extractedDims[2] << std::endl;
  std::cout << "Number of points: " << extracted->GetNumberOfPoints() << std::endl;
  std::cout << "Number of cells: " << extracted->GetNumberOfCells() << std::endl;

  vtkSmartPointer<vtkImageCast> inputCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  inputCastFilter->SetInputConnection(source->GetOutputPort());
  inputCastFilter->SetOutputScalarTypeToUnsignedChar();
  inputCastFilter->Update();

  vtkSmartPointer<vtkImageCast> extractedCastFilter =
    vtkSmartPointer<vtkImageCast>::New();
  extractedCastFilter->SetInputData(extracted);
  extractedCastFilter->SetOutputScalarTypeToUnsignedChar();
  extractedCastFilter->Update();
  
  // Create actors
  vtkSmartPointer<vtkImageActor> inputActor =
    vtkSmartPointer<vtkImageActor>::New();
  inputActor->GetMapper()->SetInputConnection(
    inputCastFilter->GetOutputPort());

  vtkSmartPointer<vtkImageActor> extractedActor =
    vtkSmartPointer<vtkImageActor>::New();
  extractedActor->GetMapper()->SetInputConnection(
    extractedCastFilter->GetOutputPort());

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  // And one interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(inputActor);
  rightRenderer->AddActor(extractedActor);

  leftRenderer->ResetCamera();

  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  
  return EXIT_SUCCESS;
}
