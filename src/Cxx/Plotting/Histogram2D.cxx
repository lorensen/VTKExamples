#include <vtkNew.h>
#include <vtkChartHistogram2D.h>

#include <vtkColor.h>
#include <vtkNamedColors.h>

#include <vtkColorLegend.h>
#include <vtkAxis.h>
#include <vtkBrush.h>
#include <vtkColorTransferFunction.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkDoubleArray.h>
#include <vtkImageData.h>
#include <vtkMath.h>
#include <vtkTextProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTable.h>
#include <vtkVector.h>

//----------------------------------------------------------------------------
int main(int, char * [])
{
  // Define colors
  vtkNew<vtkNamedColors> colors;
  vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");
  vtkColor3d titleColor = colors->GetColor3d("Orange");
  vtkColor3d axisTitleColor = colors->GetColor3d("Orange");
  vtkColor3d axisLabelColor = colors->GetColor3d("Beige");
  vtkColor4ub legendBackgroundColor = colors->GetColor4ub("Tomato");

  // Set up a 2D scene, add an XY chart to it
  int size = 400;
  vtkNew<vtkContextView> view;
  view->GetRenderWindow()->SetSize(512, 512);
  view->GetRenderer()->SetBackground(backgroundColor.GetData());

  // Define a chart
  vtkNew<vtkChartHistogram2D> chart;

  // Chart Title
  chart->SetTitle("2D Histogram");
  chart->GetTitleProperties()
    ->SetFontSize(36);
  chart->GetTitleProperties()
    ->SetColor(titleColor.GetData());

  // Chart Axes
  chart->GetAxis(0)->GetTitleProperties()
    ->SetFontSize(24);
  chart->GetAxis(0)->GetTitleProperties()
    ->SetColor(axisTitleColor.GetData());
  chart->GetAxis(0)->GetLabelProperties()
    ->SetColor(axisLabelColor.GetData());
  chart->GetAxis(0)->GetLabelProperties()
    ->SetFontSize(18);

  chart->GetAxis(1)->GetTitleProperties()
    ->SetFontSize(24);
  chart->GetAxis(1)->GetTitleProperties()
    ->SetColor(colors->GetColor3d("orange").GetData());
  chart->GetAxis(1)->GetLabelProperties()
    ->SetColor(colors->GetColor3d("beige").GetData());
  chart->GetAxis(1)->GetLabelProperties()
    ->SetFontSize(18);

  // Chart Legend
  dynamic_cast<vtkColorLegend*>(chart->GetLegend())->DrawBorderOn();
  chart->GetLegend()->GetBrush()
    ->SetColor(legendBackgroundColor);

  // Add the chart to the view
  view->GetScene()->AddItem(chart);

  vtkNew<vtkImageData> data;
  data->SetExtent(0, size-1, 0, size-1, 0, 0);
  data->AllocateScalars(VTK_DOUBLE, 1);

  data->SetOrigin(100.0, -100.0, 0.0);
  data->SetSpacing(2.0, 1.0, 1.0);

  double *dPtr = static_cast<double *>(data->GetScalarPointer(0, 0, 0));
  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j < size; ++j)
    {
      dPtr[i * size + j] =
        std::sin(vtkMath::RadiansFromDegrees(double(2*i))) *
        std::cos(vtkMath::RadiansFromDegrees(double(j)));
    }
  }
  chart->SetInputData(data);

  vtkNew<vtkColorTransferFunction> transferFunction;
  transferFunction->AddHSVSegment(0.0, 0.0, 1.0, 1.0,
                                  0.3333, 0.3333, 1.0, 1.0);
  transferFunction->AddHSVSegment(0.3333, 0.3333, 1.0, 1.0,
                                  0.6666, 0.6666, 1.0, 1.0);
  transferFunction->AddHSVSegment(0.6666, 0.6666, 1.0, 1.0,
                                  1.0, 0.2, 1.0, 0.3);
  transferFunction->Build();
  chart->SetTransferFunction(transferFunction);

  view->GetRenderWindow()->Render();
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
