#include <vtkSmartPointer.h>
#include <vtkOrientationMarkerWidget.h>

#include <vtkXMLPolyDataReader.h>
#include <vtkSuperquadricSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkNamedColors.h>

int main (int argc, char *argv[] )
{
  // Parse command line arguments
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " Filename(.vtp)" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

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
  iconActor->GetProperty()->SetColor(colors->GetColor3d("Silver").GetData());

  // Set up the renderer, window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

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
  widget->SetOrientationMarker( iconActor );
  widget->SetInteractor( iren );
  widget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
  widget->SetOutlineColor(colors->GetColor3d("Wheat").GetRed(),
                          colors->GetColor3d("Wheat").GetGreen(),
                          colors->GetColor3d("Wheat").GetBlue());
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
  superquadricActor->GetProperty()->SetDiffuseColor(colors->GetColor3d("Carrot").GetData());
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
