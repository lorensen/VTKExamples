#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    xyxFile, qFile = get_program_parameters()

    # Read the data.
    #
    pl3d = vtk.vtkMultiBlockPLOT3DReader()
    pl3d.AutoDetectFormatOn()
    pl3d.SetXYZFileName(xyxFile)
    pl3d.SetQFileName(qFile)
    pl3d.SetScalarFunctionNumber(153)
    pl3d.SetVectorFunctionNumber(200)
    pl3d.Update()

    sg = pl3d.GetOutput().GetBlock(0)

    # blue to red lut
    #
    lut = vtk.vtkLookupTable()
    lut.SetHueRange(0.667, 0.0)

    seeds = [[-0.74, 0.0, 0.3], [-0.74, 0.0, 1.0], [-0.74, 0.0, 2.0], [-0.74, 0.0, 3.0]]

    renderers = list()

    for s in range(0, len(seeds)):
        # computational planes
        floorComp = vtk.vtkStructuredGridGeometryFilter()
        floorComp.SetExtent(0, 37, 0, 75, 0, 0)
        floorComp.SetInputData(sg)
        floorComp.Update()

        floorMapper = vtk.vtkPolyDataMapper()
        floorMapper.SetInputConnection(floorComp.GetOutputPort())
        floorMapper.ScalarVisibilityOff()
        floorMapper.SetLookupTable(lut)

        floorActor = vtk.vtkActor()
        floorActor.SetMapper(floorMapper)
        floorActor.GetProperty().SetRepresentationToWireframe()
        floorActor.GetProperty().SetColor(colors.GetColor3d("Black"))
        floorActor.GetProperty().SetLineWidth(2)

        postComp = vtk.vtkStructuredGridGeometryFilter()
        postComp.SetExtent(10, 10, 0, 75, 0, 37)
        postComp.SetInputData(sg)

        postMapper = vtk.vtkPolyDataMapper()
        postMapper.SetInputConnection(postComp.GetOutputPort())
        postMapper.SetLookupTable(lut)
        postMapper.SetScalarRange(sg.GetScalarRange())

        postActor = vtk.vtkActor()
        postActor.SetMapper(postMapper)
        postActor.GetProperty().SetColor(colors.GetColor3d("Black"))

        # streamers
        #
        # spherical seed points
        rake = vtk.vtkPointSource()
        rake.SetCenter(seeds[s])
        rake.SetNumberOfPoints(10)

        streamers = vtk.vtkStreamTracer()
        streamers.SetInputConnection(pl3d.GetOutputPort())

        # streamers SetSource [rake GetOutput]
        streamers.SetSourceConnection(rake.GetOutputPort())
        streamers.SetMaximumPropagation(250)
        streamers.SetInitialIntegrationStep(.2)
        streamers.SetMinimumIntegrationStep(.01)
        streamers.SetIntegratorType(2)
        streamers.Update()

        tubes = vtk.vtkTubeFilter()
        tubes.SetInputConnection(streamers.GetOutputPort())
        tubes.SetNumberOfSides(8)
        tubes.SetRadius(.08)
        tubes.SetVaryRadius(0)

        mapTubes = vtk.vtkPolyDataMapper()

        mapTubes.SetInputConnection(tubes.GetOutputPort())
        mapTubes.SetScalarRange(sg.GetScalarRange())

        tubesActor = vtk.vtkActor()
        tubesActor.SetMapper(mapTubes)

        renderer = vtk.vtkRenderer()

        renderer.AddActor(floorActor)
        renderer.AddActor(postActor)
        renderer.AddActor(tubesActor)
        renderer.SetBackground(colors.GetColor3d("SlateGray"))
        renderers.append(renderer)

    renderWindow = vtk.vtkRenderWindow()

    # Setup viewports for the renderers
    rendererSize = 256
    xGridDimensions = 2
    yGridDimensions = 2
    renderWindow.SetSize(rendererSize * xGridDimensions, rendererSize * yGridDimensions)
    for row in range(0, yGridDimensions):
        for col in range(xGridDimensions):
            index = row * xGridDimensions + col
            # (xmin, ymin, xmax, ymax)
            viewport = [float(col) / xGridDimensions, float(yGridDimensions - (row + 1)) / yGridDimensions,
                        float(col + 1) / xGridDimensions, float(yGridDimensions - row) / yGridDimensions]
            renderers[index].SetViewport(viewport)

    camera = vtk.vtkCamera()
    camera.SetFocalPoint(0.918037, -0.0779233, 2.69513)
    camera.SetPosition(0.840735, -23.6176, 8.50211)
    camera.SetViewUp(0.00227904, 0.239501, 0.970893)
    camera.SetClippingRange(1, 100)

    renderers[0].SetActiveCamera(camera)
    for r in range(0, len(renderers)):
        renderWindow.AddRenderer(renderers[r])
        if r > 0:
            renderers[r].SetActiveCamera(camera)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    renderWindow.SetSize(512, 512)

    renderWindow.Render()
    interactor.Start()


def get_program_parameters():
    import argparse
    description = 'Streamlines seeded with spherical cloud of points. Four separate cloud positions are shown.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('xyz_file', help='postxyz.bin.')
    parser.add_argument('q_file', help='postq.bin.')
    args = parser.parse_args()
    return args.xyz_file, args.q_file


if __name__ == '__main__':
    main()
