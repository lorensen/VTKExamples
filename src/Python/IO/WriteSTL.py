#!/usr/bin/env python

import vtk


def main():
    filename = "test.stl"

    sphereSource = vtk.vtkSphereSource()
    sphereSource.Update()

    # Write the stl file to disk
    stlWriter = vtk.vtkSTLWriter()
    stlWriter.SetFileName(filename)
    stlWriter.SetInputConnection(sphereSource.GetOutputPort())
    stlWriter.Write()

    # Read and display for verification
    reader = vtk.vtkSTLReader()
    reader.SetFileName(filename)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Create a rendering window and renderer
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)

    # Create a renderwindowinteractor
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Assign actor to the renderer
    ren.AddActor(actor)

    # Enable user interface interactor
    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
