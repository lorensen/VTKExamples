#include <vtkFrustumSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCamera.h>
#include <vtkPlanes.h>

int main(int, char *[])
{
  //Create a camera.
  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  double planesArray[24];
  
  //Get the data from the camera describing the frustum planes.
  camera->GetFrustumPlanes(1, planesArray);
  
  //Create a set of planes from this data.
  vtkSmartPointer<vtkPlanes> planes = vtkSmartPointer<vtkPlanes>::New();
  planes->SetFrustumPlanes(planesArray);
  
  //Create a frustum.
  vtkSmartPointer<vtkFrustumSource> frustumSource = vtkSmartPointer<vtkFrustumSource>::New();
  frustumSource->SetPlanes(planes);
  frustumSource->Update();
  
  vtkPolyData* frustum = frustumSource->GetOutput();

  //Write the file.
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInput(frustum);
  writer->SetFileName("frustum.vtp");
  writer->Write();

  return EXIT_SUCCESS;
}
