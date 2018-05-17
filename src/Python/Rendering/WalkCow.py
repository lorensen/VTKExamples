#!/usr/local/bin/python

#  Translated from walkCow.tcl

import vtk

def walk_cow(file_name, figure):
    figure = abs(figure)
    if figure > 2:
        figure = 0

    colors = vtk.vtkNamedColors()
    # Set the background color.
    colors.SetColor("BkgColor1", [60, 93, 144, 255])
    colors.SetColor("BkgColor2", [26, 51, 102, 255])

    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # The cow pipeline.
    cow = vtk.vtkBYUReader()
    cow.SetGeometryFileName(file_name)
    cow.Update()

    cowMapper = vtk.vtkPolyDataMapper()
    cowMapper.SetInputConnection(cow.GetOutputPort())
    cowMapper.ScalarVisibilityOff()

    cowActor = vtk.vtkActor()
    cowActor.SetMapper(cowMapper)
    cowActor.GetProperty().SetColor(colors.GetColor3d("Wheat"))

    ren.AddActor(cowActor)

    # Axes pipeline.
    cowAxesSource = vtk.vtkAxes()
    cowAxesSource.SetScaleFactor(10.0)
    cowAxesSource.SetOrigin(0, 0, 0)

    cowAxesMapper = vtk.vtkPolyDataMapper()
    cowAxesMapper.SetInputConnection(cowAxesSource.GetOutputPort())

    cowAxes = vtk.vtkActor()
    cowAxes.SetMapper(cowAxesMapper)
    cowAxes.VisibilityOff()

    ren.AddActor(cowAxes)

    ren.SetBackground(colors.GetColor3d("BkgColor1"))
    renWin.SetSize(600, 480)

    iren.Initialize()
    cowAxes.VisibilityOn()
    renWin.Render()

    # Activate this if you want to see the Position and Focal point.
    # ren.GetActiveCamera().AddObserver('ModifiedEvent', CameraModifiedCallback)

    # These four walks use the same camera position.
    Rotate_X(cowActor, ren, renWin)
    Rotate_Y(cowActor, ren, renWin)
    Rotate_Z(cowActor, ren, renWin)
    Rotate_XY(cowActor, ren, renWin)

    ren.SetBackground(colors.GetColor3d("BkgColor2"))
    if figure == 1:
        Rotate_V_0(cowActor, ren, renWin)
    elif figure == 2:
        Rotate_V_V(cowActor, ren, renWin)
    else:
        Rotate_V_0(cowActor, ren, renWin)
        Rotate_V_V(cowActor, ren, renWin)
        # Walk() needs to go after Rotate_V_0() or Rotate_V_V().
        Walk(cowActor, ren, renWin)

    # Interact with data.
    renWin.EraseOff()
    iren.Start()

def main():
    file_name, figure = get_program_parameters()
    walk_cow(file_name, figure)


