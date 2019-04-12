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
#include <vtkSmartPointer.h>
#include <vtkStdString.h>
#include <vtkNamedColors.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>

int main( int argc, char *argv[] )
{
  // Handle the arguments
  if( argc < 2 )
  {
    std::cout << "Required arguments: filename [optional ignore zero:] <y/n>" << std::endl;
    return EXIT_FAILURE;
  }
  int ignoreZero = 0;
  if( argc == 3 )
  {
    vtkStdString ignore = argv[2];
    std::cout << ignore << std::endl;
    if( ignore == "y" || ignore == "Y" )
    {
      ignoreZero = 1;
    }
  }

  // Read an image
  vtkSmartPointer<vtkImageReader2Factory> readerFactory =
    vtkSmartPointer<vtkImageReader2Factory>::New();
  vtkSmartPointer<vtkImageReader2> reader;
  reader.TakeReference(
    readerFactory->CreateImageReader2(argv[1]));
  reader->SetFileName(argv[1]);
  reader->Update();

  int numComponents = reader->GetOutput()->GetNumberOfScalarComponents();
  std::cout << "Number of components: " << numComponents << std::endl;
  if( numComponents > 3 )
  {
    std::cout << "Error: cannot process an image with " << numComponents << " components!" << std::endl;
    return EXIT_FAILURE;
  }

  double colors[3][3] = {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 } };

  //const char* labels[3] = {
  //  "Red", "Green", "Blue" };

  vtkSmartPointer<vtkIntArray> redFrequencies =
    vtkSmartPointer<vtkIntArray>::New();
  vtkSmartPointer<vtkIntArray> greenFrequencies =
    vtkSmartPointer<vtkIntArray>::New();
  vtkSmartPointer<vtkIntArray> blueFrequencies =
    vtkSmartPointer<vtkIntArray>::New();

  // Process the image, extracting and barChartting a histogram for each component
  for( int i = 0; i < numComponents; ++i )
  {
    vtkSmartPointer<vtkImageExtractComponents> extract =
    vtkSmartPointer<vtkImageExtractComponents>::New();
    extract->SetInputConnection( reader->GetOutputPort() );
    extract->SetComponents( i );
    extract->Update();

    vtkSmartPointer<vtkImageAccumulate> histogram =
    vtkSmartPointer<vtkImageAccumulate>::New();
    histogram->SetInputConnection( extract->GetOutputPort() );
    histogram->SetComponentExtent( 1,55,0,0,0,0 );
    histogram->SetComponentOrigin( 0,0,0 );
    histogram->SetComponentSpacing( 1,0,0 );
    histogram->SetIgnoreZero( ignoreZero );
    histogram->Update();

    vtkIntArray* currentArray = 0;
    if( i == 0 )
    {
      currentArray = redFrequencies;
    }
    else if( i == 1 )
    {
      currentArray = greenFrequencies;
    }
    else
    {
      currentArray = blueFrequencies;
    }

    currentArray->SetNumberOfComponents(1);
    currentArray->SetNumberOfTuples( 54 );

    vtkIdType* output = static_cast<vtkIdType*>(histogram->GetOutput()->GetScalarPointer());

    for( int j = 0; j < 54; ++j )
    {
      currentArray->SetTuple1( j, *output++ );
    }
  }

  vtkSmartPointer<vtkDataObject> dataObject =
    vtkSmartPointer<vtkDataObject>::New();

  if( numComponents == 1 )
  {
    dataObject->GetFieldData()->AddArray( redFrequencies );
  }
  else
  {
    vtkIntArray* rgb[3] = {0,0,0};
    vtkSmartPointer<vtkIntArray> allFrequencies = vtkSmartPointer<vtkIntArray>::New();
    allFrequencies->SetNumberOfComponents(1);
    if( numComponents == 2 )
    {
      rgb[0] = redFrequencies;
      rgb[1] = greenFrequencies;
    }
    else
    {
      rgb[0] = redFrequencies;
      rgb[1] = greenFrequencies;
      rgb[2] = blueFrequencies;
    }
    for( int i = 0; i < 54; ++i )
    {
      for( int j = 0; j < numComponents; ++j )
      {
        allFrequencies->InsertNextTuple1( rgb[j]->GetTuple1( i ) );
      }
    }

    dataObject->GetFieldData()->AddArray( allFrequencies );
  }

  // Create a vtkBarChartActor
  vtkSmartPointer<vtkBarChartActor> barChart =
    vtkSmartPointer<vtkBarChartActor>::New();

  // BUG 1: if input is not set first, the x-axis of the bar chart will be too long
  //
  barChart->SetInput( dataObject );
  barChart->SetTitle( "Histogram" );
  barChart->GetPositionCoordinate()->SetValue(0.05,0.05,0.0);
  barChart->GetPosition2Coordinate()->SetValue(0.95,0.85,0.0);
  barChart->GetProperty()->SetColor(1,1,1);

  // BUG 2: if the number of entries is not set to the number of data array tuples, the bar chart actor will crash.
  // The crash occurs whether the legend and or labels are visible or not.

  barChart->GetLegendActor()->SetNumberOfEntries( dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples() );
  barChart->LegendVisibilityOff();
  barChart->LabelVisibilityOff();

  // BUG 3: the y-axis labels do not accurately reflect the range of data

  int count = 0;
  for( int i = 0; i < 54; ++i )
  {
    for( int j = 0; j < numComponents; ++j )
    {
      barChart->SetBarColor( count++, colors[j] );
    }
  }

  // Visualize the histogram(s)
  vtkSmartPointer<vtkNamedColors> namedColors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor( barChart );
  renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( renderWindow );

  renderWindow->Render();
  // Initialize the event loop and then start it
  interactor->Initialize();
  interactor->Start();

  return  EXIT_SUCCESS;
}
