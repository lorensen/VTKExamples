#include <vtkGenericDataObjectReader.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <string>

int main ( int argc, char *argv[] )
{
  // Ensure a filename was specified
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " InputFilename" << endl;
    return EXIT_FAILURE;
  }

  // Get the filename from the command line
  std::string inputFilename = argv[1];

  // Get all data from the file
  vtkSmartPointer<vtkGenericDataObjectReader> reader =
      vtkSmartPointer<vtkGenericDataObjectReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  // All of the standard data types can be checked and obtained like this:
  if(reader->IsFilePolyData())
  {
    std::cout << "output is a polydata" << std::endl;
    vtkPolyData* output = reader->GetPolyDataOutput();
    std::cout << "output has " << output->GetNumberOfPoints() << " points." << std::endl;
  }

  return EXIT_SUCCESS;
}
