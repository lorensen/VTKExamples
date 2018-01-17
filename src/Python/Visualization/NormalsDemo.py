#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    polyData = ReadPolyData(fileName)

    # A renderer.
    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d("White"))

    # Create background colors for each viewport.
    backgroundColors = list()
    backgroundColors.append(colors.GetColor3d("Cornsilk"))
    backgroundColors.append(colors.GetColor3d("NavajoWhite"))
    backgroundColors.append(colors.GetColor3d("Tan"))

    # Create a renderer for each view port.
    ren = list()
    ren.append(vtk.vtkRenderer())
    ren.append(vtk.vtkRenderer())
    ren.append(vtk.vtkRenderer())
    ren[0].SetViewport(0, 0, 1.0 / 3.0, 1)  # Input
    ren[1].SetViewport(1.0 / 3.0, 0, 2.0 / 3.0, 1)  # Normals (no split)
    ren[2].SetViewport(2.0 / 3.0, 0, 1, 1)  # Normals (split)

    # Shared camera.
    camera = vtk.vtkCamera()

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputData(polyData)
    normals.SetFeatureAngle(30.0)
    for i in range(0, 3):
        if i == 0:
            normals.ComputePointNormalsOff()
        elif i == 1:
            normals.ComputePointNormalsOn()
            normals.SplittingOff()
        else:
            normals.ComputePointNormalsOn()
            normals.SplittingOn()

        normals.Update()

        normalsPolyData = vtk.vtkPolyData()
        normalsPolyData.DeepCopy(normals.GetOutput())

        # mapper
        mapper = vtk.vtkPolyDataMapper()
        mapper.SetInputData(normalsPolyData)
        mapper.ScalarVisibilityOff()

        actor = vtk.vtkActor()
        actor.SetMapper(mapper)
        actor.GetProperty().SetDiffuseColor(colors.GetColor3d("Peacock"))
        actor.GetProperty().SetDiffuse(.7)
        actor.GetProperty().SetSpecularPower(20)
        actor.GetProperty().SetSpecular(.5)

        # add the actor
        ren[i].SetBackground(backgroundColors[i])
        ren[i].SetActiveCamera(camera)
        ren[i].AddActor(actor)

    # Render window.
    renwin = vtk.vtkRenderWindow()
    renwin.AddRenderer(ren[0])
    renwin.AddRenderer(ren[1])
    renwin.AddRenderer(ren[2])

    # An interactor.
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renwin)

    renwin.SetSize(900, 300)
    ren[0].GetActiveCamera().SetFocalPoint(0, 0, 0)
    ren[0].GetActiveCamera().SetPosition(1, 0, 0)
    ren[0].GetActiveCamera().SetViewUp(0, 0, -1)
    ren[0].ResetCamera()

    ren[0].GetActiveCamera().Azimuth(120)
    ren[0].GetActiveCamera().Elevation(30)
    ren[0].GetActiveCamera().Dolly(1.1)
    ren[0].ResetCameraClippingRange()

    renwin.Render()
    ren[0].ResetCamera()
    renwin.Render()

    # Start.
    interactor.Initialize()
    interactor.Start()


def get_program_parameters():
    import argparse
    description = 'Surface normal generation.'
    epilogue = '''
    (a) Faceted model without normals.
    (b) Polygons must be consistently oriented to accurately compute normals.
    (c) Sharp edges are poorly represented using shared normals as shown on the corners of this model.
    (d) Normal generation with sharp edges split.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='42400-IDGH.stl.')
    args = parser.parse_args()
    return args.filename1


def ReadPolyData(file_name):
    import os
    path, extension = os.path.splitext(file_name)
    extension = extension.lower()
    if extension == ".ply":
        reader = vtk.vtkPLYReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".vtp":
        reader = vtk.vtkXMLpoly_dataReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".obj":
        reader = vtk.vtkOBJReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".stl":
        reader = vtk.vtkSTLReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".vtk":
        reader = vtk.vtkpoly_dataReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".g":
        reader = vtk.vtkBYUReader()
        reader.SetGeometryFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    else:
        # Return a None if the extension is unknown.
        poly_data = None
    return poly_data


if __name__ == '__main__':
    main()
