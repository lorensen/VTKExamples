#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

#include "vtkTestFilterSelfProgressFilter.h"

void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);

int main(int /* argc */, char ** /* argv */)
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkTestFilterSelfProgressFilter> testFilter =
      vtkSmartPointer<vtkTestFilterSelfProgressFilter>::New();
  testFilter->SetInputConnection(sphereSource->GetOutputPort());
  testFilter->Update();

  return EXIT_SUCCESS;
}
