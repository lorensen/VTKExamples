#!/usr/bin/env python

import vtk

def main(): 
    # Create 5 points (vtkPolyData)
    pointSource = vtk.vtkPointSource()
    pointSource.SetNumberOfPoints(5)
    pointSource.Update()
    
    polydata = pointSource.GetOutput()
    
    print "points in polydata are",polydata.GetNumberOfPoints()
    
    # Create 2 points in a vtkUnstructuredGrid
    points = vtk.vtkPoints()
    points.InsertNextPoint(0,0,0)
    points.InsertNextPoint(0,0,1)
    
    ug = vtk.vtkUnstructuredGrid()
    ug.SetPoints(points)
    print "points in unstructured grid are",ug.GetNumberOfPoints()
    
    # Combine the two data sets
    appendFilter = vtk.vtkAppendFilter()
    appendFilter.AddInputData(polydata)
    appendFilter.AddInputData(ug)
    appendFilter.Update()
    
    combined = vtk.vtkUnstructuredGrid()
    
    combined = appendFilter.GetOutput()
    print "Combined points are", combined.GetNumberOfPoints()
    
    # Create a mapper and actor
    colors = vtk.vtkNamedColors()
    
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(appendFilter.GetOutputPort())
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetPointSize(5)
    
    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    # Add the actor to the scene
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))
    
    # Render and interact
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
