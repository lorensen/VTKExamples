#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellArray.h>
#include <vtkGeometryFilter.h>
#include <vtkPointSource.h>

int main(int, char *[])
{ 
  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = 
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  
  vtkSmartPointer<vtkGeometryFilter> geometryFilter = 
    vtkSmartPointer<vtkGeometryFilter>::New();
  geometryFilter->SetInputData(unstructuredGrid);
  geometryFilter->Update(); 
 
  vtkPolyData* polydata = geometryFilter->GetOutput();

  std::cout << "Output has " << polydata->GetNumberOfPoints() << " points." << std::endl;

  return EXIT_SUCCESS;
}
