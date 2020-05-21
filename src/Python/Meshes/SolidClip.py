# !/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    # Create a superquadric
    superquadric_source = vtk.vtkSuperquadricSource()
    superquadric_source.SetPhiRoundness(3.1)
    superquadric_source.SetThetaRoundness(2.2)

    # Define a clipping plane
    clip_plane = vtk.vtkPlane()
    clip_plane.SetNormal(1.0, -1.0, -1.0)
    clip_plane.SetOrigin(0.0, 0.0, 0.0)

    # Clip the source with the plane
    clipper = vtk.vtkClipPolyData()
    clipper.SetInputConnection(superquadric_source.GetOutputPort())
    clipper.SetClipFunction(clip_plane)

    # Create a mapper and actor
    superquadric_mapper = vtk.vtkPolyDataMapper()
    superquadric_mapper.SetInputConnection(clipper.GetOutputPort())

    superquadric_actor = vtk.vtkActor()
    superquadric_actor.SetMapper(superquadric_mapper)

    colors = vtk.vtkNamedColors()

    # Create a property to be used for the back faces. Turn off all
    # shading by specifying 0 weights for specular and diffuse. Max the
    # ambient.
    back_faces = vtk.vtkProperty()
    back_faces.SetSpecular(0.0)
    back_faces.SetDiffuse(0.0)
    back_faces.SetAmbient(1.0)
    back_faces.SetAmbientColor(colors.GetColor3d('Tomato'))

    superquadric_actor.SetBackfaceProperty(back_faces)

    # Create a renderer
    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d('Black'))

    render_window = vtk.vtkRenderWindow()

    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    # Add the actor to the renderer
    renderer.AddActor(superquadric_actor)
    render_window.Render()
    render_window.SetWindowName('SolidClip')

    # Interact with the window
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
