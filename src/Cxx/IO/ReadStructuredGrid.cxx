#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkXMLStructuredGridReader.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
  // Verify input arguments
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0]
              << " Filename.vts e.g. StructuredGrid.vts" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read the file
  vtkSmartPointer<vtkXMLStructuredGridReader> reader =
    vtkSmartPointer<vtkXMLStructuredGridReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkSmartPointer<vtkStructuredGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
  geometryFilter->SetInputConnection(reader->GetOutputPort());
  geometryFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(geometryFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

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
