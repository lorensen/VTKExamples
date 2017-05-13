#include <vtkSmartPointer.h>
#include <vtkRectilinearWipeWidget.h>
#include <vtkRectilinearWipeRepresentation.h>
#include <vtkJPEGReader.h>
#include <vtkImageRectilinearWipe.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty2D.h>
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkInteractorStyleImage.h>

// Define interaction style
class WipeInteractorStyle : public vtkInteractorStyleImage
{
public:
  static WipeInteractorStyle* New();
  vtkTypeMacro(WipeInteractorStyle, vtkInteractorStyleImage);

  virtual void OnChar()
  {
    if (this->Wipe)
    {
      vtkRenderWindowInteractor *rwi = this->Interactor;
      switch (rwi->GetKeyCode())
      {
        case '0':
          this->Wipe->SetWipe(0);
          break;
        case '1':
          this->Wipe->SetWipe(1);
          break;
        case '2':
          this->Wipe->SetWipe(2);
          break;
        case '3':
          this->Wipe->SetWipe(3);
          break;
        case '4':
          this->Wipe->SetWipe(4);
          break;
        case '5':
          this->Wipe->SetWipe(5);
          break;
        case '6':
          this->Wipe->SetWipe(6);
          break;
        default:
          this->Superclass::OnChar();
          break;
      }
    }
  }
  void SetWipe(vtkImageRectilinearWipe *wipe)
  {
    this->Wipe = wipe;
  }
protected:
  WipeInteractorStyle()
  {
    this->Wipe = NULL;
  }
private:
  vtkImageRectilinearWipe *Wipe;
};
vtkStandardNewMacro(WipeInteractorStyle);

int main( int argc, char *argv[] )
{
  if ( argc < 3 )
  {
    std::cerr << "Usage: " << argv[0]
              << " Input1Filename(jpg) Input2Filename(jpg)" << std::endl;
    return EXIT_FAILURE;
  }

  int wipeMode = 0;
  //Read the images
  vtkSmartPointer<vtkJPEGReader> reader1 =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader1->SetFileName ( argv[1] );

  vtkSmartPointer<vtkJPEGReader> reader2 =
    vtkSmartPointer<vtkJPEGReader>::New();
  reader2->SetFileName ( argv[2] );

  // Create a wipe pipeline
  vtkSmartPointer<vtkImageRectilinearWipe> wipe =
    vtkSmartPointer<vtkImageRectilinearWipe>::New();
  wipe->SetInputConnection(0,reader1->GetOutputPort());
  wipe->SetInputConnection(1,reader2->GetOutputPort());
  wipe->SetPosition(256,256);
  wipe->SetWipe(wipeMode);

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<WipeInteractorStyle> style =
    vtkSmartPointer<WipeInteractorStyle>::New();
  iren->SetInteractorStyle( style );
  style->SetWipe(wipe);

  vtkSmartPointer<vtkImageActor> wipeActor =
    vtkSmartPointer<vtkImageActor>::New();
  wipeActor->GetMapper()->SetInputConnection(wipe->GetOutputPort());

  // VTK widgets consist of two parts: the widget part that handles
  // event processing; and the widget representation that defines how
  // the widget appears in the scene
  // (i.e., matters pertaining to geometry).
  vtkSmartPointer<vtkRectilinearWipeWidget> wipeWidget =
    vtkSmartPointer<vtkRectilinearWipeWidget>::New();
  wipeWidget->SetInteractor(iren);

  vtkRectilinearWipeRepresentation *wipeWidgetRep=
    static_cast<vtkRectilinearWipeRepresentation *>(wipeWidget->GetRepresentation());

  wipeWidgetRep->SetImageActor(wipeActor);
  wipeWidgetRep->SetRectilinearWipe(wipe);
  wipeWidgetRep->GetProperty()->SetLineWidth(2.0);
  wipeWidgetRep->GetProperty()->SetOpacity(0.75);

  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(wipeActor);
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  // render the image
  //
  iren->Initialize();
  renWin->Render();
  wipeWidget->On();
  iren->Start();

  return EXIT_SUCCESS;
}
