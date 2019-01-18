#!/usr/bin/env python

import vtk
import random

def main():

    colors = vtk.vtkNamedColors()
    # Create points on an XY grid with random Z coordinate
    points = vtk.vtkPoints()
    
    for x in range (0, 10):
        for y in range (0, 10): 
           points.InsertNextPoint(x, y, random.uniform(0.0, 3.0))
      
    
    # Add the grid points to a polydata object
    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    
    glyphFilter = vtk.vtkVertexGlyphFilter()
    glyphFilter.SetInputData(polydata)
    glyphFilter.Update()
    
    # Create a mapper and actor
    pointsMapper = vtk.vtkPolyDataMapper()
    pointsMapper.SetInputConnection(glyphFilter.GetOutputPort())
    
    pointsActor = vtk.vtkActor()
    pointsActor.SetMapper(pointsMapper)
    pointsActor.GetProperty().SetPointSize(3)
    pointsActor.GetProperty().SetColor(colors.GetColor3d("Red"))
    
    # Triangulate the grid points
    delaunay = vtk.vtkDelaunay2D()
    delaunay.SetInputData(polydata)
    delaunay.Update()
    
    # Create a mapper and actor
    triangulatedMapper = vtk.vtkPolyDataMapper()
    triangulatedMapper.SetInputConnection(delaunay.GetOutputPort())
    
    triangulatedActor = vtk.vtkActor()
    triangulatedActor.SetMapper(triangulatedMapper)
    
    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    # Add the actor to the scene
    renderer.AddActor(pointsActor)
    renderer.AddActor(triangulatedActor)
    renderer.SetBackground(colors.GetColor3d("Green")) # Background color green
    
    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
