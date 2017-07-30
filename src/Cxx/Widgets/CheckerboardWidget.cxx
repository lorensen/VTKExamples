#include <vtkSmartPointer.h>
#include <vtkCheckerboardWidget.h>
#include <vtkCheckerboardRepresentation.h>
#include <vtkJPEGReader.h>
#include <vtkImageCheckerboard.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty2D.h>
#include <vtkCommand.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>

int main( int argc, char *argv[] )
{
  if ( argc < 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  //Read the images
  vtkSmartPointer<vtkJPEGReader> reader1 =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader1->SetFileName ( argv[1] );

  vtkSmartPointer<vtkJPEGReader> reader2 =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader2->SetFileName ( argv[2] );

  // Create a checker pipeline
  vtkSmartPointer<vtkImageCheckerboard> checker =
    vtkSmartPointer<vtkImageCheckerboard>::New();
  checker->SetInputConnection(0,reader1->GetOutputPort());
  checker->SetInputConnection(1,reader2->GetOutputPort());
  checker->SetNumberOfDivisions(3,3,1);

  // Create the RenderWindow, Renderer and both Actors
  //
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

  vtkSmartPointer<vtkImageActor> checkerActor =
    vtkSmartPointer<vtkImageActor>::New();
  checkerActor->GetMapper()->SetInputConnection(checker->GetOutputPort());

  // VTK widgets consist of two parts: the widget part that handles
  // event processing; and the widget representation that defines how
  // the widget appears in the scene
  // (i.e., matters pertaining to geometry).
  vtkSmartPointer<vtkCheckerboardWidget> checkerWidget =
    vtkSmartPointer<vtkCheckerboardWidget>::New();
  checkerWidget->SetInteractor(iren);

  vtkCheckerboardRepresentation *checkerWidgetRep=
    static_cast<vtkCheckerboardRepresentation *>
    (checkerWidget->GetRepresentation());

  checkerWidgetRep->SetImageActor(checkerActor);
  checkerWidgetRep->SetCheckerboard(checker);

  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(checkerActor);
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
  renWin->SetSize(300, 300);

  // render the image
  //
  iren->Initialize();
  renWin->Render();
  checkerWidget->On();
  iren->Start();

  return EXIT_SUCCESS;
}
