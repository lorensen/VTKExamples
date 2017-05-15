#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

#include "vtkTestPassInputTypeAlgorithmFilter.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
      vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 1.0);
  
  vtkSmartPointer<vtkPolyData> inputPolydata = 
      vtkSmartPointer<vtkPolyData>::New();
  inputPolydata->SetPoints(points);
  
  std::cout << "Input points: " << inputPolydata->GetNumberOfPoints() <<std:: endl;
  
  vtkSmartPointer<vtkTestPassInputTypeAlgorithmFilter> filter = 
      vtkSmartPointer<vtkTestPassInputTypeAlgorithmFilter>::New();
  filter->SetInput(inputPolydata);
  filter->Update();
  
  vtkPolyData* outputPolydata = vtkPolyData::SafeDownCast(filter->GetOutput());
  
  std::cout << "Output points: " << outputPolydata->GetNumberOfPoints() << std::endl;
  
  return EXIT_SUCCESS;
}
