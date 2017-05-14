#include <vtkSmartPointer.h>
#include <vtkPowerWeighting.h>
#include <vtkDenseArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array =
    vtkSmartPointer<vtkDenseArray<double> >::New();
  array->Resize(2);
  array->SetValue(0, 3);
  array->SetValue(1, 4);

  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);
  
  vtkSmartPointer<vtkPowerWeighting> powerWeighting =
    vtkSmartPointer<vtkPowerWeighting>::New();
  powerWeighting->SetPower(2);
  powerWeighting->SetInputConnection(arrayData->GetProducerPort());
  powerWeighting->Update();
  
  vtkSmartPointer<vtkArrayData> outputArrayData = powerWeighting->GetOutput();
  vtkSmartPointer<vtkDenseArray<double> > outputArray = vtkDenseArray<double>::SafeDownCast(outputArrayData->GetArray(0));

  std::cout << outputArray->GetValue(0) << std::endl;
  std::cout << outputArray->GetValue(1) << std::endl;
  
  return EXIT_SUCCESS;
}
