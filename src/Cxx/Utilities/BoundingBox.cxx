#include <vtkBoundingBox.h>

int main(int, char *[])
{
  double p0[3] = {0,0,0};
  double p1[3] = {0.5,0.5,0.5};
  double p2[3] = {1.0,1.0,1.0};

  vtkBoundingBox boundingBox;

  boundingBox.AddPoint(p0);

  double bounds[6];

  boundingBox.GetBounds(bounds);
  std::cout << "Bounds: " << bounds[0] << ", " << bounds[1] << ", " << bounds[2] << ", "
            << bounds[3] << ", " << bounds[4] << ", " << bounds[5] << std::endl;

  // After adding this point, the box gets bigger
  boundingBox.AddPoint(p2);

  boundingBox.GetBounds(bounds);
  std::cout << "Bounds: " << bounds[0] << ", " << bounds[1] << ", " << bounds[2] << ", "
            << bounds[3] << ", " << bounds[4] << ", " << bounds[5] << std::endl;

  // After adding this point, the box size does not change as the point is already inside the box
  boundingBox.AddPoint(p1);

  boundingBox.GetBounds(bounds);
  std::cout << "Bounds: " << bounds[0] << ", " << bounds[1] << ", " << bounds[2] << ", "
            << bounds[3] << ", " << bounds[4] << ", " << bounds[5] << std::endl;

  return EXIT_SUCCESS;
}
