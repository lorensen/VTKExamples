#!/usr/bin/env python
import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a circle
    polygonSource = vtk.vtkRegularPolygonSource()
    # Comment this line to generate a disk instead of a circle.
    polygonSource.GeneratePolygonOff()
    polygonSource.SetNumberOfSides(50)
    polygonSource.SetRadius(5.0)
    polygonSource.SetCenter(0.0, 0.0, 0.0)

    #  Visualize
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(polygonSource.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d('Cornsilk'))

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("Circle")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('DarkGreen'))

    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
