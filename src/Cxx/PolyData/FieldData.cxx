#include <vtkSmartPointer.h>
#include <vtkCellData.h>
#include <vtkMath.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkFieldData.h>
#include <vtkSphereSource.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> source = 
    vtkSmartPointer<vtkSphereSource>::New();
  source->Update();
 
  // Extract the polydata
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->ShallowCopy(source->GetOutput());
 
  vtkSmartPointer<vtkDoubleArray> location = 
    vtkSmartPointer<vtkDoubleArray>::New();
 
  // Create the data to store (here we just use (0,0,0))
  double locationValue[3] = {0,0,0};
 
  location->SetNumberOfComponents(3);
  location->SetName("MyDoubleArray");
  location->InsertNextTuple(locationValue);
  // The data is added to FIELD data (rather than POINT data as usual)
  polydata->GetFieldData()->AddArray(location);
 
  vtkSmartPointer<vtkIntArray> intValue =
    vtkSmartPointer<vtkIntArray>::New();
  intValue->SetNumberOfComponents(1);
  intValue->SetName("MyIntValue");
  intValue->InsertNextValue(5);

  polydata->GetFieldData()->AddArray(intValue);
 
  // Get the data back out
  vtkIntArray* retrievedArray = dynamic_cast<vtkIntArray*>(polydata->GetFieldData()->GetAbstractArray("MyIntValue"));

  std::cout << retrievedArray->GetValue(0) << std::endl;

  return EXIT_SUCCESS;
}
