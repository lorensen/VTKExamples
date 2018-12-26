#!/usr/bin/env python

import vtk

def main():
  value = 2.0
  colors = vtk.vtkNamedColors()
  
  implicitFunction = vtk.vtkSuperquadric()
  implicitFunction.SetPhiRoundness(2.5)
  implicitFunction.SetThetaRoundness(.5)
  
  # Sample the function.
  sample = vtk.vtkSampleFunction()
  sample.SetSampleDimensions(50,50,50)
  sample.SetImplicitFunction(implicitFunction)
  
  xmin, xmax, ymin, ymax, zmin, zmax = -value, value, -value, value, -value, value
  sample.SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax)
  
  # Create the 0 isosurface.
  contours = vtk.vtkContourFilter()
  contours.SetInputConnection(sample.GetOutputPort())
  contours.GenerateValues(1, 2.0, 2.0)
  
  # Map the contours to graphical primitives.
  contourMapper = vtk.vtkPolyDataMapper()
  contourMapper.SetInputConnection(contours.GetOutputPort())
  contourMapper.SetScalarRange(0.0, 1.2)
  
  # Create an actor for the contours.
  contourActor = vtk.vtkActor()
  contourActor.SetMapper(contourMapper)
  
  # Create a box around the function to indicate the sampling volume. 
  
  #Create outline.
  outline = vtk.vtkOutlineFilter()
  outline.SetInputConnection(sample.GetOutputPort())
  
  # Map it to graphics primitives.
  outlineMapper = vtk.vtkPolyDataMapper()
  outlineMapper.SetInputConnection(outline.GetOutputPort())
  
  # Create an actor.
  outlineActor = vtk.vtkActor()
  outlineActor.SetMapper(outlineMapper)
  outlineActor.GetProperty().SetColor(0,0,0)
  
  # Visualize.
  renderer = vtk.vtkRenderer()
  renderWindow = vtk.vtkRenderWindow()
  renderWindow.AddRenderer(renderer)
  interactor = vtk.vtkRenderWindowInteractor()
  interactor.SetRenderWindow(renderWindow)
  
  renderer.AddActor(contourActor)
  renderer.AddActor(outlineActor)
  renderer.SetBackground(colors.GetColor3d("Tan"))
  	
  # Enable user interface interactor
  renderWindow.Render()
  interactor.Start()
		
if __name__ == '__main__':
    main()  
		
