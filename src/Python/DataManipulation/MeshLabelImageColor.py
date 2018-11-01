from __future__ import print_function

import vtk


def main():
    colors = vtk.vtkNamedColors()
    ifn, index = get_program_parameters()

    # Prepare to read the file.
    readerVolume = vtk.vtkMetaImageReader()
    readerVolume.SetFileName(ifn)
    readerVolume.Update()

    # Extract the region of interest.
    voi = vtk.vtkExtractVOI()
    if vtk.VTK_MAJOR_VERSION <= 5:
        voi.SetInput(readerVolume.GetOutput())
    else:
        voi.SetInputConnection(readerVolume.GetOutputPort())
    voi.SetVOI(0, 517, 0, 228, 0, 392)
    voi.SetSampleRate(1, 1, 1)
    voi.Update()  # Necessary for GetScalarRange().
    srange = voi.GetOutput().GetScalarRange()  # Needs Update() before!
    print("Range", srange)

    # Prepare surface generation.
    contour = vtk.vtkDiscreteMarchingCubes()  # For label images.
    if vtk.VTK_MAJOR_VERSION <= 5:
        contour.SetInput(voi.GetOutput())
    else:
        contour.SetInputConnection(voi.GetOutputPort())
    # contour.ComputeNormalsOn()

    print("Doing label", index)

    contour.SetValue(0, index)
    contour.Update()  # Needed for GetNumberOfPolys()!!!

    smoother = vtk.vtkWindowedSincPolyDataFilter()
    if vtk.VTK_MAJOR_VERSION <= 5:
        smoother.SetInput(contour.GetOutput())
    else:
        smoother.SetInputConnection(contour.GetOutputPort())
    smoother.SetNumberOfIterations(30)  # This has little effect on the error!
    # smoother.BoundarySmoothingOff()
    # smoother.FeatureEdgeSmoothingOff()
    # smoother.SetFeatureAngle(120.0)
    # smoother.SetPassBand(.001)        # This increases the error a lot!
    smoother.NonManifoldSmoothingOn()
    smoother.NormalizeCoordinatesOn()
    smoother.GenerateErrorScalarsOn()
    # smoother.GenerateErrorVectorsOn()
    smoother.Update()

    smoothed_polys = smoother.GetOutput()
    smoother_error = smoothed_polys.GetPointData().GetScalars()

    # Find min and max z.
    se_range = smoother_error.GetRange()
    print("Smoother error range:", se_range)
    minz = se_range[0]  # min(smoother_error)
    maxz = se_range[1]  # max(smoother_error)
    if maxz > 1:
        print("Big smoother error: min/max:", minz, maxz)
    # minz = 0.3  # This way colours of different particles are comparable.
    # maxz = 1
    minz = 0.3
    maxz = 0.6

    # Create the color map.
    colorLookupTable = vtk.vtkLookupTable()
    colorLookupTable.SetTableRange(minz, maxz)  # This does nothing, use mapper.SetScalarRange(minz, maxz).
    colorLookupTable.SetHueRange(2 / 3.0, 1)
    # colorLookupTable.SetSaturationRange(0, 0)
    # colorLookupTable.SetValueRange(1, 0)
    # colorLookupTable.SetNumberOfColors(256) #256 default
    colorLookupTable.Build()

    # Calculate cell normals.
    triangleCellNormals = vtk.vtkPolyDataNormals()
    if vtk.VTK_MAJOR_VERSION <= 5:
        triangleCellNormals.SetInput(smoothed_polys)
    else:
        triangleCellNormals.SetInputData(smoothed_polys)
    triangleCellNormals.ComputeCellNormalsOn()
    triangleCellNormals.ComputePointNormalsOff()
    triangleCellNormals.ConsistencyOn()
    triangleCellNormals.AutoOrientNormalsOn()
    triangleCellNormals.Update()  # Creates vtkPolyData.

    mapper = vtk.vtkPolyDataMapper()
    # mapper.SetInput(smoothed_polys) # This has no normals.
    if vtk.VTK_MAJOR_VERSION <= 5:
        mapper.SetInput(triangleCellNormals.GetOutput())  # This is better for vis;-)
    else:
        mapper.SetInputConnection(triangleCellNormals.GetOutputPort())  # this is better for vis;-)
    mapper.ScalarVisibilityOn()  # Show colour.
    mapper.SetScalarRange(minz, maxz)
    # mapper.SetScalarModeToUseCellData() # Contains the label eg. 31
    mapper.SetScalarModeToUsePointData()  # The smoother error relates to the verts.
    mapper.SetLookupTable(colorLookupTable)

    # Take the isosurface data and create geometry.
    actor = vtk.vtkLODActor()
    actor.SetNumberOfCloudPoints(100000)
    actor.SetMapper(mapper)

    # Create the renderer.
    ren = vtk.vtkRenderer()
    ren.SetBackground(colors.GetColor3d("DimGray"))
    ren.AddActor(actor)

    # Create a window for the renderer of size 600X600
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    renWin.SetSize(600, 600)

    # Set a user interface interactor for the render window.
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Start the initialization and rendering.
    iren.Initialize()
    renWin.Render()
    ren.GetActiveCamera().SetPosition(268.628410, 128.452157, 24.517175)
    ren.GetActiveCamera().SetFocalPoint(256.006912, 175.949646, 24.175843)
    ren.GetActiveCamera().SetViewUp(0.844464, 0.227883, 0.484716)
    ren.ResetCameraClippingRange()
    renWin.Render()

    iren.Start()


def get_program_parameters():
    import argparse
    description = 'MeshLabelImageColor.'
    epilogue = '''
        Takes a label image in Meta format and meshes a single label of it.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='labels.mhd')
    parser.add_argument('label', nargs='?', const=1, type=int, default=31, help='The label to use e.g 31')
    args = parser.parse_args()
    return args.filename, args.label


if __name__ == '__main__':
    main()
