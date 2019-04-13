#include <vtkSmartPointer.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkImageActor.h>
#include <vtkImageViewer2.h>
#include <vtkXMLImageDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0]
              << " Filename.vti" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  auto colors = vtkSmartPointer<vtkNamedColors>::New();

  // Read the file
  auto reader = vtkSmartPointer<vtkXMLImageDataReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // Visualize
   auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();
  actor->GetProperty()->SetColor(colors->GetColor3d("DarkSalmon").GetData());

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
