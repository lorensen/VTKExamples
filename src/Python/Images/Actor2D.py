#!/usr/bin/env python

import vtk

def main():
    
    colors = vtk.vtkNamedColors()
    points = vtk.vtkPoints()
    points.InsertNextPoint(10,10,0)
    points.InsertNextPoint(100,100,0)
    points.InsertNextPoint(200,200,0)
    
    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    
    glyphFilter = vtk.vtkVertexGlyphFilter()
    glyphFilter.SetInputData(polydata)
    glyphFilter.Update()
    
    mapper = vtk.vtkPolyDataMapper2D()
    mapper.SetInputConnection(glyphFilter.GetOutputPort())
    mapper.Update()
    
    actor = vtk.vtkActor2D()
    actor.SetMapper(mapper)
    
    # Create a renderer, render window, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    # Add the actor to the scene
    renderer.AddActor(actor)
    renderWindow.SetSize(300,300)
    actor.GetProperty().SetColor(colors.GetColor3d("green")) 
    actor.GetProperty().SetPointSize(6)
    
    # Render and interact
    renderWindow.Render()
    w2if = vtk.vtkWindowToImageFilter()
    w2if.SetInput(renderWindow)
    w2if.Update()
    
    writer = vtk.vtkPNGWriter()
    writer.SetFileName("TestActor2D.png")
    writer.SetInputConnection(w2if.GetOutputPort())
    writer.Write()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
