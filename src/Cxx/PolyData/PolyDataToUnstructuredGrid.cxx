#include <vtkAppendFilter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkXMLUnstructuredGridWriter.h>

int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(5.0);
  sphereSource->Update();

  // Combine the two data sets
  vtkSmartPointer<vtkAppendFilter> appendFilter =
    vtkSmartPointer<vtkAppendFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  appendFilter->AddInput(sphereSource->GetOutput());
#else
  appendFilter->AddInputData(sphereSource->GetOutput());
#endif
  appendFilter->Update();

  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
     vtkSmartPointer<vtkUnstructuredGrid>::New();
  unstructuredGrid->ShallowCopy(appendFilter->GetOutput());

  // Write the unstructured grid
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName("UnstructuredGrid.vtu");
  #if VTK_MAJOR_VERSION <= 5
    writer->SetInput(unstructuredGrid);
  #else
    writer->SetInputData(unstructuredGrid);
  #endif
  writer->Write();

  return EXIT_SUCCESS;
}
