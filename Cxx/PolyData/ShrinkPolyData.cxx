#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkShrinkPolyData.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(10);
  sphereSource->SetPhiResolution(50);
  sphereSource->SetThetaResolution(50);
  sphereSource->Update();

  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("sphere.vtp");
  writer->SetInputConnection(sphereSource->GetOutputPort());
  writer->Write();
  }

  vtkSmartPointer<vtkShrinkPolyData> shrinkFilter =
      vtkSmartPointer<vtkShrinkPolyData>::New();
  shrinkFilter->SetInputConnection(sphereSource->GetOutputPort());
  shrinkFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("output.vtp");
  writer->SetInputConnection(shrinkFilter->GetOutputPort());
  writer->Write();
  
  return EXIT_SUCCESS;
}
