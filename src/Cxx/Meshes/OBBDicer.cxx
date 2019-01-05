#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkOBBDicer.h>
#include <vtkOutlineCornerFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> inputPolyData;
  if(argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  // Create pipeline
  vtkSmartPointer<vtkOBBDicer> dicer =
    vtkSmartPointer<vtkOBBDicer>::New();
  dicer->SetInputData(inputPolyData);
  dicer->SetNumberOfPieces(4);
  dicer->SetDiceModeToSpecifiedNumberOfPieces();
  dicer->Update();

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(dicer->GetOutputPort());
  inputMapper->SetScalarRange(0, dicer->GetNumberOfActualPieces());

  std::cout << "Asked for: "
            << dicer->GetNumberOfPieces() << " pieces, got: "
            << dicer->GetNumberOfActualPieces() << std::endl;

  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);
   inputActor->GetProperty()->SetInterpolationToFlat();

  vtkSmartPointer<vtkOutlineCornerFilter> outline =
    vtkSmartPointer<vtkOutlineCornerFilter>::New();
  outline->SetInputData(inputPolyData);

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(0, 0, 0);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(outlineActor);
  renderer->AddActor(inputActor);
  renderer->SetBackground(.2, .3, .4);

  // Render the image
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
