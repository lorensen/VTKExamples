#!/usr/bin/env python
import vtk
def main():
    colors = vtk.vtkNamedColors()
    geoGraticle = vtk.vtkGeoGraticule()
    transformProjection = vtk.vtkGeoTransform()
    destinationProjection = vtk.vtkGeoProjection()
    sourceProjection = vtk.vtkGeoProjection()
    transformGraticle = vtk.vtkTransformFilter()
    
	  reader = vtk.vtkXMLPolyDataReader()
    transformReader = vtk.vtkTransformFilter()
    graticleMapper = vtk.vtkPolyDataMapper()
    readerMapper = vtk.vtkPolyDataMapper()
    graticleActor = vtk.vtkActor()
    readerActor = vtk.vtkActor()

    geoGraticle.SetGeometryType( geoGraticle.POLYLINES )
    geoGraticle.SetLatitudeLevel( 2 )
    geoGraticle.SetLongitudeLevel( 2 )
    geoGraticle.SetLongitudeBounds( -180, 180 )
    geoGraticle.SetLatitudeBounds( -90, 90 )
    
    # destinationProjection defaults to latlong.
    destinationProjection.SetName( "rouss" )
    destinationProjection.SetCentralMeridian( 0. )
    transformProjection.SetSourceProjection( sourceProjection )
    transformProjection.SetDestinationProjection( destinationProjection )
    transformGraticle.SetInputConnection( geoGraticle.GetOutputPort() )
    transformGraticle.SetTransform( transformProjection )
    graticleMapper.SetInputConnection( transformGraticle.GetOutputPort() )
    graticleActor.SetMapper( graticleMapper )
  
    renderWindow = vtk.vtkRenderWindow()
    renderer = vtk.vtkRenderer()
    interactor = vtk.vtkRenderWindowInteractor()
    renderWindow.SetInteractor( interactor )
    renderWindow.AddRenderer( renderer )
    renderWindow.SetSize(640, 480)
    renderer.SetBackground(colors.GetColor3d("BurlyWood"))
    
    renderer.AddActor( readerActor )
    renderer.AddActor( graticleActor )
    
    renderWindow.Render()  	
    interactor.Initialize()
    interactor.Start()

if __name__ == '__main__':
    main()
