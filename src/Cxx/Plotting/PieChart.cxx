#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartPie.h>
#include <vtkPlot.h>
#include <vtkPlotPie.h>
#include <vtkTable.h>
#include <vtkIntArray.h>
#include <vtkStringArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkColorSeries.h>

int NUM_ITEMS = 5;
static int data[] = {77938,9109,2070,12806,19514};
//static int data[] = {200,200,200,200,200};
static const char *labels[] = {"Books","New and Popular","Periodical","Audiobook","Video"};

int main(int, char*[])
{
  // Set up a 2D scene, add an XY chart to it
  vtkSmartPointer<vtkContextView> view =
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
  view->GetRenderWindow()->SetSize(600, 350);
  vtkSmartPointer<vtkChartPie> chart =
    vtkSmartPointer<vtkChartPie>::New();
  view->GetScene()->AddItem(chart);

  // Create a table with some points in it...
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkIntArray> arrData =
    vtkSmartPointer<vtkIntArray>::New();
  vtkSmartPointer<vtkStringArray> labelArray =
    vtkSmartPointer<vtkStringArray>::New();

  arrData->SetName("2008 Circulation");
  for (int i = 0; i < NUM_ITEMS; i++)
  {
    arrData->InsertNextValue(data[i]);
    labelArray->InsertNextValue(labels[i]);
  }

  table->AddColumn(arrData);

  // Create a color series to use with our stacks.
  vtkSmartPointer<vtkColorSeries> colorSeries =
    vtkSmartPointer<vtkColorSeries>::New();
  colorSeries->SetColorScheme(vtkColorSeries::WARM);

  // Add multiple line plots, setting the colors etc
  vtkPlotPie *pie = dynamic_cast<vtkPlotPie*>(chart->AddPlot(0));
  pie->SetColorSeries(colorSeries);
  pie->SetInputData(table);
  pie->SetInputArray(0,"2008 Circulation");
  pie->SetLabels(labelArray);

  chart->SetShowLegend(true);

  chart->SetTitle("Circulation 2008");

  //Finally render the scene and compare the image to a reference image
  view->GetRenderWindow()->SetMultiSamples(0);
  view->GetRenderWindow()->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
