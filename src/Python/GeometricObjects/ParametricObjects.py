#!/usr/bin/env python

import vtk


class ParametricObjects(object):
    def ParametricObjects(self):

        colors = vtk.vtkNamedColors()

        # Select one of the following functions.
        # parametricObject = vtk.vtkParametricBoy()
        # parametricObject = vtk.vtkParametricConicSpiral()
        # parametricObject = vtk.vtkParametricCrossCap()
        # parametricObject = vtk.vtkParametricDini()
        # parametricObject = vtk.vtkParametricEllipsoid()
        # parametricObject = vtk.vtkParametricEnneper()
        # parametricObject = vtk.vtkParametricFigure8Klein()
        # parametricObject = vtk.vtkParametricKlein()
        # parametricObject = vtk.vtkParametricMobius()
        # parametricObject = vtk.vtkParametricRandomHills()
        # parametricObject = vtk.vtkParametricRoman()
        # parametricObject = vtk.vtkParametricSpline()
        # parametricObject = vtk.vtkParametricSuperEllipsoid()
        # parametricObject = vtk.vtkParametricSuperToroid()
        parametricObject = vtk.vtkParametricTorus()

        parametricSource = vtk.vtkParametricFunctionSource()
        parametricSource.SetParametricFunction(parametricObject)

        # mapper
        mapper = vtk.vtkPolyDataMapper()
        mapper.SetInputConnection(parametricSource.GetOutputPort())

        # actor
        actor = vtk.vtkActor()
        actor.SetMapper(mapper)
        actor.GetProperty().SetDiffuseColor(colors.GetColor3d("Burlywood"))

        # ------------------------------------------------------------
        # Create the RenderWindow, Renderer and Interactor
        # ------------------------------------------------------------
        ren = vtk.vtkRenderer()
        renWin = vtk.vtkRenderWindow()
        iren = vtk.vtkRenderWindowInteractor()

        renWin.AddRenderer(ren)
        iren.SetRenderWindow(renWin)

        # add actors
        ren.AddViewProp(actor)
        ren.SetBackground(colors.GetColor3d("Beige"))

        # enable user interface interactor
        iren.Initialize()
        renWin.Render()
        iren.Start()


if __name__ == "__main__":
    po = ParametricObjects()
    po.ParametricObjects()
