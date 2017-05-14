#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

void OutputPoints(vtkSmartPointer<vtkPoints> points);
void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkIdType id);

int main(int, char *[])
{
  // Create a set of points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  points->InsertNextPoint ( 0.0, 1.0, 0.0 );
  points->InsertNextPoint ( 0.0, 0.0, 1.0 );

  std::cout << "Number of points: " << points->GetNumberOfPoints() << std::endl;
  OutputPoints(points);

  ReallyDeletePoint(points, 1);

  std::cout << "Number of points: " << points->GetNumberOfPoints() << std::endl;
  OutputPoints(points);

  return EXIT_SUCCESS;
}

void OutputPoints(vtkSmartPointer<vtkPoints> points)
{
  for(vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
  {
    double p[3];
    points->GetPoint(i,p);
    cout << p[0] << " " << p[1] << " " << p[2] << endl;
  }
}

void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkIdType id)
{
  vtkSmartPointer<vtkPoints> newPoints =
    vtkSmartPointer<vtkPoints>::New();

  for(vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
  {
    if(i != id)
    {
      double p[3];
      points->GetPoint(i,p);
      newPoints->InsertNextPoint(p);
    }
  }

  points->ShallowCopy(newPoints);
}
