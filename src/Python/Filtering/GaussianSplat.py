#!/usr/bin/env python

import vtk

def main():
    # Create points on a sphere
    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()
	
    colors = vtk.vtkNamedColors()
	
    polydata = vtk.vtkPolyData()
    polydata.SetPoints(sphereSource.GetOutput().GetPoints())
    
    splatter = vtk.vtkGaussianSplatter()
    splatter.SetInputData(polydata)
    splatter.SetSampleDimensions(50,50,50)
    splatter.SetRadius(0.5)
    splatter.ScalarWarpingOff()
    
    surface = vtk.vtkContourFilter()
    surface.SetInputConnection(splatter.GetOutputPort())
    surface.SetValue(0,0.01)
    
    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(surface.GetOutputPort())
    
    actor =  vtk.vtkActor()
    actor.SetMapper(mapper)
    
    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("white"))
 
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
