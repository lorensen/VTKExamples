[VTKExamples](/index/)/[Cxx](/Cxx)/WishList/Images/HistogramBarChart

### Description
This example works, but the testing images produced usually vary slightly from the baseline.

**HistogramBarChart.cxx**
```c++
#include <vtkActor.h>
#include <vtkBarChartActor.h>
#include <vtkFieldData.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkImageExtractComponents.h>
#include <vtkIntArray.h>
#include <vtkJPEGReader.h>
#include <vtkLegendBoxActor.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkStdString.h>

int main( int argc, char *argv[] )
{
  // Handle the arguments
  if( argc < 2 )
  {
    std::cout << "Required arguments: filename.jpg, [optional ignore zero:] <y/n>" << std::endl;
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

  // Read a jpeg image
  vtkSmartPointer<vtkJPEGReader> reader =
    vtkSmartPointer<vtkJPEGReader>::New();
  if( !reader->CanReadFile( argv[1] ) )
  {
    std::cout << "Error: cannot read " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }
  reader->SetFileName( argv[1] );
  reader->Update();

  int numComponents = reader->GetOutput()->GetNumberOfScalarComponents();
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
    histogram->SetComponentExtent( 0,255,0,0,0,0 );
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
    currentArray->SetNumberOfTuples( 256 );
    int* output = static_cast<int*>(histogram->GetOutput()->GetScalarPointer());

    for( int j = 0; j < 256; ++j )
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
    for( int i = 0; i < 256; ++i )
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
  for( int i = 0; i < 256; ++i )
  {
    for( int j = 0; j < numComponents; ++j )
    {
      barChart->SetBarColor( count++, colors[j] );
    }
  }

  // Visualize the histogram(s)
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor( barChart );

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  renderWindow->SetSize(640, 480);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( renderWindow );

  // Initialize the event loop and then start it
  interactor->Initialize();
  interactor->Start();

  return  EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(HistogramBarChart)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(HistogramBarChart MACOSX_BUNDLE HistogramBarChart.cxx)
 
target_link_libraries(HistogramBarChart ${VTK_LIBRARIES})
```

**Download and Build HistogramBarChart**

Click [here to download HistogramBarChart](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/HistogramBarChart.tar) and its *CMakeLists.txt* file.
Once the *tarball HistogramBarChart.tar* has been downloaded and extracted,
```
cd HistogramBarChart/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./HistogramBarChart
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

