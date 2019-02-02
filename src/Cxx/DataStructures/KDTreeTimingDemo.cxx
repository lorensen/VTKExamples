#include <vtkSmartPointer.h>
#include <vtkAxis.h>
#include <vtkTimerLog.h>
#include <vtkMath.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkIdList.h>
#include <vtkKdTreePointLocator.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkTable.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkSphereSource.h>

#include <vector>
#include <time.h>

static void RandomPointInBounds(vtkPolyData* polydata, double p[3]);
static double TimeKDTree(vtkPolyData* polydata, int maxPoints, int numberOfTrials);

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> reader =
    vtkSmartPointer<vtkSphereSource>::New();
  reader->SetThetaResolution(30);
  reader->SetPhiResolution(30);
  reader->Update();

  std::cout << "Timing octree..." << std::endl;
  std::vector<std::pair<int, double> > results;
  int numberOfTrials = 1000;
  for(int i = 1; i < 20; i++)
  {
    double t = TimeKDTree(reader->GetOutput(), i, numberOfTrials);
    std::pair<int, double> result(i,t);
    results.push_back(result);
  }

  // Create a table with some points in it
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkFloatArray> maxPointsPerRegion =
    vtkSmartPointer<vtkFloatArray>::New();
  maxPointsPerRegion->SetName("MaxPointsPerRegion");
  table->AddColumn(maxPointsPerRegion);

  vtkSmartPointer<vtkFloatArray> runtime =
    vtkSmartPointer<vtkFloatArray>::New();
  runtime->SetName("Run time");
  table->AddColumn(runtime);

  // Fill in the table with some example values
  size_t numPoints = results.size();
  table->SetNumberOfRows(static_cast<vtkIdType>(numPoints));
  for(size_t i = 0; i < numPoints; ++i)
  {
    table->SetValue(static_cast<vtkIdType>(i), 0, results[i].first);
    table->SetValue(static_cast<vtkIdType>(i), 1, results[i].second);
    std::cout << "Put " << results[i].first << " " << results[i].second << " in the table." << std::endl;
  }

  // Set up the view
  vtkSmartPointer<vtkContextView> view =
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);

  // Add multiple line plots, setting the colors etc
  vtkSmartPointer<vtkChartXY> chart =
    vtkSmartPointer<vtkChartXY>::New();
  view->GetScene()->AddItem(chart);
  vtkPlot *line = chart->AddPlot(vtkChart::LINE);
  line->SetInputData(table, 0, 1);
  line->SetColor(0, 255, 0, 255);
  line->SetWidth(3.0);
  line->GetXAxis()->SetTitle("Max Points Per Region");
  line->GetYAxis()->SetTitle("Run time");

  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetRenderWindow()->Render();

  // Start interactor
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}

void RandomPointInBounds(vtkPolyData* polydata, double p[3])
{
  double bounds[6];
  polydata->GetBounds(bounds);

  double x = bounds[0] + (bounds[1] - bounds[0]) * vtkMath::Random(0.0,1.0);
  double y = bounds[2] + (bounds[3] - bounds[2]) * vtkMath::Random(0.0,1.0);
  double z = bounds[4] + (bounds[5] - bounds[4]) * vtkMath::Random(0.0,1.0);

  p[0] = x;
  p[1] = y;
  p[2] = z;
}

double TimeKDTree(vtkPolyData* polydata, int maxLevel, int numberOfTrials)
{
  vtkSmartPointer<vtkTimerLog> timer =
    vtkSmartPointer<vtkTimerLog>::New();
  timer->StartTimer();

  vtkMath::RandomSeed(0); // this should be changed to time(NULL) to get random behavior

  // Create the tree
  vtkSmartPointer<vtkKdTreePointLocator> kdtree =
    vtkSmartPointer<vtkKdTreePointLocator>::New();
  kdtree->SetDataSet(polydata);
  kdtree->AutomaticOff();
  kdtree->SetMaxLevel(maxLevel);
  kdtree->BuildLocator();

//  std::cout << "With maxLevel = " << maxLevel << " there are " << kdtree->GetNumberOfLeafNodes() << " leaf nodes." << std::endl;

  for(int i = 0; i < numberOfTrials; i++)
  {
    double p[3];
    RandomPointInBounds(polydata, p);
    kdtree->FindClosestPoint(p);
  }

  timer->StopTimer();

  std::cout << "KDTree took " << timer->GetElapsedTime() << std::endl;

  return timer->GetElapsedTime();
}
