#include <vtkDenseArray.h>
#include <vtkSmartPointer.h>
#include <vtkArrayWriter.h>
#include <vtkArrayData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array =
    vtkSmartPointer<vtkDenseArray<double> >::New();
  array->Resize(1,3);
  array->SetValue(0,0, 1.0);
  array->SetValue(0,1, 2.0);
  array->SetValue(0,2, 3.0);
  {
  // Method 1
  vtkSmartPointer<vtkArrayWriter> writer =
    vtkSmartPointer<vtkArrayWriter>::New();
  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);
  writer->SetInputData(arrayData);
  vtkStdString file1 = "Test1.txt";
  writer->Write(file1);
  }
  {
  vtkStdString file2 = "Test2.txt";
  // Method 2
  vtkSmartPointer<vtkArrayWriter> writer =
    vtkSmartPointer<vtkArrayWriter>::New();
  writer->Write(array, file2);
  }

  return EXIT_SUCCESS;
}
