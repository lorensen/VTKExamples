#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
    # Create an image
    source = vtk.vtkImageSinusoidSource()
    source.Update()
    
    normalizeFilter = vtk.vtkImageNormalize()
    
    normalizeFilter.SetInputConnection(source.GetOutputPort())
    normalizeFilter.Update()
    
    inputCastFilter = vtk.vtkImageCast()
    inputCastFilter.SetInputConnection(source.GetOutputPort())
    inputCastFilter.SetOutputScalarTypeToUnsignedChar()
    inputCastFilter.Update()
    
    normalizeCastFilter = vtk.vtkImageCast()
    normalizeCastFilter.SetInputConnection(normalizeFilter.GetOutputPort())
    normalizeCastFilter.SetOutputScalarTypeToUnsignedChar()
    normalizeCastFilter.Update()
    
    # Create actors
    inputActor = vtk.vtkImageActor()
    inputActor.GetMapper().SetInputConnection(inputCastFilter.GetOutputPort())
    
    normalizedActor = vtk.vtkImageActor()
    normalizedActor.GetMapper().SetInputConnection(normalizeCastFilter.GetOutputPort())
    
    # There will be one render window
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(600, 300)
    
    # And one interactor
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)
    
    # Define viewport ranges
    # (xmin, ymin, xmax, ymax)
    leftViewport = [0.0, 0.0, 0.5, 1.0]
    rightViewport = [0.5, 0.0, 1.0, 1.0]
    
    # Setup both renderers
    leftRenderer = vtk.vtkRenderer()
    renderWindow.AddRenderer(leftRenderer)
    leftRenderer.SetViewport(leftViewport)
    leftRenderer.SetBackground(colors.GetColor3d("lemon_chiffon"))
    
    rightRenderer = vtk.vtkRenderer()
    renderWindow.AddRenderer(rightRenderer)
    rightRenderer.SetViewport(rightViewport)
    rightRenderer.SetBackground(colors.GetColor3d("gray"))
    
    leftRenderer.AddActor(inputActor)
    rightRenderer.AddActor(normalizedActor)
    
    leftRenderer.ResetCamera()
    
    rightRenderer.ResetCamera()
    
    renderWindow.Render()
	interactor.Start()

if __name__ == '__main__':
    main()
