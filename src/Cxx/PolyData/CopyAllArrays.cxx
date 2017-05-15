#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>

void ManualMethod(vtkPolyData* input);
void AutomaticMethod(vtkPolyData* input);

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkPolyData* polydata = sphereSource->GetOutput();

  vtkSmartPointer<vtkDoubleArray> doubles =
    vtkSmartPointer<vtkDoubleArray>::New();
  doubles->SetName("Doubles");
  doubles->SetNumberOfTuples(polydata->GetNumberOfPoints());

  polydata->GetPointData()->AddArray(doubles);

  vtkSmartPointer<vtkIntArray> ints =
    vtkSmartPointer<vtkIntArray>::New();
  ints->SetName("Ints");
  ints->SetNumberOfTuples(polydata->GetNumberOfPoints());

  polydata->GetPointData()->AddArray(ints);

  ManualMethod(polydata);
  AutomaticMethod(polydata);

  return EXIT_SUCCESS;
}

void ManualMethod(vtkPolyData* input)
{
  unsigned int numberOfArrays = input->GetPointData()->GetNumberOfArrays();
  std::cout << "There are " << numberOfArrays << " arrays." << std::endl;

  vtkSmartPointer<vtkPolyData> newPolyData =
    vtkSmartPointer<vtkPolyData>::New();

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << input->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << input->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;

    newPolyData->GetPointData()->AddArray(input->GetPointData()->GetArray(i));
  }

  std::cout << "new polydata: " << std::endl;

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << newPolyData->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << newPolyData->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;
  }

}

void AutomaticMethod(vtkPolyData* input)
{
  unsigned int numberOfArrays = input->GetPointData()->GetNumberOfArrays();
  std::cout << "There are " << numberOfArrays << " arrays." << std::endl;

  vtkSmartPointer<vtkPolyData> newPolyData =
    vtkSmartPointer<vtkPolyData>::New();

  newPolyData->GetPointData()->PassData(input->GetPointData());

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << input->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << input->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;
  }

  std::cout << "new polydata: " << std::endl;

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << newPolyData->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << newPolyData->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;
  }

}
