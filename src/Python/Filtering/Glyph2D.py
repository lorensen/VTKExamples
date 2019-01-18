#!/usr/bin/env python

import vtk

def main():
    points = vtk.vtkPoints()
    points.InsertNextPoint(0,0,0)
    points.InsertNextPoint(1,1,0)
    points.InsertNextPoint(2,2,0)
    
    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    
    # Create anything you want here, we will use a polygon for the demo.
    polygonSource = vtk.vtkRegularPolygonSource() #default is 6 sides
    
    glyph2D = vtk.vtkGlyph2D()
    glyph2D.SetSourceConnection(polygonSource.GetOutputPort())
    glyph2D.SetInputData(polydata)
    glyph2D.Update()
    
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(glyph2D.GetOutputPort())
    mapper.Update()
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    
    # Visualize
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    renderer.AddActor(actor)
    
    style =  vtk.vtkInteractorStyleImage()
    renderWindowInteractor.SetInteractorStyle( style )
    
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
