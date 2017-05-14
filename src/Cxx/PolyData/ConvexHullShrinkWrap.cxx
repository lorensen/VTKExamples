#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkPointSource.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(10);
  sphereSource->SetPhiResolution(50);
  sphereSource->SetThetaResolution(50);
  sphereSource->Update();
  
  vtkSmartPointer<vtkPointSource> pointSource = 
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(40);
  pointSource->SetRadius(2);
  pointSource->Update();
  
  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("input.vtp");
  writer->SetInputConnection(sphereSource->GetOutputPort());
  writer->Write();
  }
  
  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("points.vtp");
  writer->SetInputConnection(pointSource->GetOutputPort());
  writer->Write();
  }
    
  vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilter = 
    vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
  smoothFilter->SetInputConnection(0, sphereSource->GetOutputPort());
  smoothFilter->SetInputConnection(1, pointSource->GetOutputPort());
  smoothFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("output.vtp");
  writer->SetInputConnection(smoothFilter->GetOutputPort());
  writer->Write();
  
  return EXIT_SUCCESS;
}
