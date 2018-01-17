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
#include <vtkTexture.h>

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " fran_cut.vtk fran_cut.png" << std::endl;
    return EXIT_FAILURE;
  }

// This example shows how to use decimation to reduce a polygonal mesh. We also
// use mesh smoothing and generate surface normals to give a pleasing result.
//

// We start by reading some data that was originally captured from
// a Cyberware laser digitizing system.
//
  vtkSmartPointer<vtkPolyDataReader> fran =
    vtkSmartPointer<vtkPolyDataReader>::New();
  fran->SetFileName(argv[1]);

// Read the corresponding texture
  vtkSmartPointer<vtkPNGReader> textureReader =
    vtkSmartPointer<vtkPNGReader>::New();
  textureReader->SetFileName(argv[2]);

  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->InterpolateOn();
  texture->SetInputConnection(textureReader->GetOutputPort());

// We want to preserve topology (not let any cracks form). This may limit
// the total reduction possible, which we have specified at 90%.
//
  vtkSmartPointer<vtkDecimatePro> deci =
    vtkSmartPointer<vtkDecimatePro>::New();
  deci->SetInputConnection(fran->GetOutputPort());
  deci->SetTargetReduction(0.9);
  deci->PreserveTopologyOn();

  vtkSmartPointer<vtkPolyDataNormals> decimatedNormals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  decimatedNormals->SetInputConnection(deci->GetOutputPort());
  decimatedNormals->FlipNormalsOn();
  decimatedNormals->SetFeatureAngle(60);

  vtkSmartPointer<vtkPolyDataNormals> originalNormals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  originalNormals->SetInputConnection(fran->GetOutputPort());
  originalNormals->FlipNormalsOn();
  originalNormals->SetFeatureAngle(60);

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkPolyDataMapper> decimatedMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  decimatedMapper->SetInputConnection(decimatedNormals->GetOutputPort());

  vtkSmartPointer<vtkActor> decimatedActor =
    vtkSmartPointer<vtkActor>::New();
  decimatedActor->SetMapper(decimatedMapper);
  decimatedActor->GetProperty()->SetAmbient(.5);
  decimatedActor->GetProperty()->SetDiffuse(.5);
  decimatedActor->SetTexture(texture);

  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(originalNormals->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetAmbient(.5);
  originalActor->GetProperty()->SetDiffuse(.5);
  originalActor->SetTexture(texture);

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
  cam1->SetClippingRange(0.0475572, 2.37786);
  cam1->SetFocalPoint(0.052665, -0.129454, -0.0573973);
  cam1->SetPosition(0.327637, -0.116299, -0.256418);
  cam1->SetViewUp(-0.0225386, 0.999137, 0.034901);
  renderer1->SetActiveCamera(cam1);
  renderer2->SetActiveCamera(cam1);

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
