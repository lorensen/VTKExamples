#!/usr/bin/env python

"""
"""

import vtk

positions = [
    [-4, 4, 0], [-2, 4, 0], [0, 4, 0], [2, 4, 0],
    [-4, 2, 0], [-2, 2, 0], [0, 2, 0], [2, 2, 0],
    [-4, 0, 0], [-2, 0, 0], [0, 0, 0], [2, 0, 0],
    [-4, -2, 0], [-2, -2, 0], [0, -2, 0], [2, -2, 0]
]

solid = [255, 255]
clear = [255, 0]
edge = [0, 255]


def main():
    colors = vtk.vtkNamedColors()

    renWin = vtk.vtkRenderWindow()

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    aren = vtk.vtkRenderer()

    # define two elliptical cylinders
    quadric1 = vtk.vtkQuadric()
    quadric1.SetCoefficients(1, 2, 0, 0, 0, 0, 0, 0, 0, -.07)

    quadric2 = vtk.vtkQuadric()
    quadric2.SetCoefficients(2, 1, 0, 0, 0, 0, 0, 0, 0, -.07)

    # Create a sphere for all to use.
    aSphere = vtk.vtkSphereSource()
    aSphere.SetPhiResolution(21)
    aSphere.SetThetaResolution(21)

    # Create texture coordinates for all.
    tcoords = vtk.vtkImplicitTextureCoords()
    tcoords.SetInputConnection(aSphere.GetOutputPort())
    tcoords.SetRFunction(quadric1)
    tcoords.SetSFunction(quadric2)

    aMapper = vtk.vtkDataSetMapper()
    aMapper.SetInputConnection(tcoords.GetOutputPort())

    # Create a mapper, sphere and texture map for each case.
    for i in range(0, 16):
        aBoolean = MakeBooleanTexture(i, 64, 0)

        aTexture2 = vtk.vtkTexture()
        aTexture2.SetInputConnection(aBoolean.GetOutputPort())
        aTexture2.InterpolateOff()
        aTexture2.RepeatOff()

        anActor2 = vtk.vtkActor()

        anActor2.SetMapper(aMapper)
        anActor2.SetTexture(aTexture2)
        anActor2.SetPosition(positions[i])
        anActor2.SetScale(2.0, 2.0, 2.0)
        aren.AddActor(anActor2)

    aren.SetBackground(colors.GetColor3d("SlateGray"))
    renWin.SetSize(500, 500)
    renWin.AddRenderer(aren)

    # Interact with the data.
    renWin.Render()

    iren.Start()


def MakeBooleanTexture(caseNumber, resolution, thickness):
    booleanTexture = vtk.vtkBooleanTexture()

    booleanTexture.SetXSize(resolution)
    booleanTexture.SetYSize(resolution)
    booleanTexture.SetThickness(thickness)

    if caseNumber == 0:
        booleanTexture.SetInIn(solid)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(solid)
        booleanTexture.SetOnIn(solid)
        booleanTexture.SetOnOut(solid)
        booleanTexture.SetInOn(solid)
        booleanTexture.SetOutOn(solid)
    elif caseNumber == 1:  # cut inside 1
        booleanTexture.SetInIn(clear)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(solid)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(solid)
    elif caseNumber == 2:  # cut outside 1
        booleanTexture.SetInIn(solid)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(solid)
        booleanTexture.SetInOn(solid)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 3:  # cut all 1
        booleanTexture.SetInIn(clear)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(clear)
        booleanTexture.SetOnOut(solid)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 4:
        booleanTexture.SetInIn(solid)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(solid)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(solid)
    elif caseNumber == 5:
        booleanTexture.SetInIn(clear)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(clear)
        booleanTexture.SetOutOn(solid)
    elif caseNumber == 6:
        booleanTexture.SetInIn(solid)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 7:
        booleanTexture.SetInIn(clear)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutOut(solid)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(clear)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(clear)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 8:
        booleanTexture.SetInIn(solid)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(solid)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(solid)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 9:
        booleanTexture.SetInIn(clear)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 10:
        booleanTexture.SetInIn(solid)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(solid)
        booleanTexture.SetOutOn(clear)
    elif caseNumber == 11:
        booleanTexture.SetInIn(clear)
        booleanTexture.SetInOut(solid)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(clear)
        booleanTexture.SetOnOut(edge)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(clear)
    elif caseNumber == 12:
        booleanTexture.SetInIn(solid)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(solid)
        booleanTexture.SetOnOut(clear)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 13:
        booleanTexture.SetInIn(clear)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutIn(solid)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(clear)
        booleanTexture.SetInOn(clear)
        booleanTexture.SetOutOn(edge)
    elif caseNumber == 14:
        booleanTexture.SetInIn(solid)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(edge)
        booleanTexture.SetOnIn(edge)
        booleanTexture.SetOnOut(clear)
        booleanTexture.SetInOn(edge)
        booleanTexture.SetOutOn(clear)
    else:  # caseNumber ==  15:
        booleanTexture.SetInIn(clear)
        booleanTexture.SetInOut(clear)
        booleanTexture.SetOutIn(clear)
        booleanTexture.SetOutOut(clear)
        booleanTexture.SetOnOn(clear)
        booleanTexture.SetOnIn(clear)
        booleanTexture.SetOnOut(clear)
        booleanTexture.SetInOn(clear)
        booleanTexture.SetOutOn(clear)

    return booleanTexture


if __name__ == '__main__':
    main()
