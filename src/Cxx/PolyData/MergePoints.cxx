#include <vtkSmartPointer.h>

#include <vtkMath.h>
#include <vtkMergePoints.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

int main(int, char *[])
{
  // Create a set of points
  vtkSmartPointer<vtkPointSource> pointsSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointsSource->SetNumberOfPoints(100);
  pointsSource->Update();

  vtkPolyData* points = pointsSource->GetOutput();

  // Get a point point in the set
  double inSet[3];
  points->GetPoint(25, inSet);

  std::cout << "There are "
            << points->GetNumberOfPoints() << " input points." << std::endl;

  vtkIdType id;

  // Insert all of the points
  vtkSmartPointer<vtkMergePoints> mergePoints =
    vtkSmartPointer<vtkMergePoints>::New();
  mergePoints->SetDataSet(points);
  mergePoints->SetDivisions(10,10,10);
  mergePoints->InitPointInsertion(points->GetPoints(), points->GetBounds());

  for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
  {
    mergePoints->InsertUniquePoint(points->GetPoint(i), id);
  }

  // Insert a few of the original points
  std::cout << "Insert some of the original points" << std::endl;
  int inserted;
  for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i+=10)
  {
    points->GetPoint(i, inSet);
    inserted = mergePoints->InsertUniquePoint(inSet, id);
    std::cout << "\tPoint: "
              << inSet[0] << ", "
              << inSet[1] << ", "
              << inSet[2] << " ";

    std::cout << "Inserted? " << ((inserted == 0) ? "No, " : "Yes, ");
    std::cout << "Id:: " << id << std::endl;
  }

  // These points are probably outside the original set of points
  std::cout << "Insert some new points" << std::endl;
  double outsideSet[3];
  for (unsigned int i = 0; i < 10; i++)
  {
    outsideSet[0] = vtkMath::Random(
      -pointsSource->GetRadius(),
      pointsSource->GetRadius());
    outsideSet[1] = vtkMath::Random(
      -pointsSource->GetRadius(),
      pointsSource->GetRadius());
    outsideSet[2] = vtkMath::Random(
      -pointsSource->GetRadius(),
      pointsSource->GetRadius());

    inserted = mergePoints->InsertUniquePoint(outsideSet, id);
    std::cout << "\tPoint: "
              << outsideSet[0] << ", "
              << outsideSet[1] << ", "
              << outsideSet[2] << " ";

    std::cout << "Inserted? " << ((inserted == 0) ? "No, " : "Yes, ");
    std::cout << "Id:: " << id << std::endl;
  }

  std::cout << "There are now "
            << points->GetNumberOfPoints() << " points." << std::endl;

  return EXIT_SUCCESS;
}
