[VTKExamples](/index/)/[Cxx](/Cxx)/Widgets/CheckerboardWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestCheckerboardWidget.png?raw=true" width="256" />

### Description
Compare two images with a checkerboard. The widget permits interactive
control of the number of checkers in the x/y directions. Checkerboards
are often used to compare the results of image registration. For an
alternative image comparison widget try the
[RectilinearWipeWidget]([Cxx/Widgets/RectilinearWipeWidget).

**CheckerboardWidget.cxx**
```c++
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
#include <vtkObjectFactory.h>
#include <vtkInteractorStyleImage.h>

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
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  // render the image
  //
  iren->Initialize();
  renWin->Render();
  checkerWidget->On();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CheckerboardWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CheckerboardWidget MACOSX_BUNDLE CheckerboardWidget.cxx)
 
target_link_libraries(CheckerboardWidget ${VTK_LIBRARIES})
```

**Download and Build CheckerboardWidget**

Click [here to download CheckerboardWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CheckerboardWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball CheckerboardWidget.tar* has been downloaded and extracted,
```
cd CheckerboardWidget/build 
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
./CheckerboardWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

