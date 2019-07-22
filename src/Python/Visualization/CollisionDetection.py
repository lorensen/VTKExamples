#!/usr/bin/env python

import time

import vtk


def get_program_parameters():
    import argparse
    description = 'Collision detection.'
    epilogue = '''
This examples uses vtkCollisionDetectionFilter to find the intersection between a
 fixed (solid white) and moving (red wireframe) sphere.
The animation places the moving sphere some distance from the fixed sphere and
 moves the moving sphere until it contacts the fixed sphere.

Three collision modes are available and can be set as the first argument on the command line.

1. All contacts (0) finds all the contacting cell pairs with two points per collision.
2. First contact (1) quickly find the first contact point.
3. Half contacts (2) finds all the contacting cell pairs with one points per collision.

    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('contactMode', nargs='?', default=0, type=int, help='Contact mode 0 (default), 1, or 2.')
    args = parser.parse_args()
    return args.contactMode


def main():
    contactMode = get_program_parameters()

    # Define colors
    colors = vtk.vtkNamedColors()

    sphere0 = vtk.vtkSphereSource()
    sphere0.SetRadius(.29)
    sphere0.SetPhiResolution(31)
    sphere0.SetThetaResolution(31)
    sphere0.SetCenter(0.0, 0, 0)

    sphere1 = vtk.vtkSphereSource()
    sphere1.SetPhiResolution(30)
    sphere1.SetThetaResolution(30)
    sphere1.SetRadius(0.3)

    matrix1 = vtk.vtkMatrix4x4()
    transform0 = vtk.vtkTransform()

    collide = vtk.vtkCollisionDetectionFilter()
    collide.SetInputConnection(0, sphere0.GetOutputPort())
    collide.SetTransform(0, transform0)
    collide.SetInputConnection(1, sphere1.GetOutputPort())
    collide.SetMatrix(1, matrix1)
    collide.SetBoxTolerance(0.0)
    collide.SetCellTolerance(0.0)
    collide.SetNumberOfCellsPerNode(2)
    if contactMode == 0:
        collide.SetCollisionModeToAllContacts()
    elif contactMode == 1:
        collide.SetCollisionModeToFirstContact()
    else:
        collide.SetCollisionModeToHalfContacts()
    collide.GenerateScalarsOn()

    # Visualize
    mapper1 = vtk.vtkPolyDataMapper()
    mapper1.SetInputConnection(collide.GetOutputPort(0))
    mapper1.ScalarVisibilityOff()
    actor1 = vtk.vtkActor()
    actor1.SetMapper(mapper1)
    actor1.GetProperty().BackfaceCullingOn()
    actor1.SetUserTransform(transform0)
    actor1.GetProperty().SetDiffuseColor(colors.GetColor3d("Tomato"))
    actor1.GetProperty().SetRepresentationToWireframe()

    mapper2 = vtk.vtkPolyDataMapper()
    mapper2.SetInputConnection(collide.GetOutputPort(1))

    actor2 = vtk.vtkActor()
    actor2.SetMapper(mapper2)
    actor2.GetProperty().BackfaceCullingOn()
    actor2.SetUserMatrix(matrix1)

    mapper3 = vtk.vtkPolyDataMapper()
    mapper3.SetInputConnection(collide.GetContactsOutputPort())
    mapper3.SetResolveCoincidentTopologyToPolygonOffset()

    actor3 = vtk.vtkActor()
    actor3.SetMapper(mapper3)
    actor3.GetProperty().SetColor(colors.GetColor3d("Black"))
    actor3.GetProperty().SetLineWidth(3.0)

    txt = vtk.vtkTextActor()
    txt.GetTextProperty().SetFontSize(18)

    renderer = vtk.vtkRenderer()
    renderer.UseHiddenLineRemovalOn()
    renderer.AddActor(actor1)
    renderer.AddActor(actor2)
    renderer.AddActor(actor3)
    renderer.AddActor(txt)
    renderer.SetBackground(colors.GetColor3d("Gray"))
    renderer.UseHiddenLineRemovalOn()

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(640, 480)
    renderWindow.AddRenderer(renderer)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    # Move the first object
    numSteps = 100
    dx = 1.0 / float(numSteps) * 2.0
    transform0.Translate(-numSteps * dx - .3, 0.0, 0.0)
    renderWindow.Render()
    renderer.GetActiveCamera().Azimuth(-60)
    renderer.GetActiveCamera().Elevation(45)
    renderer.GetActiveCamera().Dolly(1.2)

    renderWindow.SetWindowName('CollisionDetection')
    renderWindow.Render()

    for i in range(0, numSteps):
        transform0.Translate(dx, 0.0, 0.0)
        renderer.ResetCameraClippingRange()
        s = '{:s}: Number of contact cells is {:d}'.format(collide.GetCollisionModeAsString(),
                                                           collide.GetNumberOfContacts())
        txt.SetInput(s)
        renderWindow.Render()
        if collide.GetNumberOfContacts() > 0:
            break
        # The total animation time is 3 seconds
        time.sleep(3.0 / numSteps)

    renderer.ResetCamera()
    renderWindow.Render()
    renderWindow.Render()
    interactor.Start()
    # In Field Data there will be an array named "ContactCells".
    # This array indexes contacting cells (e.g.) index 10 of array 0
    #  points to a cell (triangle) which contacts/intersects a cell
    #  at index 10 of array 1.
    # You can directly obtain these, see GetContactCells(int i)
    #  in the documentation.
    # print(collide.GetOutput(0))
    # print(collide.GetOutput(1))


if __name__ == '__main__':
    main()
