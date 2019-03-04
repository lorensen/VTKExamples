#!/usr/bin/env python

# This example creates a tube around a line.
# This is helpful because when you zoom the camera, 
# the thickness of a line remains constant, 
# while the thickness of a tube varies.


import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Change Color Name to Use your own Color for Actor
    ActorColor=colors.GetColor3d("Red");
    # Change Color Name to Use your own Color for Renderer Background
    BgColor=colors.GetColor3d("Gray");

    # Create a line
    lineSource = vtk.vtkLineSource();
    lineSource.SetPoint1(1.0, 0.0, 0.0);
    lineSource.SetPoint2(.0, 1.0, 0.0);

    # Setup actor and mapper
    lineMapper = vtk.vtkPolyDataMapper()
    lineMapper.SetInputConnection(lineSource.GetOutputPort())

    lineActor = vtk.vtkActor()
    lineActor.SetMapper(lineMapper)
    lineActor.GetProperty().SetColor(ActorColor)

    # Create tube filter
    tubeFilter=vtk.vtkTubeFilter()
    tubeFilter.SetInputConnection(lineSource.GetOutputPort())
    tubeFilter.SetRadius(0.025)
    tubeFilter.SetNumberOfSides(50)
    tubeFilter.Update()

    # Setup actor and mapper
    tubeMapper = vtk.vtkPolyDataMapper()
    tubeMapper.SetInputConnection(tubeFilter.GetOutputPort())

    tubeActor= vtk.vtkActor()
    tubeActor.SetMapper(tubeMapper)
    # Make the tube have some transparency.
    tubeActor.GetProperty().SetOpacity(0.5);

    # Setup render window, renderer, and interactor
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetWindowName("TubeLine")
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    #Visualise the arrow
    renderer.AddActor(lineActor)
    renderer.AddActor(tubeActor)
    renderer.SetBackground(BgColor)
    renderer.ResetCamera()

    renderWindow.SetSize(300,300)
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()

