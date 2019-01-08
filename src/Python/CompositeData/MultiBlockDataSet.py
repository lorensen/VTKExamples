#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # PART 1 Make some Data.
    # Make a tree.
    root = vtk.vtkMultiBlockDataSet()

    branch = vtk.vtkMultiBlockDataSet()
    root.SetBlock(0, branch)

    # Make some leaves.
    leaf1 = vtk.vtkSphereSource()
    leaf1.SetCenter(0, 0, 0)
    leaf1.Update()
    branch.SetBlock(0, leaf1.GetOutput())

    leaf2 = vtk.vtkSphereSource()
    leaf2.SetCenter(1.75, 2.5, 0)
    leaf2.SetRadius(1.5)
    leaf2.Update()
    branch.SetBlock(1, leaf2.GetOutput())

    leaf3 = vtk.vtkSphereSource()
    leaf3.SetCenter(4, 0, 0)
    leaf3.SetRadius(2)
    leaf3.Update()
    root.SetBlock(1, leaf3.GetOutput())

    # PART 2 Do something with the data
    # a non composite aware filter, the pipeline will iterate
    edges = vtk.vtkExtractEdges()
    edges.SetInputData(root)

    # PART 3 Show the data
    # also demonstrate a composite aware filter
    # this filter aggregates all blocks into one polydata
    # this is handy for display, although fairly limited
    # see vtkCompositePolyDataMapper2 for something better
    polydata = vtk.vtkCompositeDataGeometryFilter()
    polydata.SetInputConnection(edges.GetOutputPort())

    # Create the Renderer, RenderWindow, and RenderWindowInteractor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(0, polydata.GetOutputPort(0))
    actor = vtk.vtkActor()
    actor.GetProperty().SetColor(colors.GetColor3d("Yellow"))
    actor.GetProperty().SetLineWidth(2)
    actor.SetMapper(mapper)

    # Enable user interface interactor.
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("CornflowerBlue"))
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
