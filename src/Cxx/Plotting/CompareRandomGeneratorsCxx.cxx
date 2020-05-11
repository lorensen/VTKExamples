#include <vtkBarChartActor.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkDataObject.h>
#include <vtkFieldData.h>
#include <vtkIntArray.h>
#include <vtkLegendBoxActor.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <algorithm>
#include <map>
#include <random>
#include <vector>

namespace {
vtkSmartPointer<vtkIntArray> CreateUniformDistribution(int, double, double);
vtkSmartPointer<vtkIntArray> CreateNormalDistribution(int, double, double);
vtkSmartPointer<vtkIntArray> CreateWeibullDistribution(int, double, double);
vtkSmartPointer<vtkIntArray> CreateGammaDistribution(int, double, double);
vtkSmartPointer<vtkIntArray> CreateCauchyDistribution(int, double, double);
vtkSmartPointer<vtkIntArray> CreateExtremeValueDistribution(int, double,
                                                            double);
} // namespace
int main(int, char*[])
{

  vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();

  int count = 100000;
  std::map<std::string, vtkSmartPointer<vtkIntArray>> frequencies;
  frequencies["Uniform Distribution"] =
      CreateUniformDistribution(count, -200.0, 200.0);
  frequencies["Normal Distribution"] =
      CreateNormalDistribution(count, 0.0, 6.0);
  frequencies["Weibull Distribution"] =
      CreateWeibullDistribution(count, 1.5, 1.0);
  frequencies["Gamma Distribution"] = CreateGammaDistribution(count, 2.0, 2.0);
  frequencies["Cauchy Distribution"] =
      CreateCauchyDistribution(count, -1.0, 2.0);
  frequencies["Extreme Value Distribution"] =
      CreateExtremeValueDistribution(count, .5, 1.0);

  std::vector<vtkSmartPointer<vtkRenderer>> renderers;

  for (auto fit = frequencies.begin(); fit != frequencies.end(); fit++)
  {
    vtkSmartPointer<vtkBarChartActor> chart =
        vtkSmartPointer<vtkBarChartActor>::New();

    vtkSmartPointer<vtkDataObject> dataObject =
        vtkSmartPointer<vtkDataObject>::New();
    dataObject->GetFieldData()->AddArray(fit->second);

    chart->SetInput(dataObject);
    chart->SetTitle(fit->first.c_str());
    chart->GetPositionCoordinate()->SetValue(0.05, 0.05, 0.0);
    chart->GetPosition2Coordinate()->SetValue(0.95, 0.85, 0.0);
    chart->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    chart->LegendVisibilityOff();
    chart->LabelVisibilityOff();
    chart->TitleVisibilityOff();
    for (int c = 0; c < count; ++c)
    {
      chart->SetBarColor(c, colors->GetColor3d("Tomato").GetData());
    }
    // Create a title
    vtkSmartPointer<vtkTextProperty> titleProperty =
        vtkSmartPointer<vtkTextProperty>::New();
    titleProperty->SetFontSize(16);
    titleProperty->SetJustificationToCentered();

    vtkSmartPointer<vtkTextMapper> titleMapper =
        vtkSmartPointer<vtkTextMapper>::New();
    titleMapper->SetInput(fit->first.c_str());
    titleMapper->SetTextProperty(titleProperty);

    vtkSmartPointer<vtkActor2D> titleActor = vtkSmartPointer<vtkActor2D>::New();
    titleActor->SetMapper(titleMapper);
    titleActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedViewport();
    titleActor->GetPositionCoordinate()->SetValue(.5, .85, 0.0);
    titleActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(chart);
    renderer->AddActor(titleActor);
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    renderers.push_back(renderer);
    renderWindow->AddRenderer(renderer);
  }

  // Setup a grid of renderers
  int gridCols = 3;
  int gridRows = 2;

  // Define side length (in pixels) of each renderer square
  int rendererSize = 300;

  renderWindow->SetWindowName("Geometric Objects Demo");
  renderWindow->SetSize(rendererSize * gridCols, rendererSize * gridRows);

  // Set up a grid of viewports for each renderer
  int r = 0;
  for (double row = 0; row < gridRows; row++)
  {
    for (double col = 0; col < gridCols; col++)
    {
      double index = row * gridCols + col;

      // Set the renderer's viewport dimensions (xmin, ymin, xmax, ymax) within
      // the render window. Note that for the Y values, we need to subtract the
      // row index from gridRows because the viewport Y axis points upwards, but
      // we want to draw the grid from top to down
      double viewport[4] = {static_cast<double>(col) / gridCols,
                            static_cast<double>(gridRows - row - 1) / gridRows,
                            static_cast<double>(col + 1) / gridCols,
                            static_cast<double>(gridRows - row) / gridRows};
      renderers[r]->SetViewport(viewport);
      ++r;
    }
  }

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderWindow->Render();

  // Initialize the event loop and then start it
  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}
namespace {
vtkSmartPointer<vtkIntArray> CreateUniformDistribution(int count, double a,
                                                       double b)
{
  std::mt19937 generator(8775070);
  double rmin, rmax;
  rmax = b;
  rmin = a;
  std::uniform_real_distribution<double> distribution(a, b);

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int)std::ceil(range / 10));

  std::vector<int> frequencies(numberOfBins,0);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins)*value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
    }
    else if (bin < 0)
    {
      bin = 0;
    }
    ++frequencies[bin];
  }
  frequencies[numberOfBins - 1] = 0;

  vtkSmartPointer<vtkIntArray> frequenciesArray =
      vtkSmartPointer<vtkIntArray>::New();
  frequenciesArray->SetNumberOfComponents(1);
  frequenciesArray->SetNumberOfTuples(numberOfBins);

  for (int i = 0; i < numberOfBins; ++i)
  {
    frequenciesArray->SetTypedTuple(i, &frequencies[i]);
  }
  frequenciesArray->SetName("frequencies");

  return frequenciesArray;
}

