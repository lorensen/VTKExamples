#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # hidden sphere
    sphere1 = vtk.vtkSphereSource()
    sphere1.SetRadius(0.5)

    innerMapper = vtk.vtkPolyDataMapper()
    innerMapper.SetInputConnection(sphere1.GetOutputPort())

    innerSphere = vtk.vtkActor()
    innerSphere.SetMapper(innerMapper)
    innerSphere.GetProperty().SetColor(colors.GetColor3d("BlanchedAlmond"))

    # sphere to texture
    sphere2 = vtk.vtkSphereSource()
    sphere2.SetRadius(1.0)
    sphere2.SetPhiResolution(21)
    sphere2.SetThetaResolution(21)

    pts = [0.0] * 6
    points = vtk.vtkPoints()
    points.SetNumberOfPoints(2)
    points.SetPoint(0, pts[:3])
    points.SetPoint(1, pts[3:])

    nrms = [0.0] * 6
    nrms[0] = 1.0
    nrms[4] = 1.0
    normals = vtk.vtkDoubleArray()
    normals.SetNumberOfComponents(3)
    normals.SetNumberOfTuples(2)
    normals.SetTuple(0, nrms[:3])
    normals.SetTuple(1, nrms[3:])

    planes = vtk.vtkPlanes()
    planes.SetPoints(points)
    planes.SetNormals(normals)

    tcoords = vtk.vtkImplicitTextureCoords()
    tcoords.SetInputConnection(sphere2.GetOutputPort())
    tcoords.SetRFunction(planes)

    outerMapper = vtk.vtkDataSetMapper()
    outerMapper.SetInputConnection(tcoords.GetOutputPort())

    tmap = vtk.vtkStructuredPointsReader()
    tmap.SetFileName(fileName)

    texture = vtk.vtkTexture()
    texture.SetInputConnection(tmap.GetOutputPort())
    texture.InterpolateOff()
    texture.RepeatOff()

    outerSphere = vtk.vtkActor()
    outerSphere.SetMapper(outerMapper)
    outerSphere.SetTexture(texture)
    outerSphere.GetProperty().SetColor(colors.GetColor3d("LightSalmon"))

    renWin = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()
    aren = vtk.vtkRenderer()
    iren.SetRenderWindow(renWin)
    renWin.AddRenderer(aren)

    aren.AddActor(innerSphere)
    aren.AddActor(outerSphere)
    aren.SetBackground(colors.GetColor3d("SlateGray"))
    aren.GetActiveCamera().Azimuth(-20)
    aren.GetActiveCamera().Elevation(-10)
    aren.ResetCamera()

    renWin.SetSize(500, 500)

    # interact with data
    renWin.Render()

    iren.Initialize()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Cut an outer sphere to reveal an inner sphere.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='texThres.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
