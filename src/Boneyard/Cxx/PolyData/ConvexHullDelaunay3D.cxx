#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDelaunay3D.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkCellArray.h>
#include <vtkDataSetSurfaceFilter.h>

int main(int, char *[])
{ 
  //Create some random points
  
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer< vtkPoints >::New();
  
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(0.1, 0.1, 0.1); //this point will be inside the convex hull
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 1.0);
    
  vtkSmartPointer< vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  //polydata->SetVerts(vertices);
  
  vtkSmartPointer<vtkXMLPolyDataWriter> pointsWriter = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  pointsWriter->SetFileName("points.vtp");
  pointsWriter->SetInput(polydata);
  pointsWriter->Write();
    
  // Create the convex hull of the pointcloud
  vtkSmartPointer<vtkDelaunay3D> delaunay = 
    vtkSmartPointer< vtkDelaunay3D >::New();
  delaunay->SetInput(polydata);
  delaunay->Update();
  
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> ugWriter = 
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  ugWriter->SetInputConnection(delaunay->GetOutputPort());
  ugWriter->SetFileName("delaunay.vtu");
  ugWriter->Write();
  
  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter = 
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(delaunay->GetOutputPort());
  surfaceFilter->Update();  
 
  vtkSmartPointer<vtkXMLPolyDataWriter> outputWriter = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  outputWriter->SetFileName("output.vtp");
  outputWriter->SetInput(surfaceFilter->GetOutput());
  outputWriter->Write();
  
  return EXIT_SUCCESS;
}
