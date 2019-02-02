#!/usr/bin/env python
import vtk
    
def main():
    colors = vtk.vtkNamedColors()
    # Create hyper tree grid source
    source = vtk.vtkHyperTreeGridSource()
    source.SetMaximumLevel( 6 )
    source.SetGridSize( 3, 3, 2 )
    source.SetGridScale( 1.5, 1., .7 )
    source.SetDimension( 3 )
    source.SetBranchFactor( 4 )
    source.SetDescriptor( "RRR .R. .RR ..R ..R .R.|R.......................... ........................... ........................... .............R............. ....RR.RR........R......... .....RRRR.....R.RR......... ........................... ........................... ...........................|........................... ........................... ........................... ...RR.RR.......RR.......... ........................... RR......................... ........................... ........................... ........................... ........................... ........................... ........................... ........................... ............RRR............|........................... ........................... .......RR.................. ........................... ........................... ........................... ........................... ........................... ........................... ........................... ...........................|........................... ..........................." )
    source.Update()
    
    shrink = vtk.vtkShrinkFilter()
    shrink.SetInputConnection(source.GetOutputPort())
    shrink.SetShrinkFactor( .8 )
    
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(shrink.GetOutputPort())
    mapper.ScalarVisibilityOff()
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(colors.GetColor3d("Burlywood"))
    
    #Create the RenderWindow, Renderer and both Actors
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)
    
    renderer.SetBackground(colors.GetColor3d("SlateGray"))
    renderer.AddActor(actor)
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(150)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCameraClippingRange()
    
    renderWindow.SetSize(640, 480)
    interactor.Start()

if __name__ == '__main__':
    main()
