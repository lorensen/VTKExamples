#include <vtkSmartPointer.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkActor.h>
#include <vtkBarChartActor.h>
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
#include <vtkImageMagnitude.h>

int main( int argc, char *argv[] )
{
  // Handle the arguments
  if( argc < 2 )
  {
    std::cout << "Required arguments: filename.jpg" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader = readerFactory->CreateImageReader2(argv[1]);
  reader->SetFileName(argv[1]);

  vtkSmartPointer<vtkImageMagnitude> magnitude =
    vtkSmartPointer<vtkImageMagnitude>::New();
  magnitude->SetInputConnection(reader->GetOutputPort());
  magnitude->Update();

  double red[3] = {1, 0, 0 };

  vtkSmartPointer<vtkIntArray> frequencies =
    vtkSmartPointer<vtkIntArray>::New();

  vtkSmartPointer<vtkImageAccumulate> histogram =
    vtkSmartPointer<vtkImageAccumulate>::New();
  histogram->SetInputConnection(magnitude->GetOutputPort());
  histogram->SetComponentExtent(0,255,0,0,0,0);
  histogram->SetComponentOrigin(0,0,0);
  histogram->SetComponentSpacing(1,0,0);
  histogram->IgnoreZeroOn();
  histogram->Update();

  frequencies->SetNumberOfComponents(1);
  frequencies->SetNumberOfTuples(256);
  int* output = static_cast<int*>(histogram->GetOutput()->GetScalarPointer());

  for(int j = 0; j < 256; ++j)
  {
    frequencies->SetTuple1(j, *output++);
  }

  vtkSmartPointer<vtkDataObject> dataObject =
    vtkSmartPointer<vtkDataObject>::New();

  dataObject->GetFieldData()->AddArray( frequencies );

  // Create a vtkBarChartActor
  vtkSmartPointer<vtkBarChartActor> barChart =
    vtkSmartPointer<vtkBarChartActor>::New();

  barChart->SetInput(dataObject);
  barChart->SetTitle("Histogram");
  barChart->GetPositionCoordinate()->SetValue(0.05,0.05,0.0);
  barChart->GetPosition2Coordinate()->SetValue(0.95,0.85,0.0);
  barChart->GetProperty()->SetColor(1,1,1);

  barChart->GetLegendActor()->SetNumberOfEntries(dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples());
  barChart->LegendVisibilityOff();
  barChart->LabelVisibilityOff();

  int count = 0;
  for(int i = 0; i < 256; ++i)
  {
    barChart->SetBarColor( count++, red );
  }

  // Visualize the histogram
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(barChart);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Initialize the event loop and then start it
  interactor->Initialize();
  interactor->Start();

  return  EXIT_SUCCESS;
}
