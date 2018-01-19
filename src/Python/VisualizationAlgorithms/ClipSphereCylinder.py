#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Demonstrate the use of clipping on polygonal data
    #

    # create pipeline
    #
    plane = vtk.vtkPlaneSource()
    plane.SetXResolution(25)
    plane.SetYResolution(25)
    plane.SetOrigin(-1, -1, 0)
    plane.SetPoint1(1, -1, 0)
    plane.SetPoint2(-1, 1, 0)

    transformSphere = vtk.vtkTransform()
    transformSphere.Identity()
    transformSphere.Translate(0.4, -0.4, 0)
    transformSphere.Inverse()

    sphere = vtk.vtkSphere()
    sphere.SetTransform(transformSphere)
    sphere.SetRadius(.5)

    transformCylinder = vtk.vtkTransform()
    transformCylinder.Identity()
    transformCylinder.Translate(-0.4, 0.4, 0)
    transformCylinder.RotateZ(30)
    transformCylinder.RotateY(60)
    transformCylinder.RotateX(90)
    transformCylinder.Inverse()

    cylinder = vtk.vtkCylinder()
    cylinder.SetTransform(transformCylinder)
    cylinder.SetRadius(.3)

    boolean = vtk.vtkImplicitBoolean()
    boolean.AddFunction(cylinder)
    boolean.AddFunction(sphere)

    clipper = vtk.vtkClipPolyData()
    clipper.SetInputConnection(plane.GetOutputPort())
    clipper.SetClipFunction(boolean)
    clipper.GenerateClippedOutputOn()
    clipper.GenerateClipScalarsOn()
    clipper.SetValue(0)

    clipMapper = vtk.vtkPolyDataMapper()
    clipMapper.SetInputConnection(clipper.GetOutputPort())
    clipMapper.ScalarVisibilityOff()

    clipActor = vtk.vtkActor()
    clipActor.SetMapper(clipMapper)
    clipActor.GetProperty().SetDiffuseColor(colors.GetColor3d("Black"))
    clipActor.GetProperty().SetRepresentationToWireframe()

    clipInsideMapper = vtk.vtkPolyDataMapper()
    clipInsideMapper.SetInputData(clipper.GetClippedOutput())
    clipInsideMapper.ScalarVisibilityOff()

    clipInsideActor = vtk.vtkActor()
    clipInsideActor.SetMapper(clipInsideMapper)
    clipInsideActor.GetProperty().SetDiffuseColor(colors.GetColor3d("Dim_Gray"))

    # Create graphics stuff
    #
    ren1 = vtk.vtkRenderer()

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size
    #
    ren1.AddActor(clipActor)

    ren1.AddActor(clipInsideActor)
    ren1.SetBackground(colors.GetColor3d("Wheat"))
    ren1.ResetCamera()
    ren1.GetActiveCamera().Dolly(1.4)
    ren1.ResetCameraClippingRange()

    renWin.SetSize(640, 480)

    # render the image
    #
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
