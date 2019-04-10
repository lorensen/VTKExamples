#include <vtkSmartPointer.h>

#include <vtkChartXY.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkPlotPoints.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>

int main(int, char*[])
{
  // Set up a 2D scene, add an XY chart to it
  vtkSmartPointer<vtkContextView> view =
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
  view->GetRenderWindow()->SetSize(400, 300);

  vtkSmartPointer<vtkChartXY> chart =
    vtkSmartPointer<vtkChartXY>::New();
  view->GetScene()->AddItem(chart);
  chart->SetShowLegend(true);

  // Create a table with some points in it...
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkFloatArray> arrX =
    vtkSmartPointer<vtkFloatArray>::New();
  arrX->SetName("X Axis");
  table->AddColumn(arrX);

  vtkSmartPointer<vtkFloatArray> arrC =
    vtkSmartPointer<vtkFloatArray>::New();
  arrC->SetName("Cosine");
  table->AddColumn(arrC);

  vtkSmartPointer<vtkFloatArray> arrS =
    vtkSmartPointer<vtkFloatArray>::New();
  arrS->SetName("Sine");
  table->AddColumn(arrS);

  vtkSmartPointer<vtkFloatArray> arrT =
    vtkSmartPointer<vtkFloatArray>::New();
  arrT->SetName("Sine - Cosine");
  table->AddColumn(arrT);

  // Test charting with a few more points...
  int numPoints = 40;
  float inc = 7.5 / (numPoints-1);
  table->SetNumberOfRows(numPoints);
  for (int i = 0; i < numPoints; ++i)
  {
    table->SetValue(i, 0, i * inc);
    table->SetValue(i, 1, cos(i * inc) + 0.0);
    table->SetValue(i, 2, sin(i * inc) + 0.0);
    table->SetValue(i, 3, sin(i * inc) - cos(i * inc));
  }

  // Add multiple scatter plots, setting the colors etc
  vtkPlot *points = chart->AddPlot(vtkChart::POINTS);
  points->SetInputData(table, 0, 1);
  points->SetColor(0, 0, 0, 255);
  points->SetWidth(1.0);
  dynamic_cast<vtkPlotPoints*>(points)->SetMarkerStyle(vtkPlotPoints::CROSS);

  points = chart->AddPlot(vtkChart::POINTS);
  points->SetInputData(table, 0, 2);
  points->SetColor(0, 0, 0, 255);
  points->SetWidth(1.0);
  dynamic_cast<vtkPlotPoints*>(points)->SetMarkerStyle(vtkPlotPoints::PLUS);

  points = chart->AddPlot(vtkChart::POINTS);
  points->SetInputData(table, 0, 3);
  points->SetColor(0, 0, 255, 255);
  points->SetWidth(1.0);
  dynamic_cast<vtkPlotPoints*>(points)->SetMarkerStyle(vtkPlotPoints::CIRCLE);

  //Finally render the scene
  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetRenderWindow()->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
