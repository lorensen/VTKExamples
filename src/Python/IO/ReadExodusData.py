#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read and display ExodusII data.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename', help='A required filename e.g mug.e.')
    parser.add_argument('nodal_var', help='The nodal variable e,g, convected.')
    args = parser.parse_args()
    return args.filename, args.nodal_var


def main():
    colors = vtk.vtkNamedColors()

    # Input file and variable
    filename, nodal_var = get_program_parameters()

    # Read Exodus Data
    reader = vtk.vtkExodusIIReader()
    reader.SetFileName(filename)
    reader.UpdateInformation()
    reader.SetTimeStep(10)
    reader.SetAllArrayStatus(vtk.vtkExodusIIReader.NODAL, 1)  # enables all NODAL variables
    reader.Update()
    # print(reader)  # uncomment this to show the file information

    # Create Geometry
    geometry = vtk.vtkCompositeDataGeometryFilter()
    geometry.SetInputConnection(0, reader.GetOutputPort(0))
    geometry.Update()

    # Mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(geometry.GetOutputPort())
    mapper.SelectColorArray(nodal_var)
    mapper.SetScalarModeToUsePointFieldData()
    mapper.InterpolateScalarsBeforeMappingOn()

    # Actor
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Renderer
    renderer = vtk.vtkRenderer()
    renderer.AddViewProp(actor)
    renderer.SetBackground(colors.GetColor3d("DimGray"))

    renderer.GetActiveCamera().SetPosition(9.0, 9.0, 7.0)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0.2, -0.7, 0.7)
    renderer.GetActiveCamera().SetDistance(14.5)

    # Window and Interactor
    window = vtk.vtkRenderWindow()
    window.AddRenderer(renderer)
    window.SetSize(600, 600)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(window)
    interactor.Initialize()

    # Show the result
    window.Render()
    interactor.Start()


if __name__ == '__main__':
    main()
