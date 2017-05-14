#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellArray.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkPointSource.h>

int main(int, char *[])
{ 

  vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = 
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  
  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter = 
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  surfaceFilter->SetInput(unstructuredGrid);
#else
  surfaceFilter->SetInputData(unstructuredGrid);
#endif
  surfaceFilter->Update(); 
 
  vtkPolyData* polydata = surfaceFilter->GetOutput();

  std::cout << "Output has " << polydata->GetNumberOfPoints() << " points." << std::endl;  

  return EXIT_SUCCESS;
}
