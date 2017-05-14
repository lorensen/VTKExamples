#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPLYWriter.h>
	
int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    std::cerr << "Required arguments: input.vtp output.ply" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFileName = argv[1];
  std::string outputFileName = argv[2];

  vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFileName.c_str());
  reader->Update();

  vtkSmartPointer<vtkPLYWriter> writer = vtkSmartPointer<vtkPLYWriter>::New();
  writer->SetFileName(outputFileName.c_str());
  writer->SetInputConnection(reader->GetOutputPort());
  writer->Update();

  return EXIT_SUCCESS;
}
