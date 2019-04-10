#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>

void TypeSpecific();
void NonTypeSpecific();

int main(int, char *[])
{
  TypeSpecific();
  NonTypeSpecific();
  
  return EXIT_SUCCESS;
}

void TypeSpecific()
{
  // Create a point set
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  vtkSmartPointer<vtkDoubleArray> weights =
    vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfValues(2);
  weights->SetValue(0, 1);
  weights->SetValue(1, 2);
  
  polydata->GetPointData()->SetScalars(weights);
  
  double weight = dynamic_cast<vtkDoubleArray*>(polydata->GetPointData()->GetScalars())->GetValue(0);
  std::cout << "double weight: " << weight << std::endl;
  
  /*
  // This causes a crash because the array is not a vtkFloatArray
  double weightf = dynamic_cast<vtkFloatArray*>(polydata->GetPointData()->GetScalars())->GetValue(0);
  std::cout << "float weight: " << weightf << std::endl;
  */
}

void NonTypeSpecific()
{
  // Create a point set
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  vtkSmartPointer<vtkDoubleArray> weights =
    vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfValues(2);
  weights->SetValue(0, 1);
  weights->SetValue(1, 2);
  
  polydata->GetPointData()->SetScalars(weights);
  
  double weight = polydata->GetPointData()->GetScalars()->GetComponent(0,0);
  std::cout << "double weight: " << weight << std::endl;
  
  double weightf = polydata->GetPointData()->GetScalars()->GetComponent(0,0);
  std::cout << "float weight: " << weightf << std::endl;

}
