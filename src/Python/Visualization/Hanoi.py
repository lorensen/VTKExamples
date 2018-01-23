#!/usr/bin/env python

#  Translated from Hanoi.cxx.

import vtk


class GV(object):
    """
    Used to store global variables.
    """

    def __init__(self, numberOfPucks=5, numberOfSteps=5, puckResolution=48, configuration=0):
        self.numberOfPucks = numberOfPucks
        self.numberOfSteps = numberOfSteps
        self.puckResolution = puckResolution
        self.configuration = configuration
        self.gotFigure2 = False  # Used to bail out of recursion if configuration == 2.
        self.L = 1.0  # Puck height.
        self.H = 1.1 * self.numberOfPucks * self.L  # Peg height.
        self.R = 0.5  # Peg radius.
        self.rMin = 4.0 * self.R  # The minimum allowable radius of disks.
        self.rMax = 12.0 * self.R  # The maximum allowable radius of disks
        self.D = 1.1 * 1.25 * self.rMax  # The distance between the pegs.
        self.numberOfMoves = 0

    def update(self, numberOfPucks, numberOfSteps, puckResolution, configuration):
        self.numberOfPucks = numberOfPucks
        self.numberOfSteps = numberOfSteps
        self.puckResolution = puckResolution
        self.configuration = configuration
        self.H = 1.1 * self.numberOfPucks * self.L  # Peg height.


# Globals
gv = GV()
renWin = vtk.vtkRenderWindow()
"""
   For pegStack we use a list of lists where the sublists correspond to the
      source, target and helper pegs.
   Python lists can be used as a stack since they have append() (corresponding
      to push()) and pop().
"""
pegStack = [[], [], []]


def hanoi():

    colors = vtk.vtkNamedColors()

    # Create the renderer and render window interactor.
    ren = vtk.vtkRenderer()
    renWin.AddRenderer(ren)
    renWin.SetSize(1200, 750)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    ren.SetBackground(colors.GetColor3d("PapayaWhip"))

    camera = vtk.vtkCamera()
    camera.SetPosition(41.0433, 27.9637, 30.442)
    camera.SetFocalPoint(11.5603, -1.51931, 0.95899)
    camera.SetClippingRange(18.9599, 91.6042)
    camera.SetViewUp(0, 1, 0)

    ren.SetActiveCamera(camera)

    # Create geometry: table, pegs, and pucks.
    pegGeometry = vtk.vtkCylinderSource()
    pegGeometry.SetResolution(8)
    pegMapper = vtk.vtkPolyDataMapper()
    pegMapper.SetInputConnection(pegGeometry.GetOutputPort())

    puckGeometry = vtk.vtkCylinderSource()
    puckGeometry.SetResolution(gv.puckResolution)
    puckMapper = vtk.vtkPolyDataMapper()
    puckMapper.SetInputConnection(puckGeometry.GetOutputPort())

    tableGeometry = vtk.vtkPlaneSource()
    tableGeometry.SetResolution(10, 10)
    tableMapper = vtk.vtkPolyDataMapper()
    tableMapper.SetInputConnection(tableGeometry.GetOutputPort())

    # Create the actors: table top, pegs, and pucks
    # The table
    table = vtk.vtkActor()
    ren.AddActor(table)
    table.SetMapper(tableMapper)
    # table.GetProperty().SetColor(0.9569, 0.6431, 0.3765)
    table.GetProperty().SetColor(colors.GetColor3d("SaddleBrown"))
    table.AddPosition(gv.D, 0, 0)
    table.SetScale(4 * gv.D, 2 * gv.D, 3 * gv.D)
    table.RotateX(90)

    # The pegs (using cylinder geometry).  Note that the pegs have to translated
    # in the  y-direction because the cylinder is centered about the origin.
    gv.H = 1.1 * gv.numberOfPucks * gv.L
    peg = list()
    for i in range(0, 3):
        peg.append(vtk.vtkActor())
        ren.AddActor(peg[i])
        peg[i].SetMapper(pegMapper)
        # peg[i].GetProperty().SetColor(1, 1, 1)
        peg[i].GetProperty().SetColor(colors.GetColor3d("Lavender"))
        peg[i].AddPosition(i * gv.D, gv.H / 2, 0)
        peg[i].SetScale(1, gv.H, 1)

    # The pucks (using cylinder geometry). Always loaded on peg# 0.
    puck = list()
    randomSequence = vtk.vtkMinimalStandardRandomSequence()
    randomSequence.SetSeed(1)
    for i in range(0, gv.numberOfPucks):
        puck.append(vtk.vtkActor())
        puck[i].SetMapper(puckMapper)
        color = [0, 0, 0]
        for j in range(0, 3):
            color[j] = randomSequence.GetValue()
            randomSequence.Next()
        puck[i].GetProperty().SetColor(*color)
        puck[i].AddPosition(0, i * gv.L + gv.L / 2, 0)
        scale = gv.rMax - i * (gv.rMax - gv.rMin) / (gv.numberOfPucks - 1)
        puck[i].SetScale(scale, 1, scale)
        ren.AddActor(puck[i])
        pegStack[0].append(puck[i])

    # Reset the camera to view all actors.
    renWin.Render()
    renWin.SetWindowName("Towers of Hanoi")

    if gv.configuration == 3:
        WriteImage("hanoi0.png", renWin, rgba=False)

    if gv.configuration != 1:
        # Begin recursion.
        Hanoi(gv.numberOfPucks - 1, 0, 2, 1)
        Hanoi(1, 0, 1, 2)
        if not gv.gotFigure2:
            Hanoi(gv.numberOfPucks - 1, 2, 1, 0)

            renWin.Render()
            if gv.configuration == 3:
                WriteImage("hanoi2.png", renWin, rgba=False)
        # Report output.
        s = 'Number of moves: {:d}\nPolygons rendered each frame: {:d}\nTotal number of frames: {:d}'
        print(s.format(gv.numberOfMoves, 3 * 8 + 1 + gv.numberOfPucks * (2 + gv.puckResolution),
                       gv.numberOfMoves * 3 * gv.numberOfSteps))

    iren.AddObserver('EndInteractionEvent', OrientationObserver(ren.GetActiveCamera()))

    # Render the image.
    iren.Initialize()
    iren.Start()

