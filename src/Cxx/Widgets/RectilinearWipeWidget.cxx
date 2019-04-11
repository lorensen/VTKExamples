#include <vtkSmartPointer.h>
#include <vtkRectilinearWipeWidget.h>
#include <vtkRectilinearWipeRepresentation.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
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
#include <vtkNamedColors.h>

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
              << " Input1Filename Input2Filename" << std::endl;
    return EXIT_FAILURE;
  }

  int wipeMode = 0;
  if (argc > 3)
  {
    wipeMode = atoi(argv[3]);
  }
  // Read the images
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader1;
  reader1.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader1->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageReader2> reader2;
  reader2.TakeReference(readerFactory->CreateImageReader2(argv[2]));
  reader2->SetFileName(argv[2]);

  // Create a wipe pipeline
  vtkSmartPointer<vtkImageRectilinearWipe> wipe =
    vtkSmartPointer<vtkImageRectilinearWipe>::New();
  wipe->SetInputConnection(0,reader1->GetOutputPort());
  wipe->SetInputConnection(1,reader2->GetOutputPort());
  wipe->SetPosition(256,256);
  wipe->SetWipe(wipeMode);

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());

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
  renWin->SetSize(300, 300);

  // render the image
  //
  renWin->Render();
  wipeWidget->On();
  iren->Start();

  return EXIT_SUCCESS;
}
