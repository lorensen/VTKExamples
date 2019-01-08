#include <vtkSmartPointer.h>
#include <vtkDecimatePolylineFilter.h>

#include <vtkMath.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

#include <vtkNamedColors.h>

int main(int, char *[])
{
  const unsigned int numberofpoints = 100;

  vtkSmartPointer<vtkPolyData> circle =
    vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
  vtkIdType* lineIndices = new vtkIdType[numberofpoints+1];

  for( unsigned int i = 0; i < numberofpoints; i++ )
  {
    const double angle = 2.0 * vtkMath::Pi() * static_cast< double >( i ) /
      static_cast< double >( numberofpoints );
    points->InsertPoint( static_cast< vtkIdType >( i ),
                         cos( angle ),
                         sin( angle ),
                         0. );
    lineIndices[i] = static_cast< vtkIdType >( i );
  }
  lineIndices[numberofpoints] = 0;
  lines->InsertNextCell( numberofpoints+1, lineIndices );
  delete[] lineIndices;

  circle->SetPoints( points );
  circle->SetLines( lines );

  vtkSmartPointer<vtkPolyDataMapper> c_mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  c_mapper->SetInputData( circle );

  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  vtkSmartPointer<vtkActor> c_actor =
    vtkSmartPointer<vtkActor>::New();
  c_actor->SetMapper( c_mapper );
  c_actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
  c_actor->GetProperty()->SetLineWidth(3);

  vtkSmartPointer<vtkDecimatePolylineFilter> decimate =
    vtkSmartPointer<vtkDecimatePolylineFilter>::New();
  decimate->SetInputData( circle );
  decimate->SetTargetReduction( 0.95 );
  decimate->Update();

  vtkSmartPointer<vtkPolyDataMapper> d_mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  d_mapper->SetInputConnection( decimate->GetOutputPort() );

  vtkSmartPointer<vtkActor> d_actor =
    vtkSmartPointer<vtkActor>::New();
  d_actor->SetMapper( d_mapper );
  d_actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
  d_actor->GetProperty()->SetLineWidth(3);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->AddActor( c_actor );
  ren->AddActor( d_actor );

  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer( ren );

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow( renwin );

  ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
  renwin->SetSize(640, 480);

  renwin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}
