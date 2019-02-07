#!/usr/bin/env python

import vtk

def main():
    colors = vtk.vtkNamedColors()
	
    # Create an image
    source1 = vtk.vtkImageCanvasSource2D()
    source1.SetScalarTypeToUnsignedChar()
    source1.SetNumberOfScalarComponents(3)
    source1.SetExtent(0, 100, 0, 100, 0, 0)
    source1.SetDrawColor(0,0,0,1)
    source1.FillBox(0, 100, 0, 100)
    source1.SetDrawColor(255,0,0,1)
    source1.FillBox(10, 20, 10, 20)
    source1.FillBox(40, 50, 20, 30)
    source1.Update()
    
    # Convert the image to a polydata
    imageDataGeometryFilter = vtk.vtkImageDataGeometryFilter()
    imageDataGeometryFilter.SetInputConnection(source1.GetOutputPort())
    imageDataGeometryFilter.Update()
    
    # Create a mapper and actor
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(imageDataGeometryFilter.GetOutputPort())
    
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    
    # Visualization
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("white")) # Background color white
    renderWindow.Render()
    renderWindowInteractor.Start()

if __name__ == '__main__':
    main()
