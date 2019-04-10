#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkAxis.h>
#include <vtkPlotStacked.h>
#include <vtkColor.h>
#include <vtkColorSeries.h>
#include <vtkTable.h>
#include <vtkIntArray.h>
#include <vtkDoubleArray.h>
#include <vtkStringArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkRenderWindowInteractor.h>


// Monthly checkout data
static const char *month_labels[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
static int book[] =       {5675, 5902, 6388, 5990, 5575, 7393, 9878, 8082, 6417, 5946, 5526, 5166};
static int new_popular[] = {701,  687,  736,  696,  750,  814,  923,  860,  786,  735,  680,  741};
static int periodical[] =  {184,  176,  166,  131,  171,  191,  231,  166,  197,  162,  152,  143};
static int audiobook[] =   {903, 1038,  987, 1073, 1144, 1203, 1173, 1196, 1213, 1076,  926,  874};
static int video[] =      {1524, 1565, 1627, 1445, 1179, 1816, 2293, 1811, 1588, 1561, 1542, 1563};

//----------------------------------------------------------------------------
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

  // Create a table with some points in it...
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkStringArray> arrMonthLabel =
    vtkSmartPointer<vtkStringArray>::New();
  arrMonthLabel->SetNumberOfValues(12);

  vtkSmartPointer<vtkDoubleArray> arrXTickPositions =
    vtkSmartPointer<vtkDoubleArray>::New();
  arrXTickPositions->SetNumberOfValues(12);

  vtkSmartPointer<vtkIntArray> arrMonth =
    vtkSmartPointer<vtkIntArray>::New();
  arrMonth->SetName("Month");
  table->AddColumn(arrMonth);

  vtkSmartPointer<vtkIntArray> arrBook =
    vtkSmartPointer<vtkIntArray>::New();
  arrBook->SetName("Books");
  table->AddColumn(arrBook);

  vtkSmartPointer<vtkIntArray> arrNewPopularBook =
    vtkSmartPointer<vtkIntArray>::New();
  arrNewPopularBook->SetName("New / Popular");
  table->AddColumn(arrNewPopularBook);

  vtkSmartPointer<vtkIntArray> arrPeriodical =
    vtkSmartPointer<vtkIntArray>::New();
  arrPeriodical->SetName("Periodical");
  table->AddColumn(arrPeriodical);

  vtkSmartPointer<vtkIntArray> arrAudiobook =
    vtkSmartPointer<vtkIntArray>::New();
  arrAudiobook->SetName("Audiobook");
  table->AddColumn(arrAudiobook);

  vtkSmartPointer<vtkIntArray> arrVideo =
    vtkSmartPointer<vtkIntArray>::New();
  arrVideo->SetName("Video");
  table->AddColumn(arrVideo);

  table->SetNumberOfRows(12);
  for (int i = 0; i < 12; i++)
  {
    arrMonthLabel->SetValue(i,month_labels[i]);
    arrXTickPositions->SetValue(i,i);

    arrBook->SetValue(i,book[i]);
    arrNewPopularBook->SetValue(i,new_popular[i]);
    arrPeriodical->SetValue(i,periodical[i]);
    arrAudiobook->SetValue(i,audiobook[i]);
    arrVideo->SetValue(i,video[i]);
  }

  // Set the Month Labels
  chart->GetAxis(1)->SetCustomTickPositions(arrXTickPositions, arrMonthLabel);
  chart->GetAxis(1)->SetMaximum(11);

  chart->GetAxis(1)->SetRange(0, 11);
  chart->GetAxis(1)->SetBehavior(vtkAxis::FIXED);
  chart->GetAxis(1)->SetTitle("Month");

  chart->SetShowLegend(true);

  chart->GetAxis(0)->SetTitle("Checkouts");

  // Add multiple line plots, setting the colors etc
  vtkPlotStacked *stack = 0;

  // Books
  stack = dynamic_cast<vtkPlotStacked*>(chart->AddPlot(vtkChart::STACKED));
  stack->SetUseIndexForXSeries(true);
  stack->SetInputData(table);
  stack->SetInputArray(1,"Books");
  stack->SetInputArray(2,"New / Popular");
  stack->SetInputArray(3,"Periodical");
  stack->SetInputArray(4,"Audiobook");
  stack->SetInputArray(5,"Video");

  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(vtkColorSeries::WILD_FLOWER);
  stack->SetColorSeries(colorSeries);

  // Finally render the scene and compare the image to a reference image
  view->GetRenderWindow()->SetMultiSamples(0);

  view->GetRenderWindow()->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
