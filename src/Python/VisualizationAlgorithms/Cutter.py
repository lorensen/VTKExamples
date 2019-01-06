#!/usr/bin/env python

# A simple script to demonstrate the vtkCutter function

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a cube
    cube = vtk.vtkCubeSource()
    cube.SetXLength(40)
    cube.SetYLength(30)
    cube.SetZLength(20)
    cubeMapper = vtk.vtkPolyDataMapper()
    cubeMapper.SetInputConnection(cube.GetOutputPort())

    # create a plane to cut,here it cuts in the XZ direction (xz normal=(1,0,0);XY =(0,0,1),YZ =(0,1,0)
    plane = vtk.vtkPlane()
    plane.SetOrigin(10, 0, 0)
    plane.SetNormal(1, 0, 0)

    # create cutter
    cutter = vtk.vtkCutter()
    cutter.SetCutFunction(plane)
    cutter.SetInputConnection(cube.GetOutputPort())
    cutter.Update()
    cutterMapper = vtk.vtkPolyDataMapper()
    cutterMapper.SetInputConnection(cutter.GetOutputPort())

    # create plane actor
    planeActor = vtk.vtkActor()
    planeActor.GetProperty().SetColor(colors.GetColor3d("Yellow"))
    planeActor.GetProperty().SetLineWidth(2)
    planeActor.SetMapper(cutterMapper)

    # create cube actor
    cubeActor = vtk.vtkActor()
    cubeActor.GetProperty().SetColor(colors.GetColor3d("Aquamarine"))
    cubeActor.GetProperty().SetOpacity(0.3)
    cubeActor.SetMapper(cubeMapper)

    # create renderers and add actors of plane and cube
    ren = vtk.vtkRenderer()
    ren.AddActor(planeActor)
    ren.AddActor(cubeActor)

    # Add renderer to renderwindow and render
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    renWin.SetSize(600, 600)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    ren.SetBackground(colors.GetColor3d("Silver"))
    renWin.Render()

    iren.Start()


if __name__ == '__main__':
    main()
