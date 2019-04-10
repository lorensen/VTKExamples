#include <vtkArrayCalculator.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(2.0, 0.0, 0.0);
  points->InsertNextPoint(3.0, 0.0, 0.0);

  vtkSmartPointer<vtkDoubleArray> array =
      vtkSmartPointer<vtkDoubleArray>::New();
  array->SetName("InputArray");
  array->SetNumberOfComponents(3);
  array->InsertNextTuple3(1, 10, 100);
  array->InsertNextTuple3(2, 20, 200);
  array->InsertNextTuple3(3, 30, 300);

  vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->AddArray(array);

  vtkSmartPointer<vtkArrayCalculator> arrayCalculator =
      vtkSmartPointer<vtkArrayCalculator>::New();
  arrayCalculator->SetInputData(polydata);
  arrayCalculator->AddVectorArrayName("InputArray");
  arrayCalculator->SetFunction("InputArray . jHat"); // Extract component '1' from the InputArray by taking the dot product of each tuple with the vector (0,1,0)
  arrayCalculator->SetResultArrayName("OutputArray");
  arrayCalculator->Update();

  vtkSmartPointer<vtkDoubleArray> outputArray =
    dynamic_cast<vtkDoubleArray*>(
      arrayCalculator->GetPolyDataOutput()->GetPointData()->GetArray("OutputArray"));

  for(vtkIdType i = 0; i < outputArray->GetNumberOfTuples(); i++)
  {
    double val = outputArray->GetValue(i);
    std::cout << "output value " << i << ": " << val << std::endl;
  }

  return EXIT_SUCCESS;
}
