#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("Bkg", [26, 51, 102, 255])

    # Create the rendering objects.
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create the pipeline, ball and spikes.
    sphere = vtk.vtkSphereSource()
    sphere.SetPhiResolution(7)
    sphere.SetThetaResolution(7)
    sphereMapper = vtk.vtkPolyDataMapper()
    sphereMapper.SetInputConnection(sphere.GetOutputPort())
    sphereActor = vtk.vtkActor()
    sphereActor.SetMapper(sphereMapper)
    sphereActor2 = vtk.vtkActor()
    sphereActor2.SetMapper(sphereMapper)

    cone = vtk.vtkConeSource()
    cone.SetResolution(5)
    glyph = vtk.vtkGlyph3D()
    glyph.SetInputConnection(sphere.GetOutputPort())
    glyph.SetSourceConnection(cone.GetOutputPort())
    glyph.SetVectorModeToUseNormal()
    glyph.SetScaleModeToScaleByVector()
    glyph.SetScaleFactor(0.25)
    spikeMapper = vtk.vtkPolyDataMapper()
    spikeMapper.SetInputConnection(glyph.GetOutputPort())
    spikeActor = vtk.vtkActor()
    spikeActor.SetMapper(spikeMapper)
    spikeActor2 = vtk.vtkActor()
    spikeActor2.SetMapper(spikeMapper)

    spikeActor.SetPosition(0, 0.7, 0)
    sphereActor.SetPosition(0, 0.7, 0)
    spikeActor2.SetPosition(0, -1.0, -10)
    sphereActor2.SetPosition(0, -1.0, -10)
    spikeActor2.SetScale(1.5, 1.5, 1.5)
    sphereActor2.SetScale(1.5, 1.5, 1.5)

    ren1.AddActor(sphereActor)
    ren1.AddActor(spikeActor)
    ren1.AddActor(sphereActor2)
    ren1.AddActor(spikeActor2)
    ren1.SetBackground(colors.GetColor3d("Bkg"))
    renWin.SetSize(300, 300)

    # Do the first render and then zoom in a little.
    renWin.Render()
    ren1.GetActiveCamera().SetFocalPoint(0, 0, 0.0)
    ren1.GetActiveCamera().Zoom(1.8)
    ren1.GetActiveCamera().SetFocalDisk(0.05)

    renWin.Render()

    iren.Start()


if __name__ == '__main__':
    main()
