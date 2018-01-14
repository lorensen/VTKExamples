#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStructuredPointsReader.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " ironProt.vtk" << std::endl;
    return EXIT_SUCCESS;
  }

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

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

// create pipeline
//
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkContourFilter> iso =
    vtkSmartPointer<vtkContourFilter>::New();
  iso->SetInputConnection(reader->GetOutputPort());
  iso->SetValue(0, 128);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);

// Add the actors to the renderer, set the background and size
//
  ren1->AddActor(outlineActor);
  ren1->AddActor(isoActor);
  ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renWin->SetSize(640, 512);

// render the image
//
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(30);
  ren1->GetActiveCamera()->Elevation(30);
  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}
