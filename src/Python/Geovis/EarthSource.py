#!/usr/bin/env python
import vtk

def main():
    colors = vtk.vtkNamedColors()
    #Create a sphere
    earthSource = vtk.vtkEarthSource()
    earthSource.OutlineOff()
    earthSource.Update()
    
    #Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(earthSource.GetOutputPort())
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    
    #Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    #Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("green")) # Background color green
    
    #Render and interact
    renderWindow.Render()
	# screenshot code:
    w2if = vtk.vtkWindowToImageFilter()
    w2if.SetInput(renderWindow)
    w2if.Update()
    
    writer = vtk.vtkPNGWriter()
    writer.SetFileName("TestEarthSource.png")
    writer.SetInputConnection(w2if.GetOutputPort())
    writer.Write()
	
	# begin interaction
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
