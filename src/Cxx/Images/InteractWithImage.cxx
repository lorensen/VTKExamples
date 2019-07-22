#include <vtkSmartPointer.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>

#include <vtkImageMapper3D.h>
#include <vtkImageActor.h> // Note: this is a 3D actor (c.f. vtkImageMapper which is 2D)
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>

int main(int argc, char* argv[])
{
  // Parse input arguments
  if ( argc != 2 )
  {
    std::cout << "Required parameters: Filename" << std::endl;
    return EXIT_FAILURE;
  }
  std::string inputFilename = argv[1];

  // Read the image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor = 
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
  renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> window = 
    vtkSmartPointer<vtkRenderWindow>::New();
  window->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(window);

  // Setup interactor style (this is what implements the zooming, panning and brightness adjustment functionality)
  vtkSmartPointer<vtkInteractorStyleImage> style = 
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(style);
  
  // Render and start interaction
  window->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
