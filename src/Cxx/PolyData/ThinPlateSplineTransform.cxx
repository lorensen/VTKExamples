#include <vtkImageGridSource.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkBMPReader.h>
#include <vtkImageBlend.h>
#include <vtkPoints.h>
#include <vtkThinPlateSplineTransform.h>
#include <vtkImageReslice.h>
#include <vtkSmartPointer.h>
#include <vtkDataObject.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTerrain.h>
#include <vtkImageMapper.h>
#include <vtkActor2D.h>

// Warp an image with a thin plate spline

int main(int argc, char *argv[])
{
  if ( argc < 2 )
  {
    std::cerr << "Usage: " << argv[0] << " Filename.bmp" << std::endl;
    return EXIT_FAILURE;
  }

  // First, create an image to warp
  vtkSmartPointer<vtkImageGridSource> imageGrid =
    vtkSmartPointer<vtkImageGridSource >::New();
  imageGrid->SetGridSpacing( 16, 16, 0 );
  imageGrid->SetGridOrigin( 0, 0, 0 );
  imageGrid->SetDataExtent( 0, 255, 0, 255, 0, 0 );
  imageGrid->SetDataScalarTypeToUnsignedChar();

  vtkSmartPointer<vtkLookupTable> table =
    vtkSmartPointer<vtkLookupTable >::New();
  table->SetTableRange( 0, 1 );
  table->SetAlphaRange( 0.0, 1.0 );
  table->SetHueRange( 0.15, 0.15 );
  table->SetSaturationRange( 1, 1 );
  table->SetValueRange( 0, 1 );
  table->Build();

  vtkSmartPointer<vtkImageMapToColors> alpha =
    vtkSmartPointer<vtkImageMapToColors >::New();
  alpha->SetInputConnection( imageGrid->GetOutputPort() );
  alpha->SetLookupTable( table );

  vtkSmartPointer<vtkBMPReader> reader =
    vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend >::New();
  blend->AddInputConnection( 0, reader->GetOutputPort() );
  blend->AddInputConnection( 0, alpha->GetOutputPort() );

  // Next, create a ThinPlateSpline transform

  vtkSmartPointer< vtkPoints > p1 = vtkSmartPointer< vtkPoints >::New();
  p1->SetNumberOfPoints( 8 );
  p1->SetPoint( 0, 0, 0, 0 );
  p1->SetPoint( 1, 0, 255, 0);
  p1->SetPoint( 2, 255, 0, 0 );
  p1->SetPoint( 3, 255, 255, 0 );
  p1->SetPoint( 4, 96, 96, 0 );
  p1->SetPoint( 5, 96, 159, 0 );
  p1->SetPoint( 6, 159, 159, 0 );
  p1->SetPoint( 7, 159, 96, 0 );

  vtkSmartPointer< vtkPoints > p2 = vtkSmartPointer< vtkPoints >::New();
  p2->SetNumberOfPoints( 8 );
  p2->SetPoint( 0, 0, 0, 0 );
  p2->SetPoint( 1, 0, 255, 0 );
  p2->SetPoint( 2, 255, 0, 0 );
  p2->SetPoint( 3, 255, 255, 0);
  p2->SetPoint( 4, 96, 159, 0 );
  p2->SetPoint( 5, 159, 159, 0 );
  p2->SetPoint( 6, 159, 96, 0 );
  p2->SetPoint( 7, 96, 96, 0 );

  vtkSmartPointer<vtkThinPlateSplineTransform> transform =
    vtkSmartPointer< vtkThinPlateSplineTransform >::New();
  transform->SetSourceLandmarks( p2 );
  transform->SetTargetLandmarks( p1 );
  transform->SetBasisToR2LogR();
  // You must invert the transform before passing it to vtkImageReslice
  transform->Inverse();

  vtkSmartPointer< vtkImageReslice > reslice =
    vtkSmartPointer<vtkImageReslice >::New();
  reslice->SetInputConnection( blend->GetOutputPort() );
  reslice->SetResliceTransform( transform );
  reslice->SetInterpolationModeToLinear();
  vtkSmartPointer< vtkImageMapper > map =
    vtkSmartPointer<vtkImageMapper >::New();
  map->SetInputConnection( reslice->GetOutputPort() );
  map->SetColorWindow( 255.0);
  map->SetColorLevel( 127.5 );
  map->SetZSlice( 0 );
  vtkSmartPointer< vtkActor2D > act =
    vtkSmartPointer< vtkActor2D >::New();
  act->SetMapper( map );
  act->SetPosition( 0.0, 0.0 );

  vtkSmartPointer< vtkRenderer > renderer =
    vtkSmartPointer<vtkRenderer >::New();
  renderer->AddActor( act );
  vtkSmartPointer< vtkRenderWindow > window =
    vtkSmartPointer<vtkRenderWindow >::New();
  window->SetSize( 640, 480 );
  window->AddRenderer(renderer);
  vtkSmartPointer< vtkRenderWindowInteractor > interactor =
    vtkSmartPointer< vtkRenderWindowInteractor >::New();
  interactor->SetRenderWindow(window);
  vtkSmartPointer< vtkInteractorStyleTerrain > style =
    vtkSmartPointer< vtkInteractorStyleTerrain >::New();
  interactor->SetInteractorStyle( style );
  window->Render();
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
