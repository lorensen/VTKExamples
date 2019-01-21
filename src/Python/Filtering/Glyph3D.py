#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
    
    points = vtk.vtkPoints()
    points.InsertNextPoint(0,0,0)
    points.InsertNextPoint(1,1,1)
    points.InsertNextPoint(2,2,2)
    
    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    
    # Create anything you want here, we will use a cube for the demo.
    cubeSource = vtk.vtkCubeSource()
    
    glyph3D = vtk.vtkGlyph3D()
    glyph3D.SetSourceConnection(cubeSource.GetOutputPort())
    glyph3D.SetInputData(polydata)
    glyph3D.Update()
    
    # Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(glyph3D.GetOutputPort())
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SlateGray")) # Background Slate Gray
    
    renderWindow.Render()
    renderWindowInteractor.Start()
	
if __name__ == '__main__':
    main()
