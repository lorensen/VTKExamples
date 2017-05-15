#include <vtkSmartPointer.h>
#include "vtkTestMultipleInputConnectionsFilter.h"

int main(int, char*[])
{
  //setup the first input
  vtkSmartPointer<vtkPoints> points1 =
    vtkSmartPointer<vtkPoints>::New();
  points1->InsertNextPoint(1.0, 2.0, 3.0);
  vtkSmartPointer<vtkPolyData> inputPolydata1 =
    vtkSmartPointer<vtkPolyData>::New();
  inputPolydata1->SetPoints(points1);

  //setup the second input
  vtkSmartPointer<vtkPoints> points2 =
    vtkSmartPointer<vtkPoints>::New();
  points2->InsertNextPoint(4.0, 5.0, 6.0);
  points2->InsertNextPoint(4.0, 5.0, 6.0);
  vtkSmartPointer<vtkPolyData> inputPolydata2 =
    vtkSmartPointer<vtkPolyData>::New();
  inputPolydata2->SetPoints(points2);

  vtkSmartPointer<vtkTesMultipleInputConnectionstFilter> filter =
    vtkSmartPointer<vtkTestMultipleInputConnectionsFilter>::New();
  filter->AddInputConnection(inputPolydata1->GetProducerPort());
  filter->AddInputConnection(inputPolydata2->GetProducerPort());
  filter->Update();

  vtkPolyData* outputPolydata = filter->GetOutput();

  std::cout << "Output points: " << outputPolydata->GetNumberOfPoints() << std::endl;

  return EXIT_SUCCESS;
}
