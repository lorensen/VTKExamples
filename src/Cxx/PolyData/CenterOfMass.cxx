#include <vtkCenterOfMass.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <limits>
#include <cmath>

int main(int, char*[])
{
  // Create a point set of a square
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(0,1,0);
  points->InsertNextPoint(1,1,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Compute the center of mass
  vtkSmartPointer<vtkCenterOfMass> centerOfMassFilter =
    vtkSmartPointer<vtkCenterOfMass>::New();
  centerOfMassFilter->SetInputData(polydata);
  centerOfMassFilter->SetUseScalarsAsWeights(false);
  centerOfMassFilter->Update();

  double center[3];
  centerOfMassFilter->GetCenter(center);

  std::cout << "Center of mass is " << center[0] << " " << center[1] << " " << center[2] << std::endl;

  return EXIT_SUCCESS;
}
