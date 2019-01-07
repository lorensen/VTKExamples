#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkImageData.h>
#include <vtkImageContinuousDilate3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkPNGReader.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();

  if(argc < 2)
  {
    // Create an image
    vtkSmartPointer<vtkImageCanvasSource2D> source =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
    source->SetScalarTypeToUnsignedChar();
    source->SetExtent(0, 200, 0, 200, 0, 0);
    source->SetDrawColor(0,0,0);
    source->FillBox(0,200,0,200);
    source->SetDrawColor(255,0,0);
    source->FillBox(100,150,100,150);
    source->Update();
    image->ShallowCopy(source->GetOutput());
  }
  else
  {
    vtkSmartPointer<vtkPNGReader> reader =
      vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    image->ShallowCopy(reader->GetOutput());
  }

  vtkSmartPointer<vtkImageContinuousDilate3D> dilateFilter =
    vtkSmartPointer<vtkImageContinuousDilate3D>::New();
  dilateFilter->SetInputData(image);
  dilateFilter->SetKernelSize(10,10,1);
  dilateFilter->Update();

  vtkSmartPointer<vtkDataSetMapper> originalMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  originalMapper->SetInputData(image);
  originalMapper->Update();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);

  vtkSmartPointer<vtkDataSetMapper> dilatedMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  dilatedMapper->SetInputConnection(dilateFilter->GetOutputPort());
  dilatedMapper->Update();

  vtkSmartPointer<vtkActor> dilatedActor =
    vtkSmartPointer<vtkActor>::New();
  dilatedActor->SetMapper(dilatedMapper);

  // Visualize
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

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

  leftRenderer->AddActor(originalActor);
  rightRenderer->AddActor(dilatedActor);

  leftRenderer->ResetCamera();
  rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
