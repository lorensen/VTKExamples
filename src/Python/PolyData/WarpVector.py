#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    points = vtk.vtkPoints()
    points.InsertNextPoint(0.0, 0.0, 0.0)
    points.InsertNextPoint(1.0, 0.0, 0.0)
    points.InsertNextPoint(2.0, 0.0, 0.0)
    points.InsertNextPoint(3.0, 0.0, 0.0)
    points.InsertNextPoint(4.0, 0.0, 0.0)

    lines = vtk.vtkCellArray()
    line = vtk.vtkLine()
    line.GetPointIds().SetId(0, 0)
    line.GetPointIds().SetId(1, 1)
    lines.InsertNextCell(line)
    line.GetPointIds().SetId(0, 1)
    line.GetPointIds().SetId(1, 2)
    lines.InsertNextCell(line)
    line.GetPointIds().SetId(0, 2)
    line.GetPointIds().SetId(1, 3)
    lines.InsertNextCell(line)
    line.GetPointIds().SetId(0, 3)
    line.GetPointIds().SetId(1, 4)
    lines.InsertNextCell(line)

    warpData = vtk.vtkDoubleArray()
    warpData.SetNumberOfComponents(3)
    warpData.SetName("warpData")
    warp = [0.0, 0.0, 0.0]
    warp[1] = 0.0
    warpData.InsertNextTuple(warp)
    warp[1] = 0.1
    warpData.InsertNextTuple(warp)
    warp[1] = 0.3
    warpData.InsertNextTuple(warp)
    warp[1] = 0.0
    warpData.InsertNextTuple(warp)
    warp[1] = 0.1
    warpData.InsertNextTuple(warp)

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    polydata.SetLines(lines)
    polydata.GetPointData().AddArray(warpData)
    polydata.GetPointData().SetActiveVectors(warpData.GetName())

    # WarpVector will use the array marked as active vector in polydata
    # it has to be a 3 component array
    # with the same number of tuples as points in polydata
    warpVector = vtk.vtkWarpVector()
    warpVector.SetInputData(polydata)
    warpVector.Update()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(warpVector.GetPolyDataOutput())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('cobalt_green'))

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)
    renderWindow.Render()
    renderWindowInteractor.Start()


if __name__ == '__main__':
    main()
