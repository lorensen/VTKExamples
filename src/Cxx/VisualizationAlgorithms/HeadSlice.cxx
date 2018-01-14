#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkExtractVOI.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " FullHead.mhd" << std::endl;
    return EXIT_FAILURE;
  }

// Create the RenderWindow, Renderer and both Actors
//
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

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

  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  vtkSmartPointer<vtkExtractVOI> extractVOI =
      vtkSmartPointer<vtkExtractVOI>::New();
  extractVOI->SetInputConnection(reader->GetOutputPort());
  extractVOI->SetVOI(0, 255, 0, 255, 45, 45);

  vtkSmartPointer<vtkContourFilter> iso =
    vtkSmartPointer<vtkContourFilter>::New();
  iso->SetInputConnection(extractVOI->GetOutputPort());
  iso->GenerateValues(12, 500, 1150);

  vtkSmartPointer<vtkPolyDataMapper> isoMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(colors->GetColor3d("Wheat").GetData());

  vtkSmartPointer<vtkOutlineFilter> outline =
    vtkSmartPointer<vtkOutlineFilter>::New();
  outline->SetInputConnection(extractVOI->GetOutputPort());

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
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Dolly(1.5);
  ren1->ResetCameraClippingRange();

  renWin->SetSize(640, 480);

  renWin->Render();
  iren->Start();
  return EXIT_SUCCESS;
}
