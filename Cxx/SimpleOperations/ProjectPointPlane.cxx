#include <vtkSmartPointer.h>
#include <vtkPlane.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPlane> plane = 
      vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);
  
  double p[3] = {23.1, 54.6, 9.2};
  double origin[3] = {0.0, 0.0, 0.0};
  double normal[3] = {0.0, 0.0, 1.0};
  double projected[3];
  
  plane->ProjectPoint(p, origin, normal, projected);
 
  std::cout << "Projected: " << projected[0] << " " 
            << projected[1] << " " << projected[2] << std::endl;
  
  return EXIT_SUCCESS;
}
