#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkSimplePointsWriter.h>

int main(int vtkNotUsed(argc), char* vtkNotUsed(argv)[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkSimplePointsWriter> writer =
    vtkSmartPointer<vtkSimplePointsWriter>::New();
  writer->SetFileName("test.xyz");
  writer->SetInputConnection(sphereSource->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
