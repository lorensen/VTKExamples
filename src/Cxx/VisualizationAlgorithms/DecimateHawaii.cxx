#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDecimatePro.h>
#include <vtkNamedColors.h>
#include <vtkPNGReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " honolulu.vtk" << std::endl;
    return EXIT_FAILURE;
  }

// This example shows how to use decimation to reduce a polygonal mesh. We also
// use mesh smoothing and generate surface normals to give a pleasing result.
//

  vtkSmartPointer<vtkPolyDataReader> hawaii =
    vtkSmartPointer<vtkPolyDataReader>::New();
  hawaii->SetFileName(argv[1]);

// We want to preserve topology (not let any cracks form). This may limit
// the total reduction possible, which we have specified at 90%.
//
  vtkSmartPointer<vtkDecimatePro> deci =
    vtkSmartPointer<vtkDecimatePro>::New();
  deci->SetInputConnection(hawaii->GetOutputPort());
  deci->SetTargetReduction(0.9);
  deci->PreserveTopologyOn();

  vtkSmartPointer<vtkPolyDataNormals> decimatedNormals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  decimatedNormals->SetInputConnection(deci->GetOutputPort());
  decimatedNormals->FlipNormalsOn();
  decimatedNormals->SetFeatureAngle(60);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> decimatedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  decimatedMapper->SetInputConnection(decimatedNormals->GetOutputPort());

  vtkSmartPointer<vtkActor> decimatedActor =
    vtkSmartPointer<vtkActor>::New();
  decimatedActor->SetMapper(decimatedMapper);
  decimatedActor->GetProperty()->SetColor(colors->GetColor3d("Aqua").GetData());
  decimatedActor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(decimatedNormals->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(colors->GetColor3d("Aqua").GetData());

// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkRenderer> renderer1 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer1->SetViewport( 0., 0., 0.5, 1. );

  vtkSmartPointer<vtkRenderer> renderer2 =
    vtkSmartPointer<vtkRenderer>::New();
  renderer2->SetViewport( 0.5, 0., 1., 1. );

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer1);
  renderWindow->AddRenderer(renderer2);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

// Add the actors to the renderer, set the background and size
//
  renderer1->AddActor(originalActor);
  renderer2->AddActor(decimatedActor);
  renderer1->SetBackground(colors->GetColor3d("Wheat").GetData());
  renderer2->SetBackground(colors->GetColor3d("Papaya_Whip").GetData());
  renderWindow->SetSize(800, 400);

// render the image
//
  vtkSmartPointer<vtkCamera> cam1 =
    vtkSmartPointer<vtkCamera>::New();
  cam1->SetFocalPoint(0, 0, 0);
  cam1->SetPosition(0, 0, 1);
  cam1->SetViewUp(0, 1, 0);
  renderer1->SetActiveCamera(cam1);
  renderer2->SetActiveCamera(cam1);
  renderer1->ResetCamera();
  cam1->Azimuth(30);
  cam1->Elevation(30);
  cam1->Dolly(1.3);
  renderer1->ResetCameraClippingRange();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
