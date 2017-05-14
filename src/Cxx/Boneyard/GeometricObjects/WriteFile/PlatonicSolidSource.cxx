#include <vtkSmartPointer.h>
#include <vtkPlatonicSolidSource.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPlatonicSolidSource> platonicSolidSource = 
      vtkSmartPointer<vtkPlatonicSolidSource>::New();
  platonicSolidSource->SetSolidTypeToOctahedron();
  platonicSolidSource->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("test.vtp");
  writer->SetInputConnection(platonicSolidSource->GetOutputPort());
  writer->Write();
  
  return EXIT_SUCCESS;
}
