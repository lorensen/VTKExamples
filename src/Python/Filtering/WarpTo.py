#!/usr/bin/env python
import vtk

def main():
    colors = vtk.vtkNamedColors()
    # Create the RenderWindow, Renderer and both Actors
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    # Create a line
    lineSource = vtk.vtkLineSource()
    lineSource.SetPoint1(0.0, 0.0, 0.0)
    lineSource.SetPoint2(0.0, 1.0, 0.0)
    lineSource.SetResolution(20)
    lineSource.Update()
    
    # Create a tube (cylinder) around the line
    tubeFilter = vtk.vtkTubeFilter()
    tubeFilter.SetInputConnection(lineSource.GetOutputPort())
    tubeFilter.SetRadius(.01) #default is .5
    tubeFilter.SetNumberOfSides(50)
    tubeFilter.Update()
    
    warpTo = vtk.vtkWarpTo()
    warpTo.SetInputConnection(tubeFilter.GetOutputPort())
    warpTo.SetPosition(10, 1, 0)
    warpTo.SetScaleFactor(5)
    warpTo.AbsoluteOn()
    
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(warpTo.GetOutputPort())
    mapper.ScalarVisibilityOff()
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
	
    renderer.SetBackground(colors.GetColor3d("green"))
    renderer.AddActor(actor)
    renderWindowInteractor.Initialize()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
