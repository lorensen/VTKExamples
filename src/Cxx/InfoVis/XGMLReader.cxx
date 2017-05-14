#include <vtkPolyData.h>
#include <vtkXGMLReader.h>
#include <vtkSmartPointer.h>
#include <vtkUndirectedGraph.h>
#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Required parameters: Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  vtkSmartPointer<vtkXGMLReader> reader =
    vtkSmartPointer<vtkXGMLReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkUndirectedGraph* g = reader->GetOutput();

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(g);
  graphLayoutView->SetLayoutStrategy("Simple 2D");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();

  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
