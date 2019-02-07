#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
    diskSource = vtk.vtkDiskSource()
    diskSource.Update()
    
    featureEdges = vtk.vtkFeatureEdges()
    featureEdges.SetInputConnection(diskSource.GetOutputPort())
    featureEdges.BoundaryEdgesOn()
    featureEdges.FeatureEdgesOff()
    featureEdges.ManifoldEdgesOff()
    featureEdges.NonManifoldEdgesOff()
    featureEdges.Update()
    
    # Visualize
    edgeMapper = vtk.vtkPolyDataMapper()
    edgeMapper.SetInputConnection(featureEdges.GetOutputPort())
    edgeActor = vtk.vtkActor()
    edgeActor.SetMapper(edgeMapper)
    
    diskMapper = vtk.vtkPolyDataMapper()
    diskMapper.SetInputConnection(diskSource.GetOutputPort())
    diskActor = vtk.vtkActor()
    diskActor.SetMapper(diskMapper)
    
    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    renderer.AddActor(edgeActor)
    renderer.AddActor(diskActor)
    renderer.SetBackground(colors.GetColor3d("green")) # Background color green
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
