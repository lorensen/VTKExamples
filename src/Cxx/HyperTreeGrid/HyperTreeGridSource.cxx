#include <vtkHyperTreeGridSource.h>

#include <vtkShrinkFilter.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>

int main( int, char*[] )
{
  // Set default argument values and options
  int dim = 3;
  int branch = 3;
  int max = 3;
  int nX = 2;
  int nY = 3;
  int nZ = 2;
  double sX = 1.5;
  double sY = 1.;
  double sZ = .7;
  int nContours = 1;
  bool skipAxisCut = false;
  bool skipContour = false;
  bool skipCut = false;
  bool skipGeometry = false;
  bool skipShrink = false;
  bool printDescriptor = false;

  // Create hyper tree grid source
  vtkSmartPointer<vtkHyperTreeGridSource> source =
    vtkSmartPointer<vtkHyperTreeGridSource>::New();
  source->SetMaximumLevel( 6 );
  source->SetGridSize( 3, 3, 2 );
  source->SetGridScale( 1.5, 1., .7 );
  source->SetDimension( 3 );
  source->SetBranchFactor( 4 );
  source->SetDescriptor( "RRR .R. .RR ..R ..R .R.|R.......................... ........................... ........................... .............R............. ....RR.RR........R......... .....RRRR.....R.RR......... ........................... ........................... ...........................|........................... ........................... ........................... ...RR.RR.......RR.......... ........................... RR......................... ........................... ........................... ........................... ........................... ........................... ........................... ........................... ............RRR............|........................... ........................... .......RR.................. ........................... ........................... ........................... ........................... ........................... ........................... ........................... ...........................|........................... ..........................." );
  source->Update();

  vtkSmartPointer<vtkShrinkFilter> shrink =
    vtkSmartPointer<vtkShrinkFilter>::New();
  shrink->SetInputConnection(source->GetOutputPort());
  shrink->SetShrinkFactor( .8 );

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(shrink->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Burlywood").GetData());

// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renderer->AddActor(actor);
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(150);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  renderWindow->SetSize(640, 480);
  interactor->Start();
  return EXIT_SUCCESS;
  }
