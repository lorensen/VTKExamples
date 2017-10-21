from __future__ import print_function
import vtk
import vtk.util.numpy_support as VN

# Callback for when selection is changed


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


sphere = vtk.vtkSphereSource()
sphere.SetCenter(0, 0, 0)
sphere.SetRadius(5.0)

sphereMapper = vtk.vtkPolyDataMapper()
sphereMapper.SetInputConnection(sphere.GetOutputPort())

sphereActor = vtk.vtkActor()
sphereActor.SetMapper(sphereMapper)

ren1 = vtk.vtkRenderer()
ren1.AddActor(sphereActor)
ren1.SetBackground(0.1, 0.2, 0.4)
ren1.GetActiveCamera().ParallelProjectionOn()

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
