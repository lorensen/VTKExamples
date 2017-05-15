#include <vtkBoundingBox.h>

int main(int, char *[])
{
  vtkBoundingBox boundingBox0;
  boundingBox0.SetBounds(0, 1, 0, 1, 0, 1);
  
  vtkBoundingBox boundingBox1;
  boundingBox1.SetBounds(5, 6, 5, 6, 5, 6);
  
  vtkBoundingBox boundingBox2;
  boundingBox2.SetBounds(0.5, 1.5, 0.5, 1.5, 0.5, 1.5);
  
  std::cout << boundingBox0.IntersectBox(boundingBox1) << std::endl; // Should be 0
  std::cout << boundingBox0.IntersectBox(boundingBox2) << std::endl; // Should be 1
  
  return EXIT_SUCCESS;
}
