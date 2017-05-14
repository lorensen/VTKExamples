#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include "vtkTestFailedFilter.h"

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkTestFailedFilter> filter =
      vtkSmartPointer<vtkTestFailedFilter>::New();
  filter->SetInputConnection(sphereSource->GetOutputPort());
  filter->Update();

  if(filter->GetErrorCode() == 23)
  {
    std::cout << "Filter failed!" << std::endl;
  }

  return EXIT_SUCCESS;
}
