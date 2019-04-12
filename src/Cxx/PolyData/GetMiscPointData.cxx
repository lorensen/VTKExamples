#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataNormals.h>
#include <string>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 3)
  {
    std::cout << "Required arguments: Filename ArrayName" << std::endl;
    return EXIT_FAILURE;
  }

  // Get filename from command line
  std::string filename = argv[1]; //first command line argument

  // Get array name
  std::string arrayName = argv[2]; //second command line argument
	
  // Read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  std::cout << "Reading " << filename << std::endl;
  reader->SetFileName(filename.c_str());
  reader->Update();

  // Extract the polydata
  vtkSmartPointer<vtkPolyData> polydata =
    reader->GetOutput();

  // Get the number of points in the polydata
  vtkIdType idNumPointsInFile = polydata->GetNumberOfPoints();

  vtkSmartPointer<vtkDoubleArray> array =
    dynamic_cast<vtkDoubleArray*>(polydata->GetPointData()->GetArray(arrayName.c_str()));

  if(array)
  {
      std::cout << "Got array " << arrayName
                << " with " << idNumPointsInFile << " values"
                << std::endl;
    for(int i = 0; i < idNumPointsInFile; i++)
    {
      double value;
      value = array->GetValue(i);
      std::cout << i << ": " << value << std::endl;
    }
  }
  else
  {
    std::cout << "The file " << filename
              << " does not have a PointData array named " << arrayName
              << std::endl;
  }

  return EXIT_SUCCESS;
}
