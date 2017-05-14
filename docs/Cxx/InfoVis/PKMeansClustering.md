[VTKExamples](/index/)/[Cxx](/Cxx)/InfoVis/PKMeansClustering

**PKMeansClustering.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkIntArray.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPoints.h>
#include <vtkTable.h>
#include <vtkDoubleArray.h>
#include <vtkPKMeansStatistics.h>

//display
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <sstream>

int main(int, char*[])
{
  //create 2 clusters, one near (0,0,0) and the other near (3,3,3)
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

  points->InsertNextPoint ( 0.0, 0.0, 0.0 );
  points->InsertNextPoint ( 3.0, 3.0, 3.0 );
  points->InsertNextPoint ( 0.1, 0.1, 0.1 );
  points->InsertNextPoint ( 3.1, 3.1, 3.1 );
  points->InsertNextPoint ( 0.2, 0.2, 0.2 );
  points->InsertNextPoint ( 3.2, 3.2, 3.2 );

  // Get the points into the format needed for KMeans
  vtkSmartPointer<vtkTable> inputData = vtkSmartPointer<vtkTable>::New();

  for ( int c = 0; c < 3; ++c )
  {
    std::stringstream colName;
    colName << "coord " << c;
    vtkSmartPointer<vtkDoubleArray> doubleArray = vtkSmartPointer<vtkDoubleArray>::New();
    doubleArray->SetNumberOfComponents(1);
    doubleArray->SetName( colName.str().c_str() );
    doubleArray->SetNumberOfTuples(points->GetNumberOfPoints());

    for ( int r = 0; r < points->GetNumberOfPoints(); ++ r )
    {
      double p[3];
      points->GetPoint(r, p);

      doubleArray->SetValue( r, p[c] );
    }

    inputData->AddColumn( doubleArray );
  }

  vtkSmartPointer<vtkPKMeansStatistics> pKMeansStatistics = vtkSmartPointer<vtkPKMeansStatistics>::New();
  //vtkSmartPointer<vtkKMeansStatistics> pKMeansStatistics = vtkSmartPointer<vtkKMeansStatistics>::New();
  //pks->SetMaxNumIterations( 10 );
#if VTK_MAJOR_VERSION <= 5
  pKMeansStatistics->SetInput( vtkStatisticsAlgorithm::INPUT_DATA, inputData );
#else
  pKMeansStatistics->SetInputData( vtkStatisticsAlgorithm::INPUT_DATA, inputData );
#endif
  pKMeansStatistics->SetColumnStatus( inputData->GetColumnName( 0 ) , 1 );
  pKMeansStatistics->SetColumnStatus( inputData->GetColumnName( 1 ) , 1 );
  pKMeansStatistics->SetColumnStatus( inputData->GetColumnName( 2 ) , 1 );
  pKMeansStatistics->RequestSelectedColumns();
  pKMeansStatistics->SetAssessOption( true );
  pKMeansStatistics->SetDefaultNumberOfClusters( 2 );
  pKMeansStatistics->Update() ;

  // Display the results
  pKMeansStatistics->GetOutput()->Dump();

  vtkSmartPointer<vtkIntArray> clusterArray = vtkSmartPointer<vtkIntArray>::New();
  clusterArray->SetNumberOfComponents(1);
  clusterArray->SetName( "ClusterId" );

  for(unsigned int r = 0; r < pKMeansStatistics->GetOutput()->GetNumberOfRows(); r++)
  {
    vtkVariant v = pKMeansStatistics->GetOutput()->GetValue(r, pKMeansStatistics->GetOutput()->GetNumberOfColumns() - 1);
    std::cout << "Point " << r << " is in cluster " << v.ToInt() << std::endl;
    clusterArray->InsertNextValue(v.ToInt());
  }

  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->SetScalars(clusterArray);

  // Output the cluster centers

  vtkMultiBlockDataSet* outputMetaDS = vtkMultiBlockDataSet::SafeDownCast( pKMeansStatistics->GetOutputDataObject( vtkStatisticsAlgorithm::OUTPUT_MODEL ) );
  vtkSmartPointer<vtkTable> outputMeta = vtkTable::SafeDownCast( outputMetaDS->GetBlock( 0 ) );
  //vtkSmartPointer<vtkTable> outputMeta = vtkTable::SafeDownCast( outputMetaDS->GetBlock( 1 ) );
  vtkDoubleArray* coord0 = vtkDoubleArray::SafeDownCast(outputMeta->GetColumnByName("coord 0"));
  vtkDoubleArray* coord1 = vtkDoubleArray::SafeDownCast(outputMeta->GetColumnByName("coord 1"));
  vtkDoubleArray* coord2 = vtkDoubleArray::SafeDownCast(outputMeta->GetColumnByName("coord 2"));

  for(unsigned int i = 0; i < coord0->GetNumberOfTuples(); ++i)
  {
    std::cout << coord0->GetValue(i) << " " << coord1->GetValue(i) << " " << coord2->GetValue(i) << std::endl;
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PKMeansClustering)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PKMeansClustering MACOSX_BUNDLE PKMeansClustering.cxx)
 
target_link_libraries(PKMeansClustering ${VTK_LIBRARIES})
```

**Download and Build PKMeansClustering**

Click [here to download PKMeansClustering](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PKMeansClustering.tar) and its *CMakeLists.txt* file.
Once the *tarball PKMeansClustering.tar* has been downloaded and extracted,
```
cd PKMeansClustering/build 
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
./PKMeansClustering
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

