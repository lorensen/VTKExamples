#include <vtkSmartPointer.h>
#include <vtkLine.h>
#include <vtkPoints.h>

int main(int, char *[])
{
  double lineP0[3] = {0.0, 0.0, 0.0};
  double lineP1[3] = {2.0, 0.0, 0.0};
  
  double p0[3] = {1.0, 0, 0};
  double p1[3] = {1.0, 2.0, 0};
  
  /*
  vtkSmartPointer<vtkLine> line = 
    vtkSmartPointer<vtkLine>::New();
  line->GetPoints()->SetPoint(0, lineP0);
  line->GetPoints()->SetPoint(0, lineP1);
  */
  
  {
  double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1);
  std::cout << "Dist0: " << dist0 << std::endl;
  
  double dist1 = vtkLine::DistanceToLine(p1, lineP0, lineP1);
  std::cout << "Dist1: " << dist1 << std::endl;
  }
  
  {
  double t;
  double closest[3];
  double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1, t, closest);
  std::cout << "Dist0: " << dist0 << " closest point: " << closest[0] << " " << closest[1] << " " << closest[2] << std::endl;
  
  double dist1 = vtkLine::DistanceToLine(p1, lineP0, lineP1, t, closest);
  std::cout << "Dist1: " << dist1 << " closest point: " << closest[0] << " " << closest[1] << " " << closest[2] << std::endl;
  } 
  return EXIT_SUCCESS;
}
