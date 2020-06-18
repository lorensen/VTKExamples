#!/usr/bin/env python

"""
    1. Create a cube and cone source.
    2. Render it with the cube in layer 0 and the cone in layer 1 of the render window.
    3. Interact with it.
    4. Notice that the cube and the cone are both visible and the layer 1 background is transparent.
    5. Pressing '0' on the keyboard will let you manipulate the objects in layer 0.
    6. Pressing '1' on the keyboard will let you manipulate the objects in layer 1.
"""

import vtk


def GenerateAndDisplayCubeAndSphere():
    colors = vtk.vtkNamedColors()

    cubeSource = vtk.vtkCubeSource()
    cubeSource.SetXLength(4.0)
    cubeSource.SetYLength(9.0)
    cubeSource.SetZLength(1.0)
    cubeSource.SetCenter(0.0, 0.0, 0.0)

    # Render the cube
    cubeMapper = vtk.vtkPolyDataMapper()
    cubeMapper.SetInputConnection(cubeSource.GetOutputPort())

    cubeActor = vtk.vtkActor()
    cubeActor.GetProperty().SetDiffuseColor(colors.GetColor3d("DarkGreen"))
    cubeActor.SetMapper(cubeMapper)

    coneSource = vtk.vtkConeSource()
    coneSource.SetCenter(0.0, 0.0, 0.0)
    coneSource.SetHeight(1.0)
    coneSource.SetRadius(0.25)
    coneSource.SetDirection(0.0, 1.0, 0.0)
    coneSource.SetResolution(60)
    coneSource.CappingOn()

    # Render the cone
    coneMapper = vtk.vtkPolyDataMapper()
    coneMapper.SetInputConnection(coneSource.GetOutputPort())

    coneActor = vtk.vtkActor()
    coneActor.GetProperty().SetDiffuseColor(colors.GetColor3d("DarkTurquoise"))
    # Make the cone slightly transparent for fun
    coneActor.GetProperty().SetOpacity(0.75)
    coneActor.SetMapper(coneMapper)

    # The renderers, render window and interactor
    renderers = list()
    renWin = vtk.vtkRenderWindow()
    for i in range(0, 2):
        renderers.append(vtk.vtkRenderer())
        renWin.AddRenderer(renderers[i])
    renWin.SetSize(800, 800)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Layer 0 - background not transparent
    renderers[0].SetBackground(colors.GetColor3d("Silver"))
    renderers[0].AddActor(cubeActor)
    renderers[0].SetLayer(0)
    # Layer 1 - the background is transparent
    #           so we only see the layer 0 background color
    renderers[1].AddActor(coneActor)
    renderers[1].SetLayer(1)
    renderers[1].SetBackground(colors.GetColor3d("MidnightBlue"))

    #  We have two layers
    renWin.SetNumberOfLayers(2)
    renWin.Render()
    renWin.SetWindowName('TransparentBackground')

    iren.AddObserver('KeyPressEvent', KeypressCallbackFunction)

    iren.Start()


def KeypressCallbackFunction(caller, ev):
    iren = caller
    renderers = iren.GetRenderWindow().GetRenderers()
    if renderers.GetNumberOfItems() < 2:
        print('We need at least two renderers, we have only', renderers.GetNumberOfItems())
        return
    renderers.InitTraversal()
    # Top item
    ren0 = renderers.GetNextItem()
    # Bottom item
    ren1 = renderers.GetNextItem()

    key = iren.GetKeySym()

    if key == '0':
        print('Pressed:', key)
        iren.GetRenderWindow().GetInteractor().GetInteractorStyle().SetDefaultRenderer(ren0)
        ren0.InteractiveOn()
        ren1.InteractiveOff()
    if key == '1':
        print('Pressed:', key)
        iren.GetRenderWindow().GetInteractor().GetInteractorStyle().SetDefaultRenderer(ren1)
        ren0.InteractiveOff()
        ren1.InteractiveOn()


def main():
    GenerateAndDisplayCubeAndSphere()


if __name__ == '__main__':
    main()
