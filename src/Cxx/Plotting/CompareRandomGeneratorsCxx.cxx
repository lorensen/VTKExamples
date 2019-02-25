#include <vtkSmartPointer.h>

#include <vtkBarChartActor.h>

#include <vtkMath.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkFieldData.h>
#include <vtkIntArray.h>
#include <vtkLegendBoxActor.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkDataObject.h>

#include <map>
#include <random>
#include <valarray>
#include <array>
#include <algorithm>

namespace
{
vtkSmartPointer<vtkIntArray> CreateUniformDistribution(int);
vtkSmartPointer<vtkIntArray> CreateNormalDistribution(int);
vtkSmartPointer<vtkIntArray> CreateWeibullDistribution(int);
vtkSmartPointer<vtkIntArray> CreateGammaDistribution(int);
vtkSmartPointer<vtkIntArray> CreateCauchyDistribution(int, double, double);
vtkSmartPointer<vtkIntArray> CreateExtremeValueDistribution(int, double, double);
}
int main( int, char *[] )
{

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();

  int count = 100000;
  std::map<std::string, vtkSmartPointer<vtkIntArray> > frequencies;
  frequencies["Uniform Distribution"] = CreateUniformDistribution(count);
  frequencies["Normal Distribution"] = CreateNormalDistribution(count);
  frequencies["Weibull Distribution"] = CreateWeibullDistribution(count);
  frequencies["Gamma Distribution"] = CreateGammaDistribution(count);
  frequencies["Cauchy Distribution"] = CreateCauchyDistribution(count, -2.0, 1.0);
  frequencies["Extreme Value Distribution"] = CreateExtremeValueDistribution(count, .5, 1.0);

  std::vector<vtkSmartPointer<vtkRenderer> > renderers;

  for (auto fit = frequencies.begin(); fit != frequencies.end(); fit++)
  {
    vtkSmartPointer<vtkBarChartActor> chart=
      vtkSmartPointer<vtkBarChartActor>::New();

    vtkSmartPointer<vtkDataObject> dataObject =
      vtkSmartPointer<vtkDataObject>::New();
    dataObject->GetFieldData()->AddArray(fit->second);

    chart->SetInput( dataObject );
    chart->SetTitle( fit->first.c_str());
    chart->GetPositionCoordinate()->SetValue(0.05,0.05,0.0);
    chart->GetPosition2Coordinate()->SetValue(0.95,0.85,0.0);
    chart->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    chart->LegendVisibilityOff();
    chart->LabelVisibilityOff();
    chart->TitleVisibilityOff();
    for( int c = 0; c < count; ++c )
    {
      chart->SetBarColor( c, colors->GetColor3d("Tomato").GetData());
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

    vtkSmartPointer<vtkActor2D> titleActor =
      vtkSmartPointer<vtkActor2D>::New();
    titleActor->SetMapper(titleMapper);
    titleActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    titleActor->GetPositionCoordinate()->SetValue(.5, .85, 0.0);
    titleActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
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
  renderWindow->SetSize(rendererSize*gridCols, rendererSize*gridRows);

  // Set up a grid of viewports for each renderer
  int r = 0;
  for( double row = 0; row < gridRows; row++ )
  {
    for( double col = 0; col < gridCols; col++ )
    {
      double index = row*gridCols + col;

      // Set the renderer's viewport dimensions (xmin, ymin, xmax, ymax) within the render window.
      // Note that for the Y values, we need to subtract the row index from gridRows
      // because the viewport Y axis points upwards, but we want to draw the grid from top to down
      double viewport[4] = {
        static_cast<double>(col) / gridCols,
        static_cast<double>(gridRows - row - 1) / gridRows,
        static_cast<double>(col + 1) / gridCols,
        static_cast<double>(gridRows - row) / gridRows };
      renderers[r]->SetViewport(viewport);
      ++r;
    }
  }

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( renderWindow );

  renderWindow->Render();

  // Initialize the event loop and then start it
  interactor->Initialize();
  interactor->Start();

  return  EXIT_SUCCESS;
}
namespace
{
vtkSmartPointer<vtkIntArray> CreateUniformDistribution(int count)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  rmax = 200.0;
  rmin = -200.0;
  std::uniform_real_distribution<double> distribution(rmin, rmax);

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int) std::ceil(range / 10));

  std::valarray<int> frequencies(0, numberOfBins);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins) * value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
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

