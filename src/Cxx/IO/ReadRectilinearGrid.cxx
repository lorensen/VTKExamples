#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkXMLRectilinearGridReader.h>
#include <vtkRectilinearGridGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " Filename.vtr e.g. RectilinearGrid.vtr" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse arguments
  std::string inputFilename = argv[1];

  // Read the file
  vtkSmartPointer<vtkXMLRectilinearGridReader> reader =
    vtkSmartPointer<vtkXMLRectilinearGridReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
/*
  vtkSmartPointer<vtkRectilinearGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkRectilinearGridGeometryFilter>::New();
  geometryFilter->SetInputConnection(reader->GetOutputPort());
  geometryFilter->Update();
*/
  // Visualize
  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  //mapper->SetInputConnection(geometryFilter->GetOutputPort());
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetRepresentationToWireframe();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
