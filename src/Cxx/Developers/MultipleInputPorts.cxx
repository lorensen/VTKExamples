#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include "vtkTestMultipleInputPortsFilter.h"

int main (int /* argc */, char * /* argv */ [])
{
  vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetThetaResolution(5);
  sphereSource1->Update();

  vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetThetaResolution(10);
  sphereSource2->Update();

  vtkSmartPointer<vtkTestMultipleInputPortsFilter> filter =
      vtkSmartPointer<vtkTestMultipleInputPortsFilter>::New();
  filter->SetInputConnection(0, sphereSource1->GetOutputPort());
  filter->SetInputConnection(1, sphereSource2->GetOutputPort());
  filter->Update();

  return EXIT_SUCCESS;
}
