#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
    
    # Create the axes and the associated mapper and actor.
    axes = vtk.vtkAxes()
    axes.SetOrigin(0, 0, 0)
    axesMapper = vtk.vtkPolyDataMapper()
    axesMapper.SetInputConnection(axes.GetOutputPort())
    axesActor = vtk.vtkActor()
    axesActor.SetMapper(axesMapper)
    
    # Create the 3D text and the associated mapper and follower (a type of actor).  Position the text so it is displayed over the origin of the axes.
    atext = vtk.vtkVectorText()
    atext.SetText("Origin")
    textMapper = vtk.vtkPolyDataMapper()
    textMapper.SetInputConnection(atext.GetOutputPort())
    textActor = vtk.vtkFollower()
    textActor.SetMapper(textMapper)
    textActor.SetScale(0.2, 0.2, 0.2)
    textActor.AddPosition(0, -0.1, 0)
    
    # Create the Renderer, RenderWindow, and RenderWindowInteractor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(640, 480)
    
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)
    
    style = vtk.vtkInteractorStyleTrackballCamera()
    interactor.SetInteractorStyle( style )
    
    # Add the actors to the renderer.
    renderer.AddActor(axesActor)
    renderer.AddActor(textActor)
    
    renderer.SetBackground(colors.GetColor3d("Silver"))
    
    # Zoom in closer.
    renderer.ResetCamera()
    renderer.GetActiveCamera().Zoom(1.6)
    
    renderer.SetBackground(colors.GetColor3d("Silver"))
    
    # Reset the clipping range of the camera; set the camera of the follower; render.
    renderer.ResetCameraClippingRange()
    textActor.SetCamera(renderer.GetActiveCamera())
    
    interactor.Initialize()
    renderWindow.Render()
    interactor.Start()
	
if __name__ == '__main__':
    main()
