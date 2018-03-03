#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create a rendering window and renderer.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.SetWindowName("Text Actor")
    renWin.AddRenderer(ren)

    # Create a render window interactor.
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create a text actor.
    txt = vtk.vtkTextActor()
    txt.SetInput("Hello World!")
    txtprop = txt.GetTextProperty()
    txtprop.SetFontFamilyToArial()
    txtprop.BoldOn()
    txtprop.SetFontSize(36)
    txtprop.ShadowOn()
    txtprop.SetShadowOffset(4, 4)
    txtprop.SetColor(colors.GetColor3d("Cornsilk"))
    txt.SetDisplayPosition(20, 30)

    # Assign actor to the renderer.
    ren.AddActor(txt)
    ren.SetBackground(colors.GetColor3d("DarkGreen"))

    # Enable user interface interactor.
    iren.Initialize()
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
