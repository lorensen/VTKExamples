#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkVersion.h>

#if VTK_VERSION_NUMBER >= 90000000000ULL
#define VTK_VER_GE_90 1
#endif

int main(int, char*[])
{
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1, 1, 1);
  points->InsertNextPoint(2, 2, 2);
  points->InsertNextPoint(3, 3, 3);

  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  vtkSmartPointer<vtkFloatArray> floatArray =
      vtkSmartPointer<vtkFloatArray>::New();
  floatArray->SetNumberOfValues(3);
  floatArray->SetNumberOfComponents(1);
  floatArray->SetName("FloatArray");
  for (vtkIdType i = 0; i < 3; i++)
  {
    floatArray->SetValue(i, 2);
  }
  polydata->GetPointData()->AddArray(floatArray);

  vtkSmartPointer<vtkIntArray> intArray = vtkSmartPointer<vtkIntArray>::New();
  intArray->SetNumberOfValues(3);
  intArray->SetNumberOfComponents(1);
  intArray->SetName("IntArray");
  for (vtkIdType i = 0; i < 3; i++)
  {
    intArray->SetValue(i, 2);
  }

  polydata->GetPointData()->AddArray(intArray);

  for (vtkIdType i = 0; i < 3; i++)
  {
    double p[3];
    polydata->GetPoint(i, p);
    vtkFloatArray* pointsFloatArray = dynamic_cast<vtkFloatArray*>(
        polydata->GetPointData()->GetArray("FloatArray"));
    vtkIntArray* pointsIntArray = dynamic_cast<vtkIntArray*>(
        polydata->GetPointData()->GetArray("IntArray"));
    std::cout << "Point " << i << " : " << p[0] << " " << p[1] << " " << p[2]
              << " " << pointsFloatArray->GetValue(i) << " "
              << pointsIntArray->GetValue(i) << std::endl;
  }

#if VTK_VER_GE_90
  polydata->GetPointData()->NullData(1);
#else
  polydata->GetPointData()->NullPoint(1);
#endif
  polydata->Modified();

  for (vtkIdType i = 0; i < 3; i++)
  {
    double p[3];
    polydata->GetPoint(i, p);
    vtkFloatArray* pointsFloatArray = dynamic_cast<vtkFloatArray*>(
        polydata->GetPointData()->GetArray("FloatArray"));
    vtkIntArray* pointsIntArray = dynamic_cast<vtkIntArray*>(
        polydata->GetPointData()->GetArray("IntArray"));
    std::cout << "Point " << i << " : " << p[0] << " " << p[1] << " " << p[2]
              << " " << pointsFloatArray->GetValue(i) << " "
              << pointsIntArray->GetValue(i) << std::endl;
  }

  return EXIT_SUCCESS;
}
