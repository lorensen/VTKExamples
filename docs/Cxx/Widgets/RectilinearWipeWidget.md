[VTKExamples](/index/)/[Cxx](/Cxx)/Widgets/RectilinearWipeWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestRectilinearWipeWidget.png?raw=true" width="256" />

### Description
This example illustrates the Rectilinear Wipe widget. This widget is
useful for comparing two images. There are 7 different image
comparison modes.  A rectilinear wipe is a 2x2 checkerboard pattern
created by combining two separate images, where various combinations
of the checker squares are possible. Using this widget, the user can
adjust the layout of the checker pattern, such as moving the center
point, moving the horizontal separator, or moving the vertical
separator.

Pressing keys 0-6 select the various wipe modes.

For an alternative image comparison widget try the [Checkerboard widget]](Cxx/Widgets/CheckerboardWidget). 

**RectilinearWipeWidget.cxx**
```c++
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
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RectilinearWipeWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RectilinearWipeWidget MACOSX_BUNDLE RectilinearWipeWidget.cxx)
 
target_link_libraries(RectilinearWipeWidget ${VTK_LIBRARIES})
```

**Download and Build RectilinearWipeWidget**

Click [here to download RectilinearWipeWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RectilinearWipeWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball RectilinearWipeWidget.tar* has been downloaded and extracted,
```
cd RectilinearWipeWidget/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./RectilinearWipeWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

