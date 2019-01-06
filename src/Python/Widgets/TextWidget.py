#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# by Panos Mavrogiorgos, email : pmav99 >a< gmail

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor('bkg', [0.1, 0.2, 0.4, 1.0])

    source = vtk.vtkSphereSource()
    output = source.GetOutput()

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(output)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d('bkg'))

    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
    render_window.SetSize(300, 300)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(render_window)

    # Create the TextActor
    text_actor = vtk.vtkTextActor()
    text_actor.SetInput("This is a test")
    text_actor.GetTextProperty().SetColor(colors.GetColor3d('Cyan'))

    # Create the text representation. Used for positioning the text_actor
    text_representation = vtk.vtkTextRepresentation()
    text_representation.GetPositionCoordinate().SetValue(0.15, 0.15)
    text_representation.GetPosition2Coordinate().SetValue(0.7, 0.2)

    # Create the TextWidget
    # Note that the SelectableOff method MUST be invoked!
    # According to the documentation :
    #
    # SelectableOn/Off indicates whether the interior region of the widget can be
    # selected or not. If not, then events (such as left mouse down) allow the user
    # to "move" the widget, and no selection is possible. Otherwise the
    # SelectRegion() method is invoked.
    text_widget = vtk.vtkTextWidget()
    text_widget.SetRepresentation(text_representation)
    text_widget.SetInteractor(interactor)
    text_widget.SetTextActor(text_actor)
    text_widget.SelectableOff()
    text_widget.On()

    interactor.Initialize()
    render_window.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
