#!/usr/bin/env python

import vtk


def main():
    inputFilename, numberOfCuts = get_program_parameters()

    colors = vtk.vtkNamedColors()

    reader= vtk.vtkXMLPolyDataReader()
    reader.SetFileName(inputFilename)
    reader.Update()

    bounds = reader.GetOutput().GetBounds()
    print(bounds)

    plane= vtk.vtkPlane()
    plane.SetOrigin((bounds[1] + bounds[0]) / 2.0,
                     (bounds[3] + bounds[2]) / 2.0,
                     (bounds[5] + bounds[4]) / 2.0)
    plane.SetNormal(0,0,1)

    # Create Scalars.
    scalars= vtk.vtkDoubleArray()
    numberOfPoints = reader.GetOutput().GetNumberOfPoints()
    scalars.SetNumberOfTuples(numberOfPoints)
    pts = reader.GetOutput().GetPoints()
    for i in range(0, numberOfPoints):
        point = pts.GetPoint(i)
        scalars.SetTuple1(i, plane.EvaluateFunction(point))
    reader.GetOutput().GetPointData().SetScalars(scalars)
    reader.GetOutput().GetPointData().GetScalars().GetRange()

    # Create the cutter.
    cutter= vtk.vtkContourFilter()
    cutter.SetInputConnection(reader.GetOutputPort())
    cutter.ComputeScalarsOff()
    cutter.ComputeNormalsOff()
    cutter.GenerateValues(
      numberOfCuts,
      0.99 * reader.GetOutput().GetPointData().GetScalars().GetRange()[0],
      0.99 * reader.GetOutput().GetPointData().GetScalars().GetRange()[1])

    cutterMapper= vtk.vtkPolyDataMapper()
    cutterMapper.SetInputConnection( cutter.GetOutputPort())
    cutterMapper.ScalarVisibilityOff()

    # Create the cut actor.
    cutterActor = vtk.vtkActor()
    cutterActor.GetProperty().SetColor(colors.GetColor3d("Banana"))
    cutterActor.GetProperty().SetLineWidth(2)
    cutterActor.SetMapper(cutterMapper)

    # Create the model actor
    modelMapper= vtk.vtkPolyDataMapper()
    modelMapper.SetInputConnection( reader.GetOutputPort())
    modelMapper.ScalarVisibilityOff()

    modelActor= vtk.vtkActor()
    modelActor.GetProperty().SetColor(colors.GetColor3d("Flesh"))
    modelActor.SetMapper(modelMapper)

    # Create renderers and add the plane and model actors.
    renderer= vtk.vtkRenderer()
    renderer.AddActor(cutterActor)
    renderer.AddActor(modelActor)

    # Add renderer to renderwindow and render
    renderWindow= vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(600, 600)

    interactor= vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    renderer.SetBackground(colors.GetColor3d("Burlywood"))
    renderer.GetActiveCamera().SetPosition(0, -1, 0)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0, 0, 1)
    renderer.GetActiveCamera().Azimuth(30)
    renderer.GetActiveCamera().Elevation(30)

    renderer.ResetCamera()
    renderWindow.Render()

    interactor.Start()

def get_program_parameters():
    import argparse
    description = 'Cutting a surface model of the skin with a series of planes produces contour lines.'
    epilogue = '''
    Lines are wrapped with tubes for visual clarity.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='Torso.vtp.')
    parser.add_argument('-n', type=int, default=20, help='Number of cuts.')
    args = parser.parse_args()
    return args.filename1, args.n


if __name__ == '__main__':
    main()
