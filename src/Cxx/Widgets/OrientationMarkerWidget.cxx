#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSuperquadricSource.h>

int main (int argc, char *argv[] )
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " Filename(.vtp)" << std::endl;
    return EXIT_FAILURE;
  }

  // Read the polydata for the icon
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkDataSetMapper> iconMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  iconMapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> iconActor =
    vtkSmartPointer<vtkActor>::New();
  iconActor->SetMapper(iconMapper);

  // Set up the renderer, window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground( 0.0980, 0.0980, 0.4392 );

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer( renderer );
  renWin->SetSize( 400, 400 );

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow( renWin );

  // Set up the widget
  vtkSmartPointer<vtkOrientationMarkerWidget> widget =
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
  widget->SetOrientationMarker( iconActor );
  widget->SetInteractor( iren );
  widget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
  widget->SetEnabled( 1 );
  widget->InteractiveOn();

  // Create a superquadric
  vtkSmartPointer<vtkSuperquadricSource> superquadricSource =
    vtkSmartPointer<vtkSuperquadricSource>::New();
  superquadricSource->SetPhiRoundness(.2);
  superquadricSource->SetThetaRoundness(.8);

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> superquadricMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  superquadricMapper->SetInputConnection(superquadricSource->GetOutputPort());

  vtkSmartPointer<vtkActor> superquadricActor =
    vtkSmartPointer<vtkActor>::New();
  superquadricActor->SetMapper(superquadricMapper);
  superquadricActor->GetProperty()->SetInterpolationToFlat();
  superquadricActor->GetProperty()->SetDiffuseColor(0.93, 0.57, 0.13);
  superquadricActor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
  superquadricActor->GetProperty()->SetDiffuse(.6);
  superquadricActor->GetProperty()->SetSpecular(.5);
  superquadricActor->GetProperty()->SetSpecularPower(5.0);

  renderer->AddActor(superquadricActor);
  renderer->ResetCamera();

  renWin->Render();

  iren->Initialize();

  iren->Start();

  return EXIT_SUCCESS;
}
