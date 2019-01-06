#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkIdList.h>
#include <vtkKdTree.h>
#include <vtkDataSetCollection.h>
#include <vtkVertexGlyphFilter.h>
 
int main(int, char *[])
{
  //Setup point coordinates
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 1.0, 0.0};
  double z[3] = {0.0, 0.0, 1.0};
 
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint (x);
  points->InsertNextPoint (y);
  points->InsertNextPoint (z);
  
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  //the tree needs cells, so add vertices to each point
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = 
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  vertexFilter->SetInputData(polydata);
  vertexFilter->Update();
  
  //Create the tree
  vtkSmartPointer<vtkKdTree> kDTree = 
    vtkSmartPointer<vtkKdTree>::New();
  kDTree->AddDataSet(vertexFilter->GetOutput());
  kDTree->BuildLocator();
 
  //get the number of points in the tree like this
  kDTree->GetDataSets()->InitTraversal();
  std::cout << "Number of points in tree: " << kDTree->GetDataSets()->GetNextDataSet()->GetNumberOfPoints() << std::endl;
 
  //or you can get the number of points in the tree like this
  std::cout << "Number of points in tree: " << kDTree->GetDataSet(0)->GetNumberOfPoints() << std::endl;
 
  //get the 0th point in the tree
  double p[3];
  kDTree->GetDataSet(0)->GetPoint(0,p);
  std::cout << "p: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
 
  return EXIT_SUCCESS;
}
