#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
    perlinNoise = vtk.vtkPerlinNoise()
    perlinNoise.SetFrequency(2, 1.25, 1.5)
    perlinNoise.SetPhase(0, 0, 0)
    
    sample = vtk.vtkSampleFunction()
    sample.SetImplicitFunction(perlinNoise)
    sample.SetSampleDimensions(65, 65, 20)
    sample.ComputeNormalsOff()
    
    surface = vtk.vtkContourFilter()
    surface.SetInputConnection(sample.GetOutputPort())
    surface.SetValue(0, 0.0)
    
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(surface.GetOutputPort())
    mapper.ScalarVisibilityOff()
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("Blue"))
    
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)
    
    # Add the actors to the renderer, set the background and size
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SlateGray")) # Slate Gray
    renderWindow.SetSize(300, 300)
    renderer.ResetCamera()
    renderWindow.Render()
    interactor.Start()
	
if __name__ == '__main__':
    main()
