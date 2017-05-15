#include <vtkSmartPointer.h>
#include <vtkIdList.h>
#include <vtkPolyDataMapper.h>
#include <vtkObjectFactory.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkPointLocator.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(400);
  pointSource->Update();

  // Create the tree
  vtkSmartPointer<vtkPointLocator> pointLocator =
    vtkSmartPointer<vtkPointLocator>::New();
  pointLocator->SetDataSet(pointSource->GetOutput());
  pointLocator->AutomaticOn();
  pointLocator->SetNumberOfPointsPerBucket(2);
  pointLocator->BuildLocator();

  double radius = .1;
  double center[3] = {0.0, 0.0, 0.0};
  vtkSmartPointer<vtkIdList> result =
    vtkSmartPointer<vtkIdList>::New();
  pointLocator->FindPointsWithinRadius (radius, center, result);

  for(vtkIdType i = 0; i < result->GetNumberOfIds(); i++)
  {
    unsigned int id = result->GetId(i);
    std::cout << "id of point " << i << " : " << id << std::endl;
  }

  return EXIT_SUCCESS;
}
