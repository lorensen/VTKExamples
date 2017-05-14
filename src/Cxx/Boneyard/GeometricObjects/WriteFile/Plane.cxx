#include <vtkXMLPolyDataWriter.h>
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPlaneSource> plane = 
    vtkSmartPointer<vtkPlaneSource>::New();
  plane->SetCenter(1.0, 0.0, 0.0);
  plane->SetNormal(1.0, 0.0, 0.0);
  
  vtkPolyData* pdata = plane->GetOutput();
    
  //write the file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInput(pdata);
  writer->SetFileName("plane.vtp");
  writer->Write();

  return EXIT_SUCCESS;
}