def get_program_parameters():
    import argparse
    description = 'Produce figures: 3-32, 3-33a, 3-33b from the VTK Textbook.'
    epilogue = '''
        It is a translation of the original WalkCow.tcl with a few additional enhancements.

        If the parameter figure is 0, 1 or 2 then these correspond to
        the VTK Textbook figures 3-32, 3-33a, 3-33b in that order.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='The file cow.g.')
    parser.add_argument('figure', default=0, type=int, nargs='?', help='The particular rotation that you want to view.')
    args = parser.parse_args()
    return args.filename, args.figure


"""
  These Rotate* and Walk functions create a scene where multiple
     views of the object exist.

    They all operate in a similar manner, namely:
    1) Accept vtkActor, vtkRenderer, vtkRenderWindow as parameters.
    2) Position the object.
    3) Position the observer with the focal point sent to the centre
        of the object.
    4) Render and set EraseOff() in the render window.
       Note that:
        EraseOff() has to be called after a Render() call
         to work in the desired way.
    5) Then rotate or Walk the object around the scene.
    6) Optionally write out the scene using Screenshot().
    6) Set EraseOff() in the render window.
    7) Reset the object position.

"""


def Rotate_X(cowActor, ren, renWin):
    # Six rotations about the x axis.
    ren.ResetCamera()
    ren.ResetCameraClippingRange()
    cowActor.SetOrientation(0.0, 0.0, 0.0)
    cowActor.SetOrigin(0.0, 0.0, 0)
    cowActor.SetPosition(0, 0, 0)
    # Get the focal point.
    bounds = cowActor.GetBounds()
    fp = [0.0] * 3
    for i in range(0, 3):
        fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0
    # This closely matches the original illustration.
    ren.GetActiveCamera().SetPosition(2, 25, 0)
    ren.GetActiveCamera().SetFocalPoint(fp)
    ren.GetActiveCamera().SetViewUp(0, 0, -1)
    ren.ResetCameraClippingRange()
    renWin.Render()
    renWin.Render()
    renWin.EraseOff()
    for idx in range(0, 6):
        cowActor.RotateX(60)
        renWin.Render()
        renWin.Render()
    # Screenshot("Fig3-31a.png", renWin)
    renWin.EraseOn()


def Rotate_Y(cowActor, ren, renWin):
    # Six rotations about the y axis.
    ren.ResetCamera()
    ren.ResetCameraClippingRange()
    cowActor.SetOrientation(0.0, 0.0, 0.0)
    cowActor.SetOrigin(0.0, 0.0, 0)
    cowActor.SetPosition(0, 0, 0)
    # Get the focal point.
    bounds = cowActor.GetBounds()
    fp = [0.0] * 3
    for i in range(0, 3):
        fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0
    # This closely matches the original illustration.
    ren.GetActiveCamera().SetPosition(2, 0, 25)
    ren.GetActiveCamera().SetFocalPoint(fp)
    ren.GetActiveCamera().SetViewUp(0, 1, 0)
    ren.ResetCameraClippingRange()
    renWin.Render()
    renWin.Render()
    renWin.EraseOff()
    for idx in range(0, 6):
        cowActor.RotateY(60)
        renWin.Render()
        renWin.Render()
    # Screenshot("Fig3-31b.png", renWin)
    renWin.EraseOn()


def Rotate_Z(cowActor, ren, renWin):
    # Six rotations about the z axis.
    ren.ResetCamera()
    ren.ResetCameraClippingRange()
    cowActor.SetOrientation(0.0, 0.0, 0.0)
    cowActor.SetOrigin(0.0, 0.0, 0)
    cowActor.SetPosition(0, 0, 0)
    # Get the focal point.
    bounds = cowActor.GetBounds()
    fp = [0.0] * 3
    for i in range(0, 3):
        fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0
    # This closely matches the original illustration.
    # ren.GetActiveCamera().SetPosition(2, 0, 25)
    ren.GetActiveCamera().SetPosition(2, 0, 25)
    ren.GetActiveCamera().SetFocalPoint(fp)
    ren.GetActiveCamera().SetViewUp(0, 1, 0)
    ren.ResetCameraClippingRange()
    renWin.Render()
    renWin.Render()
    renWin.EraseOff()
    for idx in range(0, 6):
        cowActor.RotateZ(60)
        renWin.Render()
        renWin.Render()
    # Screenshot("Fig3-31c.png", renWin)
    renWin.EraseOn()


def Rotate_XY(cowActor, ren, renWin):
    # First a rotation about the x axis, then six rotations about the y axis.
    ren.ResetCamera()
    ren.ResetCameraClippingRange()
    cowActor.SetOrientation(0.0, 0.0, 0.0)
    cowActor.SetOrigin(0.0, 0.0, 0)
    cowActor.SetPosition(0, 0, 0)
    # Get the focal point.
    bounds = cowActor.GetBounds()
    fp = [0.0] * 3
    for i in range(0, 3):
        fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0
    # This closely matches the original illustration.
    # ren.GetActiveCamera().SetPosition(2, 0, 24)
    ren.GetActiveCamera().SetPosition(2, 0, 25)
    ren.GetActiveCamera().SetFocalPoint(fp)
    ren.GetActiveCamera().SetViewUp(0, 1, 0)
    ren.ResetCameraClippingRange()
    renWin.Render()
    renWin.Render()
    renWin.EraseOff()
    cowActor.RotateX(60)
    for idx in range(0, 6):
        cowActor.RotateY(60)
        renWin.Render()
        renWin.Render()
    cowActor.RotateX(-60)
    # Screenshot("Fig3-31d.png", renWin)
    renWin.EraseOn()


def Rotate_V_0(cowActor, ren, renWin):
    # The cow rotating about a vector passing through her nose.
    # With the origin at (0, 0, 0).
    ren.ResetCamera()
    ren.ResetCameraClippingRange()
    cowActor.SetOrientation(0.0, 0.0, 0.0)
    cowActor.SetOrigin(0.0, 0.0, 0)
    cowActor.SetPosition(0, 0, 0)
    # Get the focal point.
    bounds = cowActor.GetBounds()
    fp = [0.0] * 3
    for i in range(0, 3):
        fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0
    cowPos = vtk.vtkTransform()
    cowPos.Identity()
    cowPos.SetMatrix(cowActor.GetMatrix())
    cowTransform = vtk.vtkTransform()
    cowTransform.Identity()
    cowActor.SetUserMatrix(cowTransform.GetMatrix())
    # This closely matches the original illustration.
    ren.GetActiveCamera().SetPosition(16, 9, -12)
    ren.GetActiveCamera().SetFocalPoint(fp)
    ren.ResetCameraClippingRange()
    renWin.Render()
    renWin.Render()
    renWin.EraseOff()
    for idx in range(0, 6):
        cowActor.RotateWXYZ(60, 2.19574, -1.42455, -0.0331036)
        renWin.Render()
        renWin.Render()
    # Screenshot("Fig3-33a.png", renWin)
    renWin.EraseOn()
    # Put the cow back on the origin.
    # for idx in range(0, 6):
    #     cowActor.RotateWXYZ(-60, 2.19574, -1.42455, -0.0331036)
    # cowActor.SetUserMatrix(cowPos.GetMatrix())
    # ren.GetActiveCamera().SetPosition(0, 0, 1)
    # ren.GetActiveCamera().SetViewUp(0, 1, 0)
    # ren.ResetCamera()


def Rotate_V_V(cowActor, ren, renWin):
    # The cow rotating about a vector passing through her nose.
    # With the origin at (6.11414, 1.27386, 0.015175).
    ren.ResetCamera()
    ren.ResetCameraClippingRange()
    cowActor.SetOrientation(0.0, 0.0, 0.0)
    cowActor.SetOrigin(0.0, 0.0, 0)
    cowActor.SetPosition(0, 0, 0)
    # Get the focal point.
    bounds = cowActor.GetBounds()
    fp = [0.0] * 3
    for i in range(0, 3):
        fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0
    cowPos = vtk.vtkTransform()
    cowPos.Identity()
    cowPos.SetMatrix(cowActor.GetMatrix())
    cowActor.SetOrigin(6.11414, 1.27386, 0.015175)  # The cow's nose
    cowTransform = vtk.vtkTransform()
    cowTransform.Identity()
    cowActor.SetUserMatrix(cowTransform.GetMatrix())
    # This closely matches the original illustration.
    ren.GetActiveCamera().SetPosition(31, 23, -21)
    ren.GetActiveCamera().SetFocalPoint(fp)
    ren.ResetCameraClippingRange()
    renWin.Render()
    renWin.Render()
    renWin.EraseOff()
    for idx in range(0, 6):
        cowActor.RotateWXYZ(60, 2.19574, -1.42455, -0.0331036)
        renWin.Render()
        renWin.Render()
    # Screenshot("Fig3-33b.png", renWin)
    renWin.EraseOn()
    # Put the cow back on the origin.
    # for idx in range(0, 6):
    #     cowActor.RotateWXYZ(-60, 2.19574, -1.42455, -0.0331036)
    # cowActor.SetUserMatrix(cowPos.GetMatrix())


def Walk(cowActor, ren, renWin):
    # The cow "walking" around the global origin
    cowPos = vtk.vtkTransform()
    cowPos.Identity()
    cowPos.SetMatrix(cowActor.GetMatrix())
    cowActor.SetOrientation(0.0, 0.0, 0.0)
    cowActor.SetOrigin(0.0, 0.0, 0.0)
    # Get the focal point.
    bounds = cowActor.GetBounds()
    fp = [0.0] * 3
    for i in range(0, 3):
        fp[i] = (bounds[i * 2 + 1] + bounds[i * 2]) / 2.0
    cowTransform = vtk.vtkTransform()
    cowTransform.Identity()
    cowTransform.Translate(0, 0, 5)
    cowActor.SetUserMatrix(cowTransform.GetMatrix())
    # This closely matches the original illustration.
    ren.GetActiveCamera().SetPosition(1, 24, 16)
    ren.GetActiveCamera().SetFocalPoint(fp)
    ren.GetActiveCamera().SetViewUp(0, 0, -1)
    ren.ResetCameraClippingRange()
    renWin.Render()
    renWin.Render()
    renWin.EraseOff()
    for idx in range(1, 7):
        cowTransform.Identity()
        cowTransform.RotateY(idx * 60)
        cowTransform.Translate(0, 0, 5)
        cowActor.SetUserMatrix(cowTransform.GetMatrix())
        renWin.Render()
        renWin.Render()
    # Screenshot("Fig3-32.png", renWin)
    renWin.EraseOn()
    # Walkies are over, put the cow back on the origin.
    # cowActor.SetUserMatrix(cowPos.GetMatrix())


def CameraModifiedCallback(caller, ev):
    """
     Used to estimate positions similar to the book illustrations.
    :param caller:
    :return:
    """
    print(caller.GetClassName(), "modified")
    # Print the interesting stuff.
    print("\tPosition: ",
          caller.GetPosition()[0], ", ",
          caller.GetPosition()[1], ", ",
          caller.GetPosition()[2])
    print("\tFocal point: ",
          caller.GetFocalPoint()[0], ", ",
          caller.GetFocalPoint()[1], ", ",
          caller.GetFocalPoint()[2])


def Screenshot(fileName, renWin):
    """
    Save a screenshot.
    :param fileName:
    :param renWin:
    :return:
    """
    windowToImageFilter = vtk.vtkWindowToImageFilter()
    windowToImageFilter.SetInput(renWin)
    windowToImageFilter.SetScale(1)  # image quality
    # We are not recording the alpha (transparency) channel.
    # windowToImageFilter.SetInputBufferTypeToRGBA()
    windowToImageFilter.SetInputBufferTypeToRGB()
    # Read from the front buffer.
    windowToImageFilter.ReadFrontBufferOff()
    windowToImageFilter.Update()

    writer = vtk.vtkPNGWriter()
    writer.SetFileName(fileName)
    writer.SetInputConnection(windowToImageFilter.GetOutputPort())
    writer.Write()


if __name__ == '__main__':
    main()
