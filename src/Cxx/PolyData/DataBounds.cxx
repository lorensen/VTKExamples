#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkPolyData> polyData;

  if (argc > 1)
  {
    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    auto modelSource = vtkSmartPointer<vtkSphereSource>::New();
    modelSource->Update();
    polyData = modelSource->GetOutput();
  }

  double bounds[6];
  polyData->GetBounds(bounds);

  std::cout << "xmin: " << bounds[0] << " "
            << "xmax: " << bounds[1] << std::endl
            << "ymin: " << bounds[2] << " "
            << "ymax: " << bounds[3] << std::endl
            << "zmin: " << bounds[4] << " "
            << "zmax: " << bounds[5] << std::endl;

  return EXIT_SUCCESS;
}
