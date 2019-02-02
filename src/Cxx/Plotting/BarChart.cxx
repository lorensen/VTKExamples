#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkAxis.h>
#include <vtkTable.h>
#include <vtkTextProperty.h>
#include <vtkIntArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkColorSeries.h>
#include <vtkNamedColors.h>
#include <vtkColor.h>

// Monthly circulation data
static int data_2008[] = {10822, 10941, 9979, 10370, 9460, 11228, 15093, 12231, 10160, 9816, 9384, 7892};
static int data_2009[] = {9058, 9474, 9979, 9408, 8900, 11569, 14688, 12231, 10294, 9585, 8957, 8590};
static int data_2010[] = {9058, 10941, 9979, 10270, 8900, 11228, 14688, 12231, 10160, 9585, 9384, 8590};

int main(int, char*[] )
{
  // Colors
  vtkNew<vtkColorSeries> colorSeries;
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_SEQUENTIAL_YELLOW_ORANGE_BROWN_3);
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_SPECTRAL_3);
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_BROWN_BLUE_GREEN_3);
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_SEQUENTIAL_BLUE_GREEN_3);
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_SEQUENTIAL_BLUE_PURPLE_3);
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_DIVERGING_PURPLE_ORANGE_3);

  vtkNew<vtkNamedColors> colors;
  vtkColor3d backgroundColor = colors->GetColor3d("Sienna");
  vtkColor3d axisColor = colors->GetColor3d("Wheat");
  vtkColor3d titleColor = colors->GetColor3d("Wheat");

  // Set up a 2D scene, add an XY chart to it
  vtkNew<vtkContextView>  view;
  view->GetRenderer()->SetBackground(backgroundColor.GetData());
  view->GetRenderWindow()->SetSize(640, 480);
  vtkNew<vtkChartXY>  chart;
  view->GetScene()->AddItem(chart);

  // Set various properties
  vtkAxis *xAxis = chart->GetAxis(vtkAxis::BOTTOM);
  xAxis->SetTitle("Monthly");
  xAxis->GetTitleProperties()->SetColor(axisColor.GetData());
  xAxis->GetTitleProperties()->SetFontSize(16);
  xAxis->GetTitleProperties()->ItalicOn();
  xAxis->GetLabelProperties()->SetColor(axisColor.GetData());

  vtkAxis *yAxis = chart->GetAxis(vtkAxis::LEFT);
  yAxis->SetTitle("Circulation");
  yAxis->GetTitleProperties()->SetColor(axisColor.GetData());
  yAxis->GetTitleProperties()->SetFontSize(16);
  yAxis->GetTitleProperties()->ItalicOn();
  yAxis->GetLabelProperties()->SetColor(axisColor.GetData());

  chart->SetTitle("Circulation 2008, 2009, 2010");
  chart->GetTitleProperties()->SetFontSize(24);
  chart->GetTitleProperties()->SetColor(titleColor.GetData());
  chart->GetTitleProperties()->BoldOn();

  // Create a table with some points in it...
  vtkNew<vtkTable>  table;

  vtkNew<vtkIntArray>  arrMonth;
  arrMonth->SetName("Month");
  table->AddColumn(arrMonth);

  vtkNew<vtkIntArray>  arr2008;
  arr2008->SetName("2008");
  table->AddColumn(arr2008);

  vtkNew<vtkIntArray>  arr2009;
  arr2009->SetName("2009");
  table->AddColumn(arr2009);

  vtkNew<vtkIntArray>  arr2010;
  arr2010->SetName("2010");
  table->AddColumn(arr2010);
  
  table->SetNumberOfRows(12);
  for (int i = 0; i < 12; i++)
  {
    table->SetValue(i,0,i+1);
    table->SetValue(i,1,data_2008[i]);
    table->SetValue(i,2,data_2009[i]);
    table->SetValue(i,3,data_2010[i]);
  }

  // Add multiple line plots, setting the colors etc
  vtkPlot *line = 0;
  line = chart->AddPlot(vtkChart::BAR);
  line->SetColor(colorSeries->GetColor(0).GetRed()/255.0,
                 colorSeries->GetColor(0).GetGreen()/255.0,
                 colorSeries->GetColor(0).GetBlue()/255.0);
  line->SetInputData(table, 0, 1);
  
  line = chart->AddPlot(vtkChart::BAR);
  line->SetColor(colorSeries->GetColor(1).GetRed()/255.0,
                 colorSeries->GetColor(1).GetGreen()/255.0,
                 colorSeries->GetColor(1).GetBlue()/255.0);
  line->SetInputData(table, 0, 2);

  line = chart->AddPlot(vtkChart::BAR);
  line->SetColor(colorSeries->GetColor(2).GetRed()/255.0,
                 colorSeries->GetColor(2).GetGreen()/255.0,
                 colorSeries->GetColor(2).GetBlue()/255.0);
  line->SetInputData(table, 0, 3);

  //Finally render the scene and compare the image to a reference image
  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetRenderWindow()->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
