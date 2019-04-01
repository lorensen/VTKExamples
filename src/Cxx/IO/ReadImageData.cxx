#include <vtkSmartPointer.h>
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

  auto colors = vtkNamedColors::New();

  // Read the file
  auto reader = vtkXMLImageDataReader::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // Visualize
   auto mapper = vtkDataSetMapper::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  auto actor = vtkActor::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();

  auto renderer = vtkRenderer::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
  renderer->SetBackground(colors->GetColor3d("Silver").GetData());

  auto renderWindow = vtkRenderWindow::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor = vtkRenderWindowInteractor::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->Render();
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
