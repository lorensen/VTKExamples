#include <vtkDelaunay3D.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPUnstructuredGridWriter.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkDelaunay3D> delaunay =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay->SetInputConnection(sphereSource->GetOutputPort());
  delaunay->Update();

  vtkSmartPointer<vtkXMLPUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();
  writer->SetInputConnection(delaunay->GetOutputPort());
  writer->SetFileName("Test.pvtu");
  writer->SetNumberOfPieces(4);
  writer->SetStartPiece(0);
  writer->SetEndPiece(3);
  writer->Update();

  return EXIT_SUCCESS;
}
