#include <vtkSmartPointer.h>
#include <vtkTesting.h>

int main(int, char *[])
{
  // Locate VTK_DATA_ROOT
  vtkSmartPointer<vtkTesting> testHelper =
    vtkSmartPointer<vtkTesting>::New();
  std::string dataRoot = testHelper->GetDataRoot();

  std::cout << "dataRoot: " << dataRoot << std::endl;

  return EXIT_SUCCESS;
}
