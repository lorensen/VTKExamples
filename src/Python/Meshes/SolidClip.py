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
    # This will give us the polygonal data that is clipped away
    clipper.GenerateClippedOutputOn()

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

    # Here we get the the polygonal data that is clipped away
    clipped_away_mapper = vtk.vtkPolyDataMapper()
    clipped_away_mapper.SetInputData(clipper.GetClippedOutput())
    clipped_away_mapper.ScalarVisibilityOff()

    # Let us display it as a faint object
    clipped_away_actor = vtk.vtkActor()
    clipped_away_actor.SetMapper(clipped_away_mapper)
    clipped_away_actor.GetProperty().SetDiffuseColor(colors.GetColor3d("Silver"))
    clipped_away_actor.GetProperty().SetOpacity(0.1)

    # Create a renderer
    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d('SlateGray'))

    render_window = vtk.vtkRenderWindow()

    render_window.AddRenderer(renderer)

    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    # Add the actor to the renderer
    renderer.AddActor(superquadric_actor)
    renderer.AddActor(clipped_away_actor)
    render_window.SetSize(600, 600)
    renderer.ResetCamera()
    renderer.GetActiveCamera().Dolly(1.5)
    renderer.ResetCameraClippingRange()
    render_window.Render()
    render_window.SetWindowName('SolidClip')

    # Interact with the window
    render_window_interactor.Start()


if __name__ == '__main__':
    main()
