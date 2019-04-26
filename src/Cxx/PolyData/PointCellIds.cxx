#include <vtkCellData.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

int main(int, char*[])
{
  auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfPoints()
            << " points." << std::endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfCells()
            << " cells." << std::endl;

  auto idFilter = vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(sphereSource->GetOutputPort());
#if VTK890
  idFilter->SetPointIdsArrayName("ids");
  idFilter->SetCellIdsArrayName("ids");
#else
  idFilter->SetIdsArrayName("ids");
#endif
  idFilter->Update();

  std::cout << "point arrays: " << std::endl;
  for (vtkIdType i = 0;
       i < idFilter->GetOutput()->GetPointData()->GetNumberOfArrays(); i++)
  {
    std::cout << idFilter->GetOutput()->GetPointData()->GetArrayName(i)
              << std::endl;
  }

  std::cout << "cell arrays: " << std::endl;
  for (vtkIdType i = 0;
       i < idFilter->GetOutput()->GetCellData()->GetNumberOfArrays(); i++)
  {
    std::cout << idFilter->GetOutput()->GetCellData()->GetArrayName(i)
              << std::endl;
  }

  vtkIdTypeArray* pointIds = dynamic_cast<vtkIdTypeArray*>(
      idFilter->GetOutput()->GetPointData()->GetArray("ids"));
  std::cout << "There are " << pointIds->GetNumberOfTuples() << " point ids"
            << std::endl;

  vtkIdTypeArray* cellIds = dynamic_cast<vtkIdTypeArray*>(
      idFilter->GetOutput()->GetCellData()->GetArray("ids"));
  std::cout << "There are " << cellIds->GetNumberOfTuples() << " cell ids"
            << std::endl;

  return EXIT_SUCCESS;
}
