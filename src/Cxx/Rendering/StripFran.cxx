#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDecimatePro.h>
#include <vtkMaskPolyData.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStripper.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " fran_cut.vtk" << std::endl;
    return EXIT_FAILURE;
  }
// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

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

// create a cyberware source
//
  vtkSmartPointer<vtkPolyDataReader> cyber =
    vtkSmartPointer<vtkPolyDataReader>::New();
  cyber->SetFileName(argv[1]);

  vtkSmartPointer<vtkDecimatePro> deci =
    vtkSmartPointer<vtkDecimatePro>::New();
  deci->SetInputConnection(cyber->GetOutputPort());
  deci->SetTargetReduction(0.7);
  deci->PreserveTopologyOn();

  vtkSmartPointer<vtkPolyDataNormals> normals =
    vtkSmartPointer<vtkPolyDataNormals>::New();
  normals->SetInputConnection(deci->GetOutputPort());
  
  vtkSmartPointer<vtkMaskPolyData> mask =
    vtkSmartPointer<vtkMaskPolyData>::New();
  mask->SetInputConnection(deci->GetOutputPort());
  mask->SetOnRatio(2);

  vtkSmartPointer<vtkPolyDataMapper> cyberMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cyberMapper->SetInputConnection(mask->GetOutputPort());

  vtkSmartPointer<vtkActor> cyberActor =
    vtkSmartPointer<vtkActor>::New();
  cyberActor->SetMapper(cyberMapper);
  cyberActor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());

  vtkSmartPointer<vtkStripper> stripper =
    vtkSmartPointer<vtkStripper>::New();
  stripper->SetInputConnection(cyber->GetOutputPort());

  vtkSmartPointer<vtkMaskPolyData> stripperMask =
    vtkSmartPointer<vtkMaskPolyData>::New();
  stripperMask->SetInputConnection(stripper->GetOutputPort());
  stripperMask->SetOnRatio(2);

  vtkSmartPointer<vtkPolyDataMapper> stripperMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  stripperMapper->SetInputConnection(stripperMask->GetOutputPort());

  vtkSmartPointer<vtkActor> stripperActor =
    vtkSmartPointer<vtkActor>::New();
  stripperActor->SetMapper(stripperMapper);
  stripperActor->GetProperty()->SetColor(colors->GetColor3d("Flesh").GetData());

// Add the actors to the renderer, set the background and size
//
  renderer1->AddActor(stripperActor);
  renderer2->AddActor(cyberActor);
  renderer1->SetBackground(colors->GetColor3d("Wheat").GetData());
  renderer2->SetBackground(colors->GetColor3d("Papaya_Whip").GetData());
  renderWindow->SetSize(1024, 640);

// render the image
//
  vtkSmartPointer<vtkCamera> cam1 =
    vtkSmartPointer<vtkCamera>::New();
  cam1->SetFocalPoint(0, 0, 0);
  cam1->SetPosition(1, 0, 0);
  cam1->SetViewUp(0, 1, 0);
  renderer1->SetActiveCamera(cam1);
  renderer2->SetActiveCamera(cam1);
  renderer1->ResetCamera();
  cam1->Azimuth(30);
  cam1->Elevation(30);
  cam1->Dolly(1.4);
  renderer1->ResetCameraClippingRange();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
