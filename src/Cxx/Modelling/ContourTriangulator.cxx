#include "vtkSmartPointer.h"
#include "vtkContourTriangulator.h"
#include "vtkMarchingSquares.h"

#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPNGReader.h"
#include "vtkDataSetMapper.h"
#include "vtkCamera.h"
#include "vtkProperty.h"

int main(int argc, char* argv[])
{
  std::string inputFileName;
  if (argc > 1 )
  {
    inputFileName = argv[1];
  }
  int isoValue = 500;
  if (argc > 2)
  {
    isoValue = atoi(argv[2]);
  }

  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  if (!reader->CanReadFile(inputFileName.c_str()))
  {
    std::cerr << "Error: Could not read " << inputFileName << ".\n";
    return EXIT_FAILURE;
  }
  reader->SetFileName(inputFileName.c_str());
  reader->Update();

  vtkSmartPointer<vtkMarchingSquares> iso =
    vtkSmartPointer<vtkMarchingSquares>::New();
  iso->SetInputConnection(reader->GetOutputPort());
  iso->SetValue(0, isoValue);

  vtkSmartPointer<vtkDataSetMapper> isoMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

  vtkSmartPointer<vtkContourTriangulator> poly =
    vtkSmartPointer<vtkContourTriangulator>::New();
  poly->SetInputConnection(iso->GetOutputPort());

  vtkSmartPointer<vtkDataSetMapper> polyMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  polyMapper->SetInputConnection(poly->GetOutputPort());
  polyMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> polyActor =
    vtkSmartPointer<vtkActor>::New();
  polyActor->SetMapper(polyMapper);
  polyActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  // Standard rendering classes
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetMultiSamples(0);
  renWin->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(polyActor);
  renderer->AddActor(isoActor);

  // Standard testing code.
  renderer->SetBackground(0.5,0.5,0.5);
  renWin->SetSize(300,300);

  vtkCamera *camera = renderer->GetActiveCamera();
  renderer->ResetCamera();
  camera->Azimuth(180);

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
