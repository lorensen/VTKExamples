#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    sphereSource1 = vtk.vtkSphereSource()
    sphereSource1.SetCenter(0.25, 0, 0)
    sphereSource1.Update()
    input1 = sphereSource1.GetOutput()
    sphere1Tri = vtk.vtkTriangleFilter()
    sphere1Tri.SetInputData(input1)

    sphereSource2 = vtk.vtkSphereSource()
    sphereSource2.Update()
    input2 = sphereSource2.GetOutput()
    sphere2Tri = vtk.vtkTriangleFilter()
    sphere2Tri.SetInputData(input2)

    input1Mapper = vtk.vtkPolyDataMapper()
    input1Mapper.SetInputData(input1)
    input1Mapper.ScalarVisibilityOff()
    input1Actor = vtk.vtkActor()
    input1Actor.SetMapper(input1Mapper)
    input1Actor.GetProperty().SetColor(colors.GetColor3d("Tomato"))
    input1Actor.SetPosition(input1.GetBounds()[1] - input1.GetBounds()[0], 0, 0)

    input2Mapper = vtk.vtkPolyDataMapper()
    input2Mapper.SetInputData(input2)
    input2Mapper.ScalarVisibilityOff()
    input2Actor = vtk.vtkActor()
    input2Actor.SetMapper(input2Mapper)
    input2Actor.GetProperty().SetColor(colors.GetColor3d("Mint"))
    input2Actor.SetPosition(-(input2.GetBounds()[1] - input2.GetBounds()[0]), 0, 0)

    booleanOperation = vtk.vtkPolyDataBooleanOperationFilter()
    # booleanOperation.SetOperationToUnion()
    booleanOperation.SetOpermodeToIntersection()
    # booleanOperation.SetOperationToDifference()

    booleanOperation.SetInputConnection(0, sphere1Tri.GetOutputPort())
    booleanOperation.SetInputConnection(1, sphere2Tri.GetOutputPort())
    booleanOperation.Update()

    booleanOperationMapper = vtk.vtkPolyDataMapper()
    booleanOperationMapper.SetInputConnection(booleanOperation.GetOutputPort())
    booleanOperationMapper.ScalarVisibilityOff()

    booleanOperationActor = vtk.vtkActor()
    booleanOperationActor.SetMapper(booleanOperationMapper)
    booleanOperationActor.GetProperty().SetDiffuseColor(colors.GetColor3d("Banana"))

    renderer = vtk.vtkRenderer()
    renderer.AddViewProp(input1Actor)
    renderer.AddViewProp(input2Actor)
    renderer.AddViewProp(booleanOperationActor)
    renderer.SetBackground(colors.GetColor3d("Silver"))
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)

    renWinInteractor = vtk.vtkRenderWindowInteractor()
    renWinInteractor.SetRenderWindow(renderWindow)

    renderWindow.Render()
    renWinInteractor.Start()


if __name__ == '__main__':
    main()
