#include <vtkBox.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  // Define a box
  double bounds[6] = {-1,1,-1,1,-1,1};

  // Define a ray
  double rayOrigin[3] = {-5.0, 0, 0};
  double rayDirection[3] = {1.0, 0, 0};

  double intersection[3];
  double t;

  char hit = vtkBox::IntersectBox(bounds, rayOrigin, rayDirection, intersection, t);

  if(!hit)
  {
    std::cout << "Not hit!" << std::endl;
  }
  else
  {
    // Intersection should be (-1.0, 0, 0)
    std::cout << "Intersection is " << intersection[0] << " " << intersection[1] << " " << intersection[2] << std::endl;
    std::cout << "t is " << t << std::endl;
  }

  return EXIT_SUCCESS;
}
