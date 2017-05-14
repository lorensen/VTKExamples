#include <vtkSmartPointer.h>
#include <vtkGraph.h>
#include <vtkMutableUndirectedGraph.h>

#include "vtkTestGraphAlgorithmSource.h"

int main (int, char *[])
{
  vtkSmartPointer<vtkTestGraphAlgorithmSource> source =
    vtkSmartPointer<vtkTestGraphAlgorithmSource>::New();
  source->Update();
  
  vtkGraph* outputGraph = source->GetOutput();
  
  std::cout << "Output number of vertices: "
            << outputGraph->GetNumberOfVertices() << std::endl;
  
  return EXIT_SUCCESS;
}
