#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    aren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(aren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create single splat point
    pts = vtk.vtkPoints()
    verts = vtk.vtkCellArray()
    norms = vtk.vtkDoubleArray()
    scalars = vtk.vtkDoubleArray()

    x = [0.0] * 3
    pts.InsertNextPoint(x)
    norms.SetNumberOfTuples(1)
    norms.SetNumberOfComponents(3)
    n = [0] * 3
    n[0] = 0.707
    n[1] = 0.707
    n[2] = 0.0
    norms.InsertTuple(0, n)
    scalars.SetNumberOfTuples(1)
    scalars.SetNumberOfComponents(1)
    scalars.InsertTuple1(0, 1.0)

    verts.InsertNextCell(1)
    verts.InsertCellPoint(0)

    pData = vtk.vtkPolyData()
    pData.SetPoints(pts)
    pData.SetVerts(verts)
    pData.GetPointData().SetNormals(norms)
    pData.GetPointData().SetScalars(scalars)

    # Splat point and generate isosurface.
    splat = vtk.vtkGaussianSplatter()
    splat.SetInputData(pData)
    splat.SetModelBounds(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)
    splat.SetSampleDimensions(75, 75, 75)
    splat.SetRadius(0.5)
    splat.SetEccentricity(5.0)
    splat.SetExponentFactor(-3.25)
    contour = vtk.vtkContourFilter()
    contour.SetInputConnection(splat.GetOutputPort())
    contour.SetValue(0, 0.9)
    splatMapper = vtk.vtkPolyDataMapper()
    splatMapper.SetInputConnection(contour.GetOutputPort())
    splatActor = vtk.vtkActor()
    splatActor.SetMapper(splatMapper)

    # Create outline.
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(splat.GetOutputPort())
    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())
    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Brown"))

    # Create cone to indicate direction.
    cone = vtk.vtkConeSource()
    cone.SetResolution(24)
    coneMapper = vtk.vtkPolyDataMapper()
    coneMapper.SetInputConnection(cone.GetOutputPort())
    coneActor = vtk.vtkActor()
    coneActor.SetMapper(coneMapper)
    coneActor.SetScale(0.75, 0.75, 0.75)
    coneActor.RotateZ(45.0)
    coneActor.AddPosition(0.50, 0.50, 0.0)
    coneActor.GetProperty().SetColor(colors.GetColor3d("DeepPink"))
    #
    # Rendering stuff.
    #
    aren.SetBackground(colors.GetColor3d("Beige"))
    aren.AddActor(splatActor)
    aren.AddActor(outlineActor)
    aren.AddActor(coneActor)

    renWin.SetSize(640, 480)
    renWin.Render()

    # Interact with the data.
    iren.Start()


if __name__ == '__main__':
    main()
