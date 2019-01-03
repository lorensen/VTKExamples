#include <vtkSmartPointer.h>

#include <vtkTestPolyDataFilter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  
  vtkSmartPointer<vtkPolyData> inputPolydata =   
    vtkSmartPointer<vtkPolyData>::New();
  inputPolydata->SetPoints(points);
  
  std::cout << "Input points: " << inputPolydata->GetNumberOfPoints() 
            << std::endl;
  
  vtkSmartPointer<vtkTestPolyDataFilter> filter = 
    vtkSmartPointer<vtkTestPolyDataFilter>::New();
  filter->SetInputData(inputPolydata);
  filter->Update();
  
  vtkPolyData* outputPolydata = filter->GetOutput();
  
  std::cout << "Output points: " << outputPolydata->GetNumberOfPoints() 
            << std::endl;
  
  return EXIT_SUCCESS;
}