vtkSmartPointer<vtkIntArray> CreateNormalDistribution(int count)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::normal_distribution<double> distribution(0.0, 6.0);
  rmax = 36;
  rmin = -36.0;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int) std::ceil(range / 10));

  std::valarray<int> frequencies(0, numberOfBins);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins) * value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
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
vtkSmartPointer<vtkIntArray> CreateWeibullDistribution(int count)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::weibull_distribution<double> distribution(2.0,1.5);
  rmax = 5.0;
  rmin = -5.0;;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int) std::ceil(range / 10));

  std::valarray<int> frequencies(0, numberOfBins);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins) * value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
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
vtkSmartPointer<vtkIntArray> CreateGammaDistribution(int count)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::gamma_distribution<double> distribution(1.0, 2.0);
  rmax = 20.0;
  rmin = 0.0;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int) std::ceil(range / 10));

  std::valarray<int> frequencies(0, numberOfBins);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins) * value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
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

vtkSmartPointer<vtkIntArray> CreateCauchyDistribution(int count, double a, double b)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);
  std::cauchy_distribution<double> distribution(a, b);

  double prev = 0.0;
  for ( double x = -100.0; x < 100.0; x += 1.0)
  {
    double p;
    p =  (1.0 / (vtkMath::Pi() * b));
    p *= std::pow(b, 2.0);
    p /= (std::pow(x - a, 2.0)) + std::pow(b, 2.0);
//    std::cout << "x: " << x << " " << p << std::endl;
    if (p < .01 && prev > p)
    {
      rmin = x;
      break;
    }
    prev = p;
  }

  prev = 0.0;
  for ( double x = 100.0; x > -100.0; x -= 1.0)
  {
    double p;
    p =  (1.0 / (vtkMath::Pi() * b));
    p *= std::pow(b, 2.0);
    p /= (std::pow(x - a, 2.0)) + std::pow(b, 2.0);
//    std::cout << "x: " << x << " " << p << std::endl;
    if (p < .01 && prev > p)
    {
      rmax = x;
      break;
    }
    prev = p;
  }
  std::cout << "rmax: " << rmin << std::endl;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int) std::ceil(range / 10));

  std::valarray<int> frequencies(0, numberOfBins);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins) * value));
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
  frequencies[0] = 0;
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
vtkSmartPointer<vtkIntArray> CreateExtremeValueDistribution(int count, double a, double b)
{
  double rmin, rmax;
  std::mt19937 generator(8775070);

  std::extreme_value_distribution<double> distribution(a, b);

  double prev = 0.0;
  for ( double x = -20.0; x < 20.0; x += 1.0)
  {
    double p;
    double zx = std::exp(a * (-x/b));
    p = (1.0 / b) * zx * std::exp(-zx);
    if (x == -20.0) prev = p;
//    std::cout << "x: " << x << " " << p << " prev: " << prev << std::endl;
    if (p < .01 && prev > p)
    {
      rmin = x;
      break;
    }
    prev = p;
  }
  for ( double x = 200.0; x > -20.0; x -= 1.0)
  {
    double prev;
    double zx = std::exp(a * (-x/b));
    double p = (1.0 / b) * zx * std::exp(-zx);
    if (x == 200.0) prev = 0.0;
//    std::cout << "x: " << x << " " << p << " prev: " << prev << std::endl;
    if (p < .01 && prev < p)
    {
      rmax = x;
      break;
    }
    prev = p;
  }
  rmax = 5.0;
  rmin = -2.0;
  std::cout << "rmin: " << rmin << std::endl;
  std::cout << "rmax: " << rmax << std::endl;

  double range = (rmax - rmin);
  int numberOfBins = std::max(51, (int) std::ceil(range / 10));

  std::valarray<int> frequencies(0, numberOfBins);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = (int)(std::floor((numberOfBins) * value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
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
}
