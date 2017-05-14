#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>

int main(int, char *[])
{
  // Create the polygon
  vtkSmartPointer<vtkPolygon> polygon =
    vtkSmartPointer<vtkPolygon>::New();
  polygon->GetPoints()->InsertNextPoint(0.0, 0.0, 0.0);
  polygon->GetPoints()->InsertNextPoint(1.0, 0.0, 0.0);
  polygon->GetPoints()->InsertNextPoint(1.0, 1.0, 0.0);
  polygon->GetPoints()->InsertNextPoint(0.0, 1.0, 0.0);

  double testIn[3] = {0.5, 0.5, 0.0};
  double testOut[3] = {2.0, 0.5, 0.0};

  double n[3];
  polygon->ComputeNormal(polygon->GetPoints()->GetNumberOfPoints(),
          static_cast<double*>(polygon->GetPoints()->GetData()->GetVoidPointer(0)), n);

  double bounds[6];
  polygon->GetPoints()->GetBounds(bounds);

  std::cout << "testIn in polygon? " << polygon->PointInPolygon(testIn,
      polygon->GetPoints()->GetNumberOfPoints(), static_cast<double*>(
      polygon->GetPoints()->GetData()->GetVoidPointer(0)), bounds, n) << std::endl;

  std::cout << "testOut in polygon? " << polygon->PointInPolygon(testOut,
      polygon->GetPoints()->GetNumberOfPoints(), static_cast<double*>(
      polygon->GetPoints()->GetData()->GetVoidPointer(0)), bounds, n) << std::endl;

  /*
  std::cout << "New functions:" << std::endl;

  std::cout << "testIn in polygon? " << polygon->PointInPolygon(testIn) << std::endl;

  std::cout << "testOut in polygon? " << polygon->PointInPolygon(testOut) << std::endl;
  */
  return EXIT_SUCCESS;
}
