[VTKExamples](/index/)/[Cxx](/Cxx)/Interaction/ImageRegion

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Interaction/TestImageRegion.png?raw=true" width="256" />

### Description
This example shows how to get the image coordinates of the corners of a BorderWidget.

It currently says the pick for the lower left corner of the border widget is valid even when it is off the image.

**ImageRegion.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkAssemblyNode.h>
#include <vtkAssemblyPath.h>
#include <vtkBorderRepresentation.h>
#include <vtkBorderWidget.h>
#include <vtkCommand.h>
#include <vtkCoordinate.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkPolyData.h>
#include <vtkPropPicker.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

class vtkBorderCallback : public vtkCommand
{
public:
  vtkBorderCallback(){}

  static vtkBorderCallback *New()
  {
    return new vtkBorderCallback;
  }

  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkBorderWidget *borderWidget =
      reinterpret_cast<vtkBorderWidget*>(caller);

    // Get the display coordinates of the two corners of the box
    vtkCoordinate* lowerLeftCoordinate = static_cast<vtkBorderRepresentation*>
       (borderWidget->GetRepresentation())->GetPositionCoordinate();
    double* lowerLeft;
    lowerLeft = lowerLeftCoordinate ->GetComputedWorldValue(this->Renderer);
    std::cout << "Lower left coordinate: " << lowerLeft[0] << ", " << lowerLeft[1] << std::endl;
    lowerLeft[2] = 0;

    vtkCoordinate* upperRightCoordinate = static_cast<vtkBorderRepresentation*>
       (borderWidget->GetRepresentation())->GetPosition2Coordinate();
    double* upperRight;
    upperRight = upperRightCoordinate ->GetComputedWorldValue(this->Renderer);
    std::cout << "Upper right coordinate: " << upperRight[0] << ", " << upperRight[1] << std::endl;
    upperRight[2] = 0;

    // Pick at the two corners of the box
    vtkSmartPointer<vtkPropPicker> picker =
      vtkSmartPointer<vtkPropPicker>::New();

//    int valid1 = picker->Pick( lowerLeft[0],
    picker->Pick( lowerLeft[0],
                  lowerLeft[1], 0.0, this->Renderer );

    vtkAssemblyPath* path = picker->GetPath();

    vtkProp* pickedProp = NULL;

    bool validPick = false;
    if( path )
    {
      std::cout << "There are " << path->GetNumberOfItems() << " items in the path." << std::endl;
      vtkCollectionSimpleIterator sit;
      path->InitTraversal( sit );
      vtkAssemblyNode *node;
      for( int i = 0; i < path->GetNumberOfItems(); ++i )
      {
        node = path->GetNextNode( sit );
        pickedProp = node->GetViewProp();
        if( this->ImageActor == vtkImageActor::SafeDownCast( pickedProp ) )
        {
          std::cout << "Correct actor picked." << std::endl;
          validPick = true;
          break;
        }
      }
    }

    if(!validPick)
    {
      std::cout << "Off Image" << std::endl;
    }
    else
    {
      double pos1[3];
      picker->GetPickPosition( pos1 );
      std::cout << "Lower Left Pick: " << pos1[0] << " " << pos1[1] << std::endl;
    }
    /*
      if(valid1 != 0)
        {
        std::cout << "Valid1: " << valid1 << std::endl;
        double pos1[3];
        picker->GetPickPosition( pos1 );
        std::cout << "Lower Left Pick: " << pos1[0] << " " << pos1[1] << std::endl;
        }
      else
        {
        std::cout << "Left - nothing was picked" << std::endl;
        }
      */

      /*
      int valid2 = picker->Pick( upperRight[0],
                    upperRight[1], 0.0, this->Renderer );
      if(valid2 != 0)
        {
        std::cout << "Valid2: " << valid2 << std::endl;
        double pos2[3];
        picker->GetPickPosition( pos2 );
        std::cout << "Upper right Pick: " << pos2[0] << " " << pos2[1] << std::endl;
        }
      else
        {
        std::cout << "Right - nothing was picked" << std::endl;
        }
      */
    std::cout << std::endl;
  }

  void SetRenderer(vtkSmartPointer<vtkRenderer> ren) {this->Renderer = ren;}
  void SetImageActor(vtkSmartPointer<vtkImageActor> im) {this->ImageActor = im;}

private:
  vtkSmartPointer<vtkRenderer> Renderer;
  vtkSmartPointer<vtkImageActor> ImageActor;

};

int main (int argc, char *argv[])
{
  // Parse input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              <<" Filename(.jpg)" << std::endl;
    return EXIT_FAILURE;
  }

  std::string InputFilename = argv[1];

  // Read the image
  vtkSmartPointer<vtkJPEGReader> jPEGReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( InputFilename.c_str() );

  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(jPEGReader->GetOutputPort());

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle( style );

  vtkSmartPointer<vtkBorderWidget> borderWidget =
    vtkSmartPointer<vtkBorderWidget>::New();
  borderWidget->SetInteractor(renderWindowInteractor);
  static_cast<vtkBorderRepresentation*>(borderWidget->GetRepresentation())->
     GetBorderProperty()->SetColor(1,0,0);
  borderWidget->SelectableOff();

  vtkSmartPointer<vtkBorderCallback> borderCallback =
    vtkSmartPointer<vtkBorderCallback>::New();
  borderCallback->SetRenderer(renderer);
  borderCallback->SetImageActor(actor);

  borderWidget->AddObserver(vtkCommand::InteractionEvent,borderCallback);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1);

  renderWindow->Render();
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  borderWidget->On();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageRegion)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageRegion MACOSX_BUNDLE ImageRegion.cxx)
 
target_link_libraries(ImageRegion ${VTK_LIBRARIES})
```

**Download and Build ImageRegion**

Click [here to download ImageRegion](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageRegion.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageRegion.tar* has been downloaded and extracted,
```
cd ImageRegion/build 
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
./ImageRegion
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

