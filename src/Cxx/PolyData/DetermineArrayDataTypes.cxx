#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkXMLPolyDataReader.h>
#include <vector>
#include <string>

void FindAllData(const std::string &inputFilename);

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " InputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];
  FindAllData(inputFilename);
	
  return EXIT_SUCCESS;
}

void FindAllData(const std::string &InputFilename)
{
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(InputFilename.c_str());
  reader->Update();
  vtkPolyData* polydata = reader->GetOutput();

  unsigned int numberOfArrays = polydata->GetPointData()->GetNumberOfArrays();
  std::cout << "NumArrays: " << numberOfArrays << std::endl;
	
  std::cout << "key: " << std::endl;;
  //more values can be found in <VTK_DIR>/Common/vtkSetGet.h
  std::cout << VTK_UNSIGNED_CHAR << " unsigned char" << std::endl;
  std::cout << VTK_UNSIGNED_INT << " unsigned int" << std::endl;
  std::cout << VTK_FLOAT << " float" << std::endl;
  std::cout << VTK_DOUBLE << " double" << std::endl;
	
  std::vector<std::string> arrayNames;
  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    //the following two lines are equivalent
    //arrayNames.push_back(polydata->GetPointData()->GetArray(i)->GetName());
    arrayNames.push_back(polydata->GetPointData()->GetArrayName(i));
    int dataTypeID = polydata->GetPointData()->GetArray(i)->GetDataType();
    std::cout << "Array " << i << ": " << arrayNames[i] << " (type: " << dataTypeID << ")" << std::endl;
  }
}
