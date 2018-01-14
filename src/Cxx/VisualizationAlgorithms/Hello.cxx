#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkImplicitModeller.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " hello.vtk" << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

// Create lines which serve as the "seed" geometry. The lines spell the
// word "hello".
//
  vtkSmartPointer<vtkPolyDataReader> reader =
    vtkSmartPointer<vtkPolyDataReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkPolyDataMapper> lineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  lineMapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> lineActor =
    vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  lineActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  lineActor->GetProperty()->SetLineWidth(3.0);

// Create implicit model with vtkImplicitModeller. This computes a scalar
// field which is the distance from the generating geometry. The contour
// filter then extracts the geometry at the distance value 0.25 from the
// generating geometry.
//
  vtkSmartPointer<vtkImplicitModeller> imp =
    vtkSmartPointer<vtkImplicitModeller>::New();
  imp->SetInputConnection(reader->GetOutputPort());
  imp->SetSampleDimensions(110, 40, 20);
  imp->SetMaximumDistance(0.25);
  imp->SetModelBounds(-1.0, 10.0, -1.0, 3.0, -1.0, 1.0);

  vtkSmartPointer<vtkContourFilter> contour =
    vtkSmartPointer<vtkContourFilter>::New();
  contour->SetInputConnection(imp->GetOutputPort());
  contour->SetValue(0, 0.25);

  vtkSmartPointer<vtkPolyDataMapper> impMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  impMapper->SetInputConnection(contour->GetOutputPort());
  impMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> impActor =
    vtkSmartPointer<vtkActor>::New();
  impActor->SetMapper(impMapper);
  impActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());
  impActor->GetProperty()->SetOpacity(0.5);

// Create the usual graphics stuff.
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

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(lineActor);
  ren1->AddActor(impActor);
  ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
  renWin->SetSize(640, 480);

  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  camera->SetFocalPoint(4.5, 1,  0);
  camera->SetPosition(4.5, 1.0, 6.73257);
  camera->SetViewUp(0,  1,  0);

  ren1->SetActiveCamera(camera);
  ren1->ResetCamera();
  camera->Dolly(1.3);
  camera->SetClippingRange(1.81325, 90.6627);

  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}
