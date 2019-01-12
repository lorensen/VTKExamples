from __future__ import print_function

import vtk
import vtk.util.numpy_support as VN

# Callback for when selection is changed

# This is global - fix later.
ren1 = vtk.vtkRenderer()


def selectionCallback(caller, eventId):
    hsel = vtk.vtkHardwareSelector()
    hsel.SetFieldAssociation(vtk.vtkDataObject.FIELD_ASSOCIATION_CELLS)
    hsel.SetRenderer(ren1)

    x, y = caller.GetRenderWindow().GetSize()

    # Create a small area around clicked point for selector area
    hsel.SetArea(0, 0, x, y)
    res = hsel.Select()

    numNodes = res.GetNumberOfNodes()
    if (numNodes < 1):
        print("No visible cells")
    else:
        sel_node = res.GetNode(0)
        print('Visible cell IDs: ', VN.vtk_to_numpy(sel_node.GetSelectionList()).tolist())


def main():
    colors = vtk.vtkNamedColors()

    sphere = vtk.vtkSphereSource()
    sphere.SetCenter(0, 0, 0)
    sphere.SetRadius(5.0)

    sphereMapper = vtk.vtkPolyDataMapper()
    sphereMapper.SetInputConnection(sphere.GetOutputPort())

    sphereActor = vtk.vtkActor()
    sphereActor.SetMapper(sphereMapper)
    sphereActor.GetProperty().SetColor(colors.GetColor3d('Bisque'))

    ren1.AddActor(sphereActor)
    ren1.SetBackground(0.1, 0.2, 0.4)
    ren1.GetActiveCamera().ParallelProjectionOn()
    ren1.SetBackground(colors.GetColor3d('Navy'))

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)
    renWin.SetSize(300, 300)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    iren.AddObserver("UserEvent", selectionCallback)

    style = vtk.vtkInteractorStyleTrackballCamera()
    iren.SetInteractorStyle(style)
    renWin.GetInteractor().SetInteractorStyle(style)

    ren1.ResetCamera()
    renWin.Render()

    iren.Initialize()
    iren.Start()


if __name__ == '__main__':
    main()
