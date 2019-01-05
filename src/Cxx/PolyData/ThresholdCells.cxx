#include <vtkIntArray.h>
#include <vtkCellData.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkThreshold.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New(); 
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,1);
  points->InsertNextPoint(2,2,2);
  points->InsertNextPoint(3,3,3);
  points->InsertNextPoint(4,4,4);

  // Create three triangles
  vtkSmartPointer<vtkTriangle> triangle0 = 
    vtkSmartPointer<vtkTriangle>::New();
  triangle0->GetPointIds()->SetId ( 0, 0 );
  triangle0->GetPointIds()->SetId ( 1, 1 );
  triangle0->GetPointIds()->SetId ( 2, 2 );
  
  vtkSmartPointer<vtkTriangle> triangle1 = 
    vtkSmartPointer<vtkTriangle>::New();
  triangle1->GetPointIds()->SetId ( 0, 1 );
  triangle1->GetPointIds()->SetId ( 1, 2 );
  triangle1->GetPointIds()->SetId ( 2, 3 );
  
  vtkSmartPointer<vtkTriangle> triangle2 = 
    vtkSmartPointer<vtkTriangle>::New();
  triangle2->GetPointIds()->SetId ( 0, 2 );
  triangle2->GetPointIds()->SetId ( 1, 3 );
  triangle2->GetPointIds()->SetId ( 2, 4 );

  // Add the triangles to a cell array
  vtkSmartPointer<vtkCellArray> triangles = 
    vtkSmartPointer<vtkCellArray>::New();
  triangles->InsertNextCell ( triangle0 );
  triangles->InsertNextCell ( triangle1 );
  triangles->InsertNextCell ( triangle2 );
  
  // Setup index array
  vtkSmartPointer<vtkIntArray> index = 
    vtkSmartPointer<vtkIntArray>::New();
  index->SetNumberOfComponents(1);
  index->SetName("index");
  index->InsertNextValue(0);
  index->InsertNextValue(1);
  index->InsertNextValue(2);
  
  // Add points, cells and index array to a polydata
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetPolys(triangles);
  polydata->GetCellData()->AddArray(index);
  
  std::cout << "There are " << polydata->GetNumberOfCells() 
            << " cells before thresholding." << std::endl;
  
  vtkSmartPointer<vtkThreshold> threshold = 
    vtkSmartPointer<vtkThreshold>::New();
  threshold->SetInputData(polydata);
  threshold->ThresholdByLower(1);
  // doesn't work because the array is not added as SCALARS, i.e. via SetScalars
  // threshold->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, vtkDataSetAttributes::SCALARS);
  // use like this:
  threshold->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, "index");
  threshold->Update();
  
  vtkUnstructuredGrid* thresholdedPolydata = threshold->GetOutput();
  std::cout << "There are " << thresholdedPolydata->GetNumberOfCells() 
            << " cells after thresholding." << std::endl;
  
  return EXIT_SUCCESS;
}
