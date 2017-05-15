#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>

int main(int, char *[])
{
  //Create a cube.
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource->SetCenter(0.0, 0.0, 0.0);
  cubeSource->SetXLength(.5);
  cubeSource->SetYLength(.5);
  cubeSource->SetZLength(.5);
  cubeSource->Update();
  
  //Write the file.
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(cubeSource->GetOutputPort());
  writer->SetFileName("cube.vtp");
  writer->Write();
  
  return EXIT_SUCCESS;
}
