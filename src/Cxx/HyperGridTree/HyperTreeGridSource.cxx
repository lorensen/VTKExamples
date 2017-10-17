#include <vtkHyperTreeGrid.h>
#include <vtkHyperTreeGridSource.h>
#include <vtkHyperTreeGridGeometry.h>

#include <vtkShrinkFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main( int argc, char* argv[] )
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
  vtkNew<vtkHyperTreeGridSource> source;
  source->SetMaximumLevel( 6 );
  source->SetGridSize( 3, 3, 2 );
  source->SetGridScale( 1.5, 1., .7 );
  source->SetDimension( 3 );
  source->SetBranchFactor( 4 );
  source->SetDescriptor( "RRR .R. .RR ..R ..R .R.|R.......................... ........................... ........................... .............R............. ....RR.RR........R......... .....RRRR.....R.RR......... ........................... ........................... ...........................|........................... ........................... ........................... ...RR.RR.......RR.......... ........................... RR......................... ........................... ........................... ........................... ........................... ........................... ........................... ........................... ............RRR............|........................... ........................... .......RR.................. ........................... ........................... ........................... ........................... ........................... ........................... ........................... ...........................|........................... ..........................." );
  source->Update();

  vtkNew<vtkShrinkFilter> shrink;
  shrink->SetInputConnection(source->GetOutputPort());
  shrink->SetShrinkFactor( .8 );

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(shrink->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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
  ren1->AddActor(actor);
  iren->Start();
  return EXIT_SUCCESS;
  }
