#!/usr/bin/env python

import vtk

# Use this variable to select one of the two methods below.
SELECT_FRUSTUM_METHOD = True

if SELECT_FRUSTUM_METHOD:
    # one way    
    camera = vtk.vtkCamera()
    planesArray = [0 for i in range(24)]
    
    camera.GetFrustumPlanes(1, planesArray)
    
    planes = vtk.vtkPlanes()
    planes.SetFrustumPlanes(planesArray)

else:    
    # another way    
    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()
    bounds = [0 for i in range(6)]
    sphereSource.GetOutput().GetBounds(bounds)
    
    planes = vtk.vtkPlanes()
    planes.SetBounds(bounds)
    
# At this point we have the planes created by either of the methods above.
# You can do whatever you want with them.

# For visualisation we will produce an n-sided convex hull 
# and visualise it.

# To generate the convex hull we supply a vtkPolyData object and a bounding box.
# We define the bounding box to be where we expect the resulting polyhedron to lie.
# Make it a generous fit as it is only used to create the initial
# polygons that are eventually clipped.
hull  = vtk.vtkHull()
hull.SetPlanes(planes)

pd = vtk.vtkPolyData()

hull.GenerateHull(pd, -200, 200, -200, 200, -200, 200)

mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(pd)
else:
    mapper.SetInputData(pd)

actor = vtk.vtkActor()
actor.SetMapper(mapper)

renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
renderer.AddActor(actor)

renderWindow.Render()
renderWindowInteractor.Start()       
