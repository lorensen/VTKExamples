#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
    
    # Create the polydata geometry
    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()
    
    # Set up the actor to display the untransformed polydata
    originalMapper = vtk.vtkPolyDataMapper()
    originalMapper.SetInputConnection(sphereSource.GetOutputPort())
    
    originalActor = vtk.vtkActor()
    originalActor.SetMapper(originalMapper)
    originalActor.GetProperty().SetColor(colors.GetColor3d("blue"))
    
    # Set up the transform filter
    translation = vtk.vtkTransform()
    translation.Translate(1.0, 2.0, 3.0)
    
    transformFilter = vtk.vtkTransformPolyDataFilter()
    transformFilter.SetInputConnection(sphereSource.GetOutputPort())
    transformFilter.SetTransform(translation)
    transformFilter.Update()
    
    # Set up the actor to display the transformed polydata
    transformedMapper = vtk.vtkPolyDataMapper()
    transformedMapper.SetInputConnection(transformFilter.GetOutputPort())
    
    transformedActor = vtk.vtkActor()
    transformedActor.SetMapper(transformedMapper)
    transformedActor.GetProperty().SetColor(colors.GetColor3d("red"))
    
    # Set up the rest of the visualization pipeline
    renderer = vtk.vtkRenderer()
    renderer.AddActor(originalActor)
    renderer.AddActor(transformedActor)
    renderer.SetBackground(colors.GetColor3d("green")) # Set renderer's background color to green
    
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    renderWindowInteractor.Start()
	
if __name__ == '__main__':
    main()
