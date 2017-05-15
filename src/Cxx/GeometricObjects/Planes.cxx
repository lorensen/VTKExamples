#include <vtkSmartPointer.h>
#include <vtkPlanes.h>
#include <vtkCamera.h>
#include <vtkSphereSource.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>

int main(int, char *[])
{
  // one way
  {
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  double planesArray[24];

  camera->GetFrustumPlanes(1, planesArray);

  vtkSmartPointer<vtkPlanes> planes =
    vtkSmartPointer<vtkPlanes>::New();
  planes->SetFrustumPlanes(planesArray);
  }

  // another way
  {
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  double bounds[6];
  sphereSource->GetOutput()->GetBounds(bounds);

  vtkSmartPointer<vtkPlanes> planes =
    vtkSmartPointer<vtkPlanes>::New();
  planes->SetBounds(bounds);
  }
  
  return EXIT_SUCCESS;
}
