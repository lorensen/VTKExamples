#include <vtkImageData.h>
#include <vtkInteractorStyleImage.h>
#include <vtkTIFFWriter.h>
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkTIFFReader.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Required parameters: OutputFilename.tif" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1];

  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetExtent(0,9,0,9,0,0);
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetDrawColor(0, 0, 0, 0);
  imageSource->FillBox(0,9,0,9);
  imageSource->SetDrawColor(255, 0, 0, 0);
  imageSource->FillBox(5,7,5,7);
  imageSource->Update();

  vtkSmartPointer<vtkTIFFWriter> tiffWriter =
    vtkSmartPointer<vtkTIFFWriter>::New();
  tiffWriter->SetFileName(filename.c_str());
  tiffWriter->SetInputConnection(imageSource->GetOutputPort());
  tiffWriter->Write();

  // Read and display for verification
  vtkSmartPointer<vtkTIFFReader> reader =
    vtkSmartPointer<vtkTIFFReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();
  return EXIT_SUCCESS;
}
