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
    
    vertexGlyphFilter = vtk.vtkVertexGlyphFilter()
    vertexGlyphFilter.AddInputData(polydata)
    vertexGlyphFilter.Update()
    
    # Create a mapper and actor
    mapper =  vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(vertexGlyphFilter.GetOutputPort())
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetPointSize(10)
    actor.GetProperty().SetColor(colors.GetColor3d("Yellow"))
    
    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor =  vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    # Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Green")) # Background color green
    
    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
