import vtk


def main():
    colors = vtk.vtkNamedColors()
    
    # Set the background color.
    colors.SetColor("bkg", [0.2, 0.3, 0.4, 1.0])

    # Create a sphere to deform
    sphere = vtk.vtkSphereSource()
    sphere.SetThetaResolution(51)
    sphere.SetPhiResolution(17)
    sphere.Update()
    bounds = sphere.GetOutput().GetBounds()

    # Create a filter to color the sphere
    ele = vtk.vtkElevationFilter()
    ele.SetInputConnection(sphere.GetOutputPort())
    ele.SetLowPoint(0,0,-0.5);
    ele.SetHighPoint(0,0,0.5);
    ele.SetLowPoint((bounds[1] + bounds[0]) / 2.0,
                    (bounds[3] + bounds[2]) / 2.0,
                    -bounds[5]);
    ele.SetHighPoint((bounds[1] + bounds[0]) / 2.0,
                     (bounds[3] + bounds[2]) / 2.0,
                     bounds[5]);
    ele.Update()

    # Create a mesh to deform the sphere
    pts = vtk.vtkPoints()
    pts.SetNumberOfPoints(6)
    pts.SetPoint(0,
                 bounds[0] - 0.1 * (bounds[1] - bounds[0]),
                 (bounds[3] + bounds[2]) / 2.0,
                 (bounds[5] + bounds[4]) / 2.0)
    pts.SetPoint(1,
                 bounds[1] + 0.1 * (bounds[1] - bounds[0]),
                 (bounds[3] + bounds[2]) / 2.0,
                 (bounds[5] + bounds[4]) / 2.0)
    pts.SetPoint(2,
                 (bounds[1] + bounds[0]) / 2.0,
                 bounds[2] - 0.1 * (bounds[3] - bounds[2]),
                 (bounds[5] + bounds[4]) / 2.0)
    pts.SetPoint(3,
                 (bounds[1] + bounds[0]) / 2.0,
                 bounds[3] + 0.1 * (bounds[3] - bounds[2]),
                 (bounds[5] + bounds[4]) / 2.0)
    pts.SetPoint(4,
                 (bounds[1] + bounds[0]) / 2.0,
                 (bounds[3] + bounds[2]) / 2.0,
                 bounds[4] - 0.1 * (bounds[5] - bounds[4]))
    pts.SetPoint(5,
                 (bounds[1] + bounds[0]) / 2.0,
                 (bounds[3] + bounds[2]) / 2.0,
                 bounds[5] + 0.1 * (bounds[5] - bounds[4]))
    tris = vtk.vtkCellArray()

    cells = [[2, 0, 4], [1, 2, 4], [3, 1, 4], [0, 3, 4], [0, 2, 5], [2, 1, 5], [1, 3, 5], [3, 0, 5]]

    for cell in cells:
        tris.InsertNextCell(3)
        for c in cell:
            tris.InsertCellPoint(c)

    pd = vtk.vtkPolyData()
    pd.SetPoints(pts)
    pd.SetPolys(tris)

    meshMapper = vtk.vtkPolyDataMapper()
    meshMapper.SetInputData(pd)
    meshActor = vtk.vtkActor()
    meshActor.SetMapper(meshMapper)
    meshActor.GetProperty().SetRepresentationToWireframe()
    meshActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    deform = vtk.vtkDeformPointSet()
    deform.SetInputData(ele.GetOutput())
    deform.SetControlMeshData(pd)
    deform.Update()

    controlPoint = pts.GetPoint(5)
    pts.SetPoint(5, controlPoint[0],
                 controlPoint[1],
                 bounds[5] + .8 * (bounds[5] - bounds[4]))
    pts.Modified()

    polyMapper = vtk.vtkPolyDataMapper()
    polyMapper.SetInputConnection(deform.GetOutputPort())
    polyActor = vtk.vtkActor()
    polyActor.SetMapper(polyMapper)

    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    renderer.AddActor(polyActor)
    renderer.AddActor(meshActor)

    renderer.GetActiveCamera().SetPosition(1,1,1)
    renderer.ResetCamera()
    renderer.SetBackground(colors.GetColor3d("bkg"))

    renWin.SetSize(300,300)
    renWin.Render()

    iren.Start()

if __name__ == '__main__':
    main()
