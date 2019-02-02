#include <vtkNew.h>
#include <vtkPlotFunctionalBag.h>
#include <vtkChartXY.h>
#include <vtkChartLegend.h>

#include <vtkNamedColors.h>
#include <vtkColorSeries.h>
#include <vtkColor.h>

#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkDoubleArray.h>
#include <vtkLookupTable.h>
#include <vtkMath.h>
#include <vtkPen.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStringArray.h>
#include <vtkTable.h>

#include <sstream>

//----------------------------------------------------------------------------
int main(int, char * [])
{
  vtkNew<vtkNamedColors> colors;

  // Creates an input table
  const int numCols = 7;
  const int numVals = 100;

  vtkNew<vtkTable> inputTable;

  vtkNew<vtkDoubleArray> arr[numCols];
  for (int i = 0; i < numCols; i++)
  {
    std::stringstream ss;
    ss << "Y" << i;
    arr[i]->SetName(ss.str().c_str());
    arr[i]->SetNumberOfValues(numVals);
    for (int j = 0; j < numVals; j++)
    {
      arr[i]->SetValue(j, (i+1) *
        fabs(sin((j * 2.f *vtkMath::Pi()) /
        static_cast<float>(numVals))) * j + i * 20);
    }
    inputTable->AddColumn(arr[i]);
  }

  // Create a X-axis column
  vtkNew<vtkDoubleArray> xArr;
  xArr->SetName("X");
  xArr->SetNumberOfValues(numVals);
  for (int j = 0; j < numVals; j++)
  {
    xArr->SetValue(j, j * 2.0);
  }
  inputTable->AddColumn(xArr);


  // Create the bag columns
  vtkNew<vtkDoubleArray> q3Arr;
  q3Arr->SetName("Q3");
  q3Arr->SetNumberOfComponents(2);
  q3Arr->SetNumberOfTuples(numVals);
  vtkNew<vtkDoubleArray> q2Arr;
  q2Arr->SetName("Q2");
  q2Arr->SetNumberOfComponents(2);
  q2Arr->SetNumberOfTuples(numVals);

  for (int i = 0; i < numVals; i++)
  {
    double v0, v1;
    v0 = arr[1]->GetVariantValue(i).ToFloat();
    v1 = arr[5]->GetVariantValue(i).ToFloat();
    q3Arr->SetTuple2(i, v0, v1);

    v0 = arr[2]->GetVariantValue(i).ToFloat();
    v1 = arr[4]->GetVariantValue(i).ToFloat();
    q2Arr->SetTuple2(i, v0, v1);
  }

  inputTable->AddColumn(q3Arr);
  inputTable->AddColumn(q2Arr);

  // Set up a 2D scene and add an XY chart to it
  vtkNew<vtkContextView> view;
  view->GetRenderWindow()->SetSize(640, 480);
  view->GetRenderWindow()->SetMultiSamples(0);

  vtkNew<vtkChartXY> chart;
  chart->SetShowLegend(true);
  chart->GetLegend()->SetHorizontalAlignment(vtkChartLegend::LEFT);
  chart->GetLegend()->SetVerticalAlignment(vtkChartLegend::TOP);

  view->GetScene()->AddItem(chart);

  // Create the functional bag plots
  vtkColor3d color3d = colors->GetColor3d("Tomato");
  vtkNew<vtkPlotFunctionalBag> q3Plot;
  q3Plot->SetColor(color3d.GetRed(), color3d.GetGreen(), color3d.GetBlue());
  q3Plot->SetInputData(inputTable, "X", "Q3");
  chart->AddPlot(q3Plot);

  color3d = colors->GetColor3d("Banana");
  vtkNew<vtkPlotFunctionalBag> q2Plot;
  q2Plot->SetColor(color3d.GetRed(), color3d.GetGreen(), color3d.GetBlue());
  q2Plot->SetInputData(inputTable, "X", "Q2");
  chart->AddPlot(q2Plot);

  vtkNew<vtkColorSeries> colorSeries;
  colorSeries->SetColorScheme(vtkColorSeries::BREWER_QUALITATIVE_SET3);;

  vtkNew<vtkLookupTable> lookup;
  lookup->SetNumberOfColors(numCols);
  lookup->SetRange(0, numCols-1);
  for (int j = 0; j < numCols; j++)
  {
    vtkNew<vtkPlotFunctionalBag> plot;
    vtkColor3ub color = colorSeries->GetColorRepeating(j);
    lookup->SetTableValue(
      j,
      color.GetRed()/255., color.GetGreen()/255., color.GetBlue()/255., 1.);
    double rgb[3];
    lookup->GetColor(j, rgb);
    plot->SetColor(rgb[0], rgb[1], rgb[2]);
    plot->SetInputData(inputTable, "X",
                       inputTable->GetColumn(j)->GetName());
    plot->GetPen()->SetWidth(3.0);
    chart->AddPlot(plot);
  }

  view->GetRenderer()->SetBackground(colors->GetColor3d("SlateGray").GetData());

  // Render the scene
  view->GetRenderWindow()->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
