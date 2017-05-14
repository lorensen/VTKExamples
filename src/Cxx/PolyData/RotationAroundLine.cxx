#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>
 
int main(int, char *[])
{
  //Create a cone
  vtkSmartPointer<vtkConeSource> coneSource = 
    vtkSmartPointer<vtkConeSource>::New();
  
  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(coneSource->GetOutputPort());
  writer->SetFileName("original.vtp");
  writer->Write();
  }
  
  vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
  //transform->RotateWXYZ(double angle, double x, double y, double z);
  transform->RotateWXYZ(10, 0, 1, 0);
  
  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter = 
      vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  
  transformFilter->SetTransform(transform);
  transformFilter->SetInputConnection(coneSource->GetOutputPort());
  transformFilter->Update();
  
  {
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
        vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetInputConnection(transformFilter->GetOutputPort());
    writer->SetFileName("transformed.vtp");
    writer->Write();
  }
  
  return EXIT_SUCCESS;
}
