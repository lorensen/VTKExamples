# arrow.py adapted from the C++ vtk examples and translated to python.

import vtk

arrowSource = vtk.vtkArrowSource()
#arrowSource.SetShaftRadius(0.01)
#arrowSource.SetTipLength(.9)
 
# Create a mapper and actor
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(arrowSource.GetOutputPort())
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Visualize
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
 
renderer.AddActor(actor)
renderer.SetBackground(.1, .2, .3) # Background color dark blue
 
renderWindow.Render()
renderWindowInteractor.Start()
