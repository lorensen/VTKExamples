[VTKExamples](/home/)/[Cxx](/Cxx)/Images/PickPixel

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestPickPixel.png?raw=true" width="256" />

### Description
This example demonstrates how to continuously retrieve pixel values using the mouse.

* Contributed by: Dean Inglis

**PickPixel.cxx**
```c++
#include <vtkVersion.h>
#include <vtkAssemblyPath.h>
#include <vtkCell.h>
#include <vtkCommand.h>
#include <vtkCornerAnnotation.h>
#include <vtkDataArray.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkPointData.h>
#include <vtkPropPicker.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>

// The mouse motion callback, to pick the image and recover pixel values
class vtkImageInteractionCallback1 : public vtkCommand
{
public:

  static vtkImageInteractionCallback1 *New()
  {
    return new vtkImageInteractionCallback1;
  }

  vtkImageInteractionCallback1()
  {
    this->Viewer = 0;
    this->Picker = 0;
    this->Annotation = 0;
    this->PointData = vtkPointData::New();
  }

  ~vtkImageInteractionCallback1()
  {
     this->Viewer = 0;
     this->Picker = 0;
     this->Annotation = 0;
     this->PointData->Delete();
  }

  void SetPicker(vtkPropPicker *picker)
  {
    this->Picker = picker;
  }

  void SetAnnotation(vtkCornerAnnotation *annotation)
  {
    this->Annotation = annotation;
  }

  void SetViewer(vtkImageViewer2 *viewer)
  {
    this->Viewer = viewer;
  }

    virtual void Execute(vtkObject *, unsigned long vtkNotUsed(event), void *)
    {
      //this->Viewer;
      vtkRenderWindowInteractor *interactor =
        this->Viewer->GetRenderWindow()->GetInteractor();
      vtkRenderer* renderer = this->Viewer->GetRenderer();
      vtkImageActor* actor = this->Viewer->GetImageActor();
      vtkImageData* image = this->Viewer->GetInput();
      vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
          interactor->GetInteractorStyle());

#if VTK_MAJOR_VERSION <= 5
      image->Update();
#endif

      // Pick at the mouse location provided by the interactor
      this->Picker->Pick( interactor->GetEventPosition()[0],
                          interactor->GetEventPosition()[1],
                          0.0, renderer );

      // There could be other props assigned to this picker, so
      // make sure we picked the image actor
      vtkAssemblyPath* path = this->Picker->GetPath();
      bool validPick = false;

      if( path )
      {
        vtkCollectionSimpleIterator sit;
        path->InitTraversal( sit );
        vtkAssemblyNode *node;
        for( int i = 0; i < path->GetNumberOfItems() && !validPick; ++i )
        {
          node = path->GetNextNode( sit );
          if( actor == vtkImageActor::SafeDownCast( node->GetViewProp() ) )
          {
            validPick = true;
          }
        }
      }

      if( !validPick )
      {
        this->Annotation->SetText( 0, "Off Image" );
        interactor->Render();
        // Pass the event further on
        style->OnMouseMove();
        return;
      }

      // Get the world coordinates of the pick
      double pos[3];
      this->Picker->GetPickPosition( pos );
      // Fixes some numerical problems with the picking
      double *bounds = actor->GetDisplayBounds();
      int axis = this->Viewer->GetSliceOrientation();
      pos[axis] = bounds[2*axis];

      vtkPointData* pd = image->GetPointData();
      if( !pd )
      {
        return;
      }

      this->PointData->InterpolateAllocate( pd, 1, 1 );

      // Use tolerance as a function of size of source data
      double tol2 = image->GetLength();
      tol2 = tol2 ? tol2*tol2 / 1000.0 : 0.001;

      // Find the cell that contains pos
      int subId;
      double pcoords[3], weights[8];
      vtkCell* cell = image->FindAndGetCell(
          pos, NULL, -1, tol2, subId, pcoords, weights );
      if( cell )
      {
        // Interpolate the point data
        this->PointData->InterpolatePoint( pd, 0, cell->PointIds, weights );
        int components =
          this->PointData->GetScalars()->GetNumberOfComponents();
        double* tuple = this->PointData->GetScalars()->GetTuple( 0 );

        std::string message = "Location: ( ";
        message += vtkVariant( pos[0] ).ToString();
        message += ", ";
        message += vtkVariant( pos[1] ).ToString();
        message += ", ";
        message += vtkVariant( pos[2] ).ToString();
        message += " )\nValue: ( ";

        for( int c = 0; c < components; ++c )
        {
          message += vtkVariant( tuple[ c ] ).ToString();
          if( c != components - 1 )
          {
            message += ", ";
          }
        }
        message += " )";
        this->Annotation->SetText( 0, message.c_str() );
        interactor->Render();
        style->OnMouseMove();
      }
    }

private:

  // Pointer to the viewer
  vtkImageViewer2 *Viewer;

  // Pointer to the picker
  vtkPropPicker *Picker;

  // Pointer to the annotation
  vtkCornerAnnotation *Annotation;

  // Interpolator
  vtkPointData* PointData;
};


int main ( int argc, char* argv[] )
{
//Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename(jpeg)" << std::endl;
    return EXIT_FAILURE;
  }

  //Parse input argument
  std::string inputFilename = argv[1];

  //Read the image
  vtkSmartPointer<vtkJPEGReader> jpegReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  if( !jpegReader->CanReadFile( inputFilename.c_str() ) )
  {
    std::cout << argv[0] << ": Error reading file "
              << inputFilename << endl << "Exiting..." << endl;
    return EXIT_FAILURE;
  }
  jpegReader->SetFileName ( inputFilename.c_str() );

  // Picker to pick pixels
  vtkSmartPointer<vtkPropPicker> propPicker =
    vtkSmartPointer<vtkPropPicker>::New();
  propPicker->PickFromListOn();

  // Give the picker a prop to pick
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  propPicker->AddPickList( imageViewer->GetImageActor() );

  // Visualize
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetInputConnection( jpegReader->GetOutputPort() );
  imageViewer->SetupInteractor( renderWindowInteractor );
  imageViewer->SetSize( 600, 600 );

  vtkRenderer* renderer = imageViewer->GetRenderer();
  renderer->ResetCamera();
  renderer->GradientBackgroundOn();
  renderer->SetBackground(0,0,0);
  renderer->SetBackground2(1,1,1);

  // Annotate the image with window/level and mouse over pixel information
  vtkSmartPointer<vtkCornerAnnotation> cornerAnnotation =
    vtkSmartPointer<vtkCornerAnnotation>::New();
  cornerAnnotation->SetLinearFontScaleFactor( 2 );
  cornerAnnotation->SetNonlinearFontScaleFactor( 1 );
  cornerAnnotation->SetMaximumFontSize( 20 );
  cornerAnnotation->SetText( 0, "Off Image" );
  cornerAnnotation->SetText( 3, "<window>\n<level>" );
  cornerAnnotation->GetTextProperty()->SetColor( 1,0,0);

  imageViewer->GetRenderer()->AddViewProp( cornerAnnotation );

  // Callback listens to MouseMoveEvents invoked by the interactor's style
  vtkSmartPointer<vtkImageInteractionCallback1> callback =
    vtkSmartPointer<vtkImageInteractionCallback1>::New();
  callback->SetViewer( imageViewer );
  callback->SetAnnotation( cornerAnnotation );
  callback->SetPicker( propPicker );

  // InteractorStyleImage allows for the following controls:
  // 1) middle mouse + move = camera pan
  // 2) left mouse + move = window/level
  // 3) right mouse + move = camera zoom
  // 4) middle mouse wheel scroll = zoom
  // 5) 'r' = reset window/level
  // 6) shift + 'r' = reset camera
  vtkInteractorStyleImage* imageStyle = imageViewer->GetInteractorStyle();
  imageStyle->AddObserver( vtkCommand::MouseMoveEvent, callback );

  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PickPixel)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PickPixel MACOSX_BUNDLE PickPixel.cxx)
 
target_link_libraries(PickPixel ${VTK_LIBRARIES})
```

**Download and Build PickPixel**

Click [here to download PickPixel](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PickPixel.tar) and its *CMakeLists.txt* file.
Once the *tarball PickPixel.tar* has been downloaded and extracted,
```
cd PickPixel/build 
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
./PickPixel
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