def main():
    maxPucks = 20
    if not verify_parameters(maxPucks):
        return
    hanoi()


def get_program_parameters():
    import argparse
    description = 'Towers of Hanoi. .'
    epilogue = '''
Where:  -p specifies the number of pucks.
        -s specifies the number of steps.
        -r specifies the puck resolution.
        -c specifies configuration.
            0 final configuration.
            1 initial configuration.
            2 intermediate configuration.
            3 final configuration and save images
Defaults:  -p 5 -s 5 -r 48 -c 0
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--numberOfPucks', '-p', default=5, type=int, nargs='?', help='The number of pucks.')
    parser.add_argument('--numberOfSteps', '-s', default=5, type=int, nargs='?', help='The number of steps.')
    parser.add_argument('--puckResolution', '-r', default=48, type=int, nargs='?', help='The puck resolution.')
    parser.add_argument('--configuration', '-c', default=0, type=int, nargs='?', help='The configuration.')
    args = parser.parse_args()
    return args.numberOfPucks, args.numberOfSteps, args.puckResolution, args.configuration


def verify_parameters(maxPucks):
    numberOfPucks, numberOfSteps, puckResolution, configuration = get_program_parameters()
    numberOfPucks = abs(numberOfPucks)
    numberOfSteps = abs(numberOfSteps)
    puckResolution = abs(puckResolution)
    configuration = abs(configuration)
    check = True
    if numberOfPucks < 2:
        print('Please use more pucks!')
        check = False
    if numberOfPucks > maxPucks:
        print('Too many pucks specified! Maximum is', maxPucks)
        check = False
    if numberOfSteps < 3:
        print('Please use more steps!')
        check = False
    if configuration > 3:
        print('0 >= configuration <= 3')
        check = False
    if check:
        gv.update(numberOfPucks, numberOfSteps, puckResolution, configuration)
    return check


def MovePuck(peg1, peg2):
    """
    This routine is responsible for moving pucks from peg1 to peg2.
    :param peg1: Initial peg.
    :param peg2: Final peg.
    :return:
    """
    gv.numberOfMoves += 1

    # Get the actor to move
    movingActor = pegStack[peg1].pop()

    # Get the distance to move up.
    distance = (gv.H - (gv.L * (len(pegStack[peg1]) - 1)) + gv.rMax) / gv.numberOfSteps

    for i in range(0, gv.numberOfSteps):
        movingActor.AddPosition(0, distance, 0)
        renWin.Render()

    # Get the distance to move across
    distance = (peg2 - peg1) * gv.D / gv.numberOfSteps
    flipAngle = 180.0 / gv.numberOfSteps
    for i in range(0, gv.numberOfSteps):
        movingActor.AddPosition(distance, 0, 0)
        movingActor.RotateX(flipAngle)
        renWin.Render()
        if gv.numberOfMoves == 13 and i == 3:  # for making book image
            if gv.configuration == 3 or gv.configuration == 2:
                cam = renWin.GetRenderers().GetFirstRenderer().GetActiveCamera()
                camera1 = vtk.vtkCamera()
                camera1.SetPosition(54.7263, 41.6467, 44.125)
                camera1.SetFocalPoint(11.5603, -1.51931, 0.95899)
                camera1.SetClippingRange(42.4226, 115.659)
                camera1.SetViewUp(0, 1, 0)
                renWin.GetRenderers().GetFirstRenderer().SetActiveCamera(camera1)
                renWin.Render()
                if gv.configuration == 3:
                    WriteImage("hanoi1.png", renWin, rgba=False)
                if gv.configuration == 2:
                    gv.gotFigure2 = True
                    break
                renWin.GetRenderers().GetFirstRenderer().SetActiveCamera(cam)
                renWin.Render()
    if gv.gotFigure2:
        pegStack[peg2].append(movingActor)
        return

    # Get the distance to move down.
    distance = ((gv.L * (len(pegStack[peg2]) - 1)) - gv.H - gv.rMax) / gv.numberOfSteps

    for i in range(0, gv.numberOfSteps):
        movingActor.AddPosition(0, distance, 0)
        renWin.Render()
    pegStack[peg2].append(movingActor)


def Hanoi(n, peg1, peg2, peg3):
    """
    Tower of Hanoi.
    :param n: Number of disks.
    :param peg1: Source
    :param peg2: Target
    :param peg3: Helper
    :return:
    """
    # If gotFigure2 is true, we break out of the recursion.
    if gv.gotFigure2:
        return
    if n != 1:
        Hanoi(n - 1, peg1, peg3, peg2)
        if gv.gotFigure2:
            return
        Hanoi(1, peg1, peg2, peg3)
        Hanoi(n - 1, peg3, peg2, peg1)
    else:
        MovePuck(peg1, peg2)


class OrientationObserver(object):
    def __init__(self, cam):
        self.cam = cam

    def __call__(self, caller, ev):
        # Just do this to demonstrate who called callback and the event that triggered it.
        print(caller.GetClassName(), "Event Id:", ev)
        # Now print the camera orientation.
        CameraOrientation(self.cam)


def CameraOrientation(cam):
    fmt1 = "{:>15s}"
    fmt2 = "{:9.6g}"
    print(fmt1.format("Position:"), ', '.join(map(fmt2.format, cam.GetPosition())))
    print(fmt1.format("Focal point:"), ', '.join(map(fmt2.format, cam.GetFocalPoint())))
    print(fmt1.format("Clipping range:"), ', '.join(map(fmt2.format, cam.GetClippingRange())))
    print(fmt1.format("View up:"), ', '.join(map(fmt2.format, cam.GetViewUp())))
    print(fmt1.format("Distance:"), fmt2.format(cam.GetDistance()))


def WriteImage(fileName, renWin1, rgba=True):
    """
    Write the render window view to an image file.

    Image types supported are:
     BMP, JPEG, PNM, PNG, PostScript, TIFF.
    The default parameters are used for all writers, change as needed.

    :param fileName: The file name, if no extension then PNG is assumed.
    :param renWin1: The render window.
    :param rgba: Used to set the buffer type.
    :return:
    """

    import os

    if fileName:
        # Select the writer to use.
        path, ext = os.path.splitext(fileName)
        ext = ext.lower()
        if not ext:
            ext = '.png'
            fileName = fileName + ext
        if ext == '.bmp':
            writer = vtk.vtkBMPWriter()
        elif ext == '.jpg':
            writer = vtk.vtkJPEGWriter()
        elif ext == '.pnm':
            writer = vtk.vtkPNMWriter()
        elif ext == '.ps':
            if rgba:
                rgba = False
            writer = vtk.vtkPostScriptWriter()
        elif ext == '.tiff':
            writer = vtk.vtkTIFFWriter()
        else:
            writer = vtk.vtkPNGWriter()

        windowto_image_filter = vtk.vtkWindowToImageFilter()
        windowto_image_filter.SetInput(renWin1)
        windowto_image_filter.SetScale(1)  # image quality
        if rgba:
            windowto_image_filter.SetInputBufferTypeToRGBA()
        else:
            windowto_image_filter.SetInputBufferTypeToRGB()
            # Read from the front buffer.
            windowto_image_filter.ReadFrontBufferOff()
            windowto_image_filter.Update()

        writer.SetFileName(fileName)
        writer.SetInputConnection(windowto_image_filter.GetOutputPort())
        writer.Write()
    else:
        raise RuntimeError('Need a filename.')


if __name__ == '__main__':
    main()