vtkSmartPointer<vtkIntArray> CreateNormalDistribution(int count, double a,
                                                      double b)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::normal_distribution<double> distribution(a, b);
  rmax = 6.0 * b;
  rmin = -6.0 * b;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int)std::ceil(range / 10));

  std::vector<int> frequencies(numberOfBins, 0);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins)*value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
    }
    else if (bin < 0)
    {
      bin = 0;
    }
    ++frequencies[bin];
  }
  frequencies[numberOfBins - 1] = 0;

  vtkSmartPointer<vtkIntArray> frequenciesArray =
      vtkSmartPointer<vtkIntArray>::New();
  frequenciesArray->SetNumberOfComponents(1);
  frequenciesArray->SetNumberOfTuples(numberOfBins);

  for (int i = 0; i < numberOfBins; ++i)
  {
    frequenciesArray->SetTypedTuple(i, &frequencies[i]);
  }
  frequenciesArray->SetName("frequencies");

  return frequenciesArray;
}
vtkSmartPointer<vtkIntArray> CreateWeibullDistribution(int count, double a,
                                                       double b)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::weibull_distribution<double> distribution(a, b);
  rmax = 3.0;
  rmin = 0.0;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int)std::ceil(range / 10));

  std::vector<int> frequencies(numberOfBins, 0);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins)*value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
    }
    else if (bin < 0)
    {
      bin = 0;
    }
    ++frequencies[bin];
  }
  frequencies[numberOfBins - 1] = 0;

  vtkSmartPointer<vtkIntArray> frequenciesArray =
      vtkSmartPointer<vtkIntArray>::New();
  frequenciesArray->SetNumberOfComponents(1);
  frequenciesArray->SetNumberOfTuples(numberOfBins);

  for (int i = 0; i < numberOfBins; ++i)
  {
    frequenciesArray->SetTypedTuple(i, &frequencies[i]);
  }
  frequenciesArray->SetName("frequencies");

  return frequenciesArray;
}
vtkSmartPointer<vtkIntArray> CreateGammaDistribution(int count, double a,
                                                     double b)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::gamma_distribution<double> distribution(a, b);
  rmax = 20.0;
  rmin = 0.0;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int)std::ceil(range / 10));

  std::vector<int> frequencies(numberOfBins, 0);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins)*value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
    }
    else if (bin < 0)
    {
      bin = 0;
    }
    ++frequencies[bin];
  }
  frequencies[numberOfBins - 1] = 0;

  vtkSmartPointer<vtkIntArray> frequenciesArray =
      vtkSmartPointer<vtkIntArray>::New();
  frequenciesArray->SetNumberOfComponents(1);
  frequenciesArray->SetNumberOfTuples(numberOfBins);

  for (int i = 0; i < numberOfBins; ++i)
  {
    frequenciesArray->SetTypedTuple(i, &frequencies[i]);
  }
  frequenciesArray->SetName("frequencies");

  return frequenciesArray;
}

vtkSmartPointer<vtkIntArray> CreateCauchyDistribution(int count, double a,
                                                      double b)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::cauchy_distribution<double> distribution(a, b);

  rmin = -10;
  rmax = 15.0;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int)std::ceil(range / 10));

  std::vector<int> frequencies(numberOfBins, 0);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins)*value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
    }
    else if (bin < 0)
    {
      bin = 0;
    }
    ++frequencies[bin];
  }
  frequencies[0] = frequencies[1];
  frequencies[numberOfBins - 1] = frequencies[numberOfBins - 2];

  vtkSmartPointer<vtkIntArray> frequenciesArray =
      vtkSmartPointer<vtkIntArray>::New();
  frequenciesArray->SetNumberOfComponents(1);
  frequenciesArray->SetNumberOfTuples(numberOfBins);

  for (int i = 0; i < numberOfBins; ++i)
  {
    frequenciesArray->SetTypedTuple(i, &frequencies[i]);
  }
  frequenciesArray->SetName("frequencies");

  return frequenciesArray;
}
vtkSmartPointer<vtkIntArray> CreateExtremeValueDistribution(int count, double a,
                                                            double b)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);

  std::extreme_value_distribution<double> distribution(a, b);
  rmax = 5.0;
  rmin = -2.0;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int)std::ceil(range / 10));

  std::vector<int> frequencies(numberOfBins, 0);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins)*value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
    }
    else if (bin < 0)
    {
      bin = 0;
    }
    ++frequencies[bin];
  }
  frequencies[numberOfBins - 1] = 0;

  vtkSmartPointer<vtkIntArray> frequenciesArray =
      vtkSmartPointer<vtkIntArray>::New();
  frequenciesArray->SetNumberOfComponents(1);
  frequenciesArray->SetNumberOfTuples(numberOfBins);

  for (int i = 0; i < numberOfBins; ++i)
  {
    frequenciesArray->SetTypedTuple(i, &frequencies[i]);
  }
  frequenciesArray->SetName("frequencies");

  return frequenciesArray;
}
} // namespace
