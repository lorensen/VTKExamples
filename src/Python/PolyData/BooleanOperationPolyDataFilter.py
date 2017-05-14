#!/usr/bin/env python

import vtk

sphereSource1 = vtk.vtkSphereSource()
sphereSource1.SetCenter(0.25, 0, 0)
sphereSource1.Update()
input1 = sphereSource1.GetOutput()
sphere1Tri = vtk.vtkTriangleFilter()
sphere1Tri.SetInput(input1)

sphereSource2 = vtk.vtkSphereSource()
sphereSource2.Update()
input2 = sphereSource2.GetOutput()
sphere2Tri = vtk.vtkTriangleFilter()
sphere2Tri.SetInput(input2)

input1Mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    input1Mapper.SetInputConnection(input1.GetProducerPort())
else:
    input1Mapper.SetInputData(input1)

input1Mapper.ScalarVisibilityOff()
input1Actor = vtk.vtkActor()
input1Actor.SetMapper(input1Mapper)
input1Actor.GetProperty().SetColor(1,0,0)
input1Actor.SetPosition(input1.GetBounds()[1]-input1.GetBounds()[0],0 ,0)
input2Mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    input2Mapper.SetInputConnection(input2.GetProducerPort())
else:
    input2Mapper.SetInputData(input2)

input2Mapper.ScalarVisibilityOff()
input2Actor = vtk.vtkActor()
input2Actor.SetMapper(input2Mapper)
input2Actor.GetProperty().SetColor(0,1,0)
input2Actor.SetPosition(-(input2.GetBounds()[1]-input2.GetBounds()[0]), 0, 0)

booleanOperation = vtk.vtkBooleanOperationPolyDataFilter()
#booleanOperation.SetOperationToUnion()
booleanOperation.SetOperationToIntersection()
#booleanOperation.SetOperationToDifference()

if vtk.VTK_MAJOR_VERSION <= 5:
    booleanOperation.SetInputConnection(0, sphere1Tri.GetOutputPort())
    booleanOperation.SetInputConnection(1, sphere2Tri.GetOutputPort())
else:
    booleanOperation.SetInputData(0, sphere1Tri)
    booleanOperation.SetInputData(1, sphere2Tri)
booleanOperation.Update()

booleanOperationMapper = vtk.vtkPolyDataMapper()
booleanOperationMapper.SetInputConnection(booleanOperation.GetOutputPort())
booleanOperationMapper.ScalarVisibilityOff()

booleanOperationActor = vtk.vtkActor()
booleanOperationActor.SetMapper(booleanOperationMapper)

renderer = vtk.vtkRenderer()
renderer.AddViewProp(input1Actor)
renderer.AddViewProp(input2Actor)
renderer.AddViewProp(booleanOperationActor)
renderer.SetBackground(.1, .2, .3)
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer( renderer )

renWinInteractor = vtk.vtkRenderWindowInteractor()
renWinInteractor.SetRenderWindow( renderWindow )


renderWindow.Render()
renWinInteractor.Start()
