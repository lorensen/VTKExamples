#include <vtkSmartPointer.h>
#include <vtkGeoGraticule.h>

#include <vtkActor.h>
#include <vtkGeoProjection.h>
#include <vtkGeoTransform.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransformFilter.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkNamedColors.h>

int main( int argc, char* argv[] )
{
  vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();

  int latLevel = 2;
  int lngLevel = 2;
  const char* pname = "rouss";

  vtkSmartPointer<vtkGeoGraticule> ggr =
    vtkSmartPointer<vtkGeoGraticule>::New();
  vtkSmartPointer<vtkGeoTransform> xfm =
    vtkSmartPointer<vtkGeoTransform>::New();
  vtkSmartPointer<vtkGeoProjection> gcs =
    vtkSmartPointer<vtkGeoProjection>::New();
  vtkSmartPointer<vtkGeoProjection> pcs =
    vtkSmartPointer<vtkGeoProjection>::New();
  vtkSmartPointer<vtkTransformFilter> xff =
    vtkSmartPointer<vtkTransformFilter>::New();
  vtkSmartPointer<vtkXMLPolyDataReader> pdr =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  vtkSmartPointer<vtkTransformFilter> xf2 =
    vtkSmartPointer<vtkTransformFilter>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper2 =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkActor> actor2 =
    vtkSmartPointer<vtkActor>::New();

  ggr->SetGeometryType( vtkGeoGraticule::POLYLINES );
  ggr->SetLatitudeLevel( latLevel );
  ggr->SetLongitudeLevel( lngLevel );
  ggr->SetLongitudeBounds( -180, 180 );
  ggr->SetLatitudeBounds( -90, 90 );

  // gcs defaults to latlong.
  pcs->SetName( pname );
  pcs->SetCentralMeridian( 0. );
  xfm->SetSourceProjection( gcs );
  xfm->SetDestinationProjection( pcs );
  xff->SetInputConnection( ggr->GetOutputPort() );
  xff->SetTransform( xfm );
  mapper->SetInputConnection( xff->GetOutputPort() );
  actor->SetMapper( mapper );

  pdr->SetFileName(argv[1]);

  xf2->SetTransform( xfm );
  xf2->SetInputConnection( pdr->GetOutputPort() );
  mapper2->SetInputConnection( xf2->GetOutputPort() );
  actor2->SetMapper( mapper2 );

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindow->SetInteractor( interactor );
  renderWindow->AddRenderer( renderer );
  renderWindow->SetSize(640, 480);
  renderer->SetBackground(colors->GetColor3d("BurlyWood").GetData());

  renderer->AddActor( actor );
  renderer->AddActor( actor2 );

  renderWindow->Render();
  interactor->Start();
  return EXIT_SUCCESS;
};
