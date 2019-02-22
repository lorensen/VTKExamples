#include <vtkBarChartActor.h>

#include <vtkActor.h>
#include <vtkFieldData.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkImageExtractComponents.h>
#include <vtkIntArray.h>
#include <vtkLegendBoxActor.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNew.h>
#include <vtkStdString.h>
#include <vtkNamedColors.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>

#include <random>
#include <valarray>
#include <algorithm>

int main( int, char *[] )
{
  unsigned int count = 1000000;
  std::mt19937 generator(8775070);
  double rmin;
  double rmax;
//  std::uniform_real_distribution<double> distribution(rmin, rmax); rmax = 200.0; rmin = -200.0;
//  std::normal_distribution<double> distribution(0.0, 6.0); rmax = 36; rmin = -36.0;
//  std::weibull_distribution<double> distribution(2.0,1.5); rmax = 5.0; rmin = -5.0;;
//  std::gamma_distribution<double> distribution(1.0, 2.0); rmax = 20.0; rmin = 0.0; std::string title("Gamma Distribution");
//  std::cauchy_distribution<double> distribution(0.0,1.0); rmax = 10.0; rmin = -10.0; std::string title("Cauchy Distribution");
  std::extreme_value_distribution<double> distribution(.5,1.0); rmax = 5.0; rmin = -2.0; std::string title("Extreme Value Distribution");

  std::cout << "rmax: " << rmax << " rmin: " << rmin << std::endl;
  double range = (rmax - rmin);
  unsigned int numberOfBins = std::max(51, (int) std::ceil(range / 10));
  std::cout << "Bins: " << numberOfBins << std::endl;
  vtkNew<vtkIntArray> allFrequencies;
  allFrequencies->SetNumberOfComponents(1);
  allFrequencies->SetNumberOfTuples(numberOfBins);

  std::valarray<int> frequencies(0,numberOfBins);
  for (int i = 0; i < count; ++i)
  {
    double value = (distribution(generator) - rmin) / range;
    int bin = int(std::floor((numberOfBins) * value));
    if (bin > numberOfBins - 1)
    {
      bin = numberOfBins - 1;
    }
    ++frequencies[bin];
  }
  int sum = frequencies.sum();
#if 0
  std::cout << "sum: " << sum << std::endl;
  for (int i = 0; i < numberOfBins; ++i)
  {
    std::cout << "freq[" << i << "]: " << frequencies[i] << std::endl;
  }
#endif
  frequencies[numberOfBins - 1] = 0;
  for (int i = 0; i < numberOfBins; ++i)
  {
    allFrequencies->SetTypedTuple(i, &frequencies[i]);
  }
  vtkNew<vtkDataObject> dataObject;
  dataObject->GetFieldData()->AddArray( allFrequencies );

  // Create a vtkBarChartActor
  vtkNew<vtkNamedColors> namedColors;

  vtkNew<vtkBarChartActor> barChart;
  barChart->SetInput( dataObject );
  barChart->SetTitle( title.c_str());
  barChart->GetPositionCoordinate()->SetValue(0.05,0.05,0.0);
  barChart->GetPosition2Coordinate()->SetValue(0.95,0.85,0.0);
  barChart->GetProperty()->SetColor(namedColors->GetColor3d("Wheat").GetData());

  barChart->GetLegendActor()->SetNumberOfEntries( dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples() );
  barChart->LegendVisibilityOff();
  barChart->LabelVisibilityOff();

  for( int i = 0; i < count; ++i )
  {
    barChart->SetBarColor( i, namedColors->GetColor3d("Tomato").GetData());
  }

  // Visualize the histogram(s)
  vtkNew<vtkRenderer> renderer;
  renderer->AddActor( barChart );
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer( renderer );
  renderWindow->SetSize(640, 480);

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  // Initialize the event loop and then start it
  interactor->Initialize();
  interactor->Start();

  return  EXIT_SUCCESS;
}
