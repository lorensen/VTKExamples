#include <vtkSmartPointer.h>
#include <vtkPoints.h>

int main(int, char *[])
{
  //create a list of points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  
  //add a point to the list
  const float p[3] = {1.0, 2.0, 3.0};
  points->InsertNextPoint(p);
  
  //retrieve the point
  double* pout = points->GetPoint(0);
  cout << pout[0] << " " << pout[1] << " " << pout[2] << endl;
  
  return EXIT_SUCCESS;
}
