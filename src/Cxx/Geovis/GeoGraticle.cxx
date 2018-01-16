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

  vtkSmartPointer<vtkGeoGraticule> geoGraticle =
    vtkSmartPointer<vtkGeoGraticule>::New();
  vtkSmartPointer<vtkGeoTransform> transformProjection =
    vtkSmartPointer<vtkGeoTransform>::New();
  vtkSmartPointer<vtkGeoProjection> destinationProjection =
    vtkSmartPointer<vtkGeoProjection>::New();
  vtkSmartPointer<vtkGeoProjection> sourceProjection =
    vtkSmartPointer<vtkGeoProjection>::New();
  vtkSmartPointer<vtkTransformFilter> transformGraticle =
    vtkSmartPointer<vtkTransformFilter>::New();
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  vtkSmartPointer<vtkTransformFilter> transformReader =
    vtkSmartPointer<vtkTransformFilter>::New();
  vtkSmartPointer<vtkPolyDataMapper> graticleMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkPolyDataMapper> readerMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> graticleActor =
    vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkActor> readerActor =
    vtkSmartPointer<vtkActor>::New();

  geoGraticle->SetGeometryType( vtkGeoGraticule::POLYLINES );
  geoGraticle->SetLatitudeLevel( latLevel );
  geoGraticle->SetLongitudeLevel( lngLevel );
  geoGraticle->SetLongitudeBounds( -180, 180 );
  geoGraticle->SetLatitudeBounds( -90, 90 );

  // destinationProjection defaults to latlong.
  destinationProjection->SetName( pname );
  destinationProjection->SetCentralMeridian( 0. );
  transformProjection->SetSourceProjection( sourceProjection );
  transformProjection->SetDestinationProjection( destinationProjection );
  transformGraticle->SetInputConnection( geoGraticle->GetOutputPort() );
  transformGraticle->SetTransform( transformProjection );
  graticleMapper->SetInputConnection( transformGraticle->GetOutputPort() );
  graticleActor->SetMapper( graticleMapper );

  reader->SetFileName(argv[1]);
  transformReader->SetTransform( transformProjection );
  transformReader->SetInputConnection( reader->GetOutputPort() );
  readerMapper->SetInputConnection( transformReader->GetOutputPort() );
  readerActor->SetMapper( readerMapper );

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

  renderer->AddActor( readerActor );
  renderer->AddActor( graticleActor );

  renderWindow->Render();
  
  interactor->Initialize();
  interactor->Start();
  return EXIT_SUCCESS;
};
