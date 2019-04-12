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
  pKMeansStatistics->SetInputData( vtkStatisticsAlgorithm::INPUT_DATA, inputData );
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

  vtkMultiBlockDataSet* outputMetaDS = dynamic_cast<vtkMultiBlockDataSet*>( pKMeansStatistics->GetOutputDataObject( vtkStatisticsAlgorithm::OUTPUT_MODEL ) );
  vtkSmartPointer<vtkTable> outputMeta = dynamic_cast<vtkTable*>( outputMetaDS->GetBlock( 0 ) );
  //vtkSmartPointer<vtkTable> outputMeta = dynamic_cast<vtkTable*>( outputMetaDS->GetBlock( 1 ) );
  vtkDoubleArray* coord0 = dynamic_cast<vtkDoubleArray*>(outputMeta->GetColumnByName("coord 0"));
  vtkDoubleArray* coord1 = dynamic_cast<vtkDoubleArray*>(outputMeta->GetColumnByName("coord 1"));
  vtkDoubleArray* coord2 = dynamic_cast<vtkDoubleArray*>(outputMeta->GetColumnByName("coord 2"));

  for(unsigned int i = 0; i < coord0->GetNumberOfTuples(); ++i)
  {
    std::cout << coord0->GetValue(i) << " " << coord1->GetValue(i) << " " << coord2->GetValue(i) << std::endl;
  }
  return EXIT_SUCCESS;
}
