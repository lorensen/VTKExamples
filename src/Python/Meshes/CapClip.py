import vtk


def CapClip(filePath = None):
    # PolyData to process
    polyData = vtk.vtkPolyData()

    if filePath != None:
        reader = vtk.vtkXMLPolyDataReader()
        reader.SetFileName(filePath)
        reader.Update()
        polyData = reader.GetOutput()
        
    else:
        # Create a sphere
        sphereSource = vtk.vtkSphereSource()
        sphereSource.SetThetaResolution(20)
        sphereSource.SetPhiResolution(11)

        plane = vtk.vtkPlane()
        plane.SetOrigin(0, 0, 0)
        plane.SetNormal(1.0, -1.0, -1.0)

        clipper = vtk.vtkClipPolyData()
        clipper.SetInputConnection(sphereSource.GetOutputPort())
        clipper.SetClipFunction(plane)
        clipper.SetValue(0)
        clipper.Update()

        polyData = clipper.GetOutput()
        
    clipMapper = vtk.vtkDataSetMapper()
    if vtk.VTK_MAJOR_VERSION < 5:
        clipMapper.SetInput(polyData)
    else:
        clipMapper.SetInputData(polyData)

    clipActor = vtk.vtkActor()
    clipActor.SetMapper(clipMapper)
    clipActor.GetProperty().SetColor(1.0000, 0.3882, 0.2784)
    clipActor.GetProperty().SetInterpolationToFlat()

    # Now extract feature edges
    boundaryEdges = vtk.vtkFeatureEdges()
    if vtk.VTK_MAJOR_VERSION < 5:
        boundaryEdges.SetInput(polyData)
    else:
        boundaryEdges.SetInputData(polyData)

    boundaryEdges.BoundaryEdgesOn()
    boundaryEdges.FeatureEdgesOff()
    boundaryEdges.NonManifoldEdgesOff()
    boundaryEdges.ManifoldEdgesOff()

    boundaryStrips = vtk.vtkStripper()
    boundaryStrips.SetInputConnection(boundaryEdges.GetOutputPort())
    boundaryStrips.Update()

    # Change the polylines into polygons
    boundaryPoly = vtk.vtkPolyData()
    boundaryPoly.SetPoints(boundaryStrips.GetOutput().GetPoints())
    boundaryPoly.SetPolys(boundaryStrips.GetOutput().GetLines())

    boundaryMapper = vtk.vtkPolyDataMapper()
    if vtk.VTK_MAJOR_VERSION < 5:
        boundaryMapper.SetInput(boundaryPoly)
    else:
        boundaryMapper.SetInputData(boundaryPoly)

    boundaryActor = vtk.vtkActor()
    boundaryActor.SetMapper(boundaryMapper)
    boundaryActor.GetProperty().SetColor(0.8900, 0.8100, 0.3400)

    # create render window, renderer and interactor
    renderWindow = vtk.vtkRenderWindow()
    renderer = vtk.vtkRenderer()
    renderWindow.AddRenderer(renderer)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renderWindow)

    # set background color
    renderer.SetBackground(.2, .3, .4)

    # add our actor to the renderer
    renderer.AddActor(clipActor)
    renderer.AddActor(boundaryActor)

    # Generate an interesting view
    renderer.ResetCamera()
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)
    renderer.GetActiveCamera().Dolly(1.2)
    renderer.ResetCameraClippingRange()

    renderWindow.Render()
    iren.Start()


if __name__ == '__main__':
    CapClip()