#!/usr/bin/env python

import vtk

camera = vtk.vtkCamera()
planesArray = [0 for i in range(24)]

camera.GetFrustumPlanes(1, planesArray)

planes = vtk.vtkPlanes()
planes.SetFrustumPlanes(planesArray)

frustumSource = vtk.vtkFrustumSource()
frustumSource.SetPlanes(planes)
frustumSource.Update()

frustum = frustumSource.GetOutput()

mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(frustum)
else:
    mapper.SetInputData(frustum)

actor = vtk.vtkActor()
actor.SetMapper(mapper)

# a renderer and render window
renderer = vtk.vtkRenderer()
renderWindow = vtk. vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)

# an interactor
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# add the actors to the scene
renderer.AddActor(actor)
renderer.SetBackground( .2, .1, .3) # Background color dark purple

# render an image (lights and cameras are created automatically)
renderWindow.Render()

# begin mouse interaction
renderWindowInteractor.Start()
