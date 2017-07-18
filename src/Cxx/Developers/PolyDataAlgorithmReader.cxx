#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

#include <vtkTestReader.h>

int main (int, char *[])
{
  vtkSmartPointer<vtkTestReader> reader =
    vtkSmartPointer<vtkTestReader>::New();
  reader->Update();
  
  vtkPolyData* polydata = reader->GetOutput();
  polydata->Print(std::cout);

  return EXIT_SUCCESS;
}
