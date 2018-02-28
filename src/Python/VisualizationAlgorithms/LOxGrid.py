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

    # Computational planes.
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
    floorActor.GetProperty().SetColor(colors.GetColor3d("Beige"))
    floorActor.GetProperty().SetLineWidth(2)

    subFloorComp = vtk.vtkStructuredGridGeometryFilter()

    subFloorComp.SetExtent(0, 37, 0, 15, 22, 22)
    subFloorComp.SetInputData(sg)

    subFloorMapper = vtk.vtkPolyDataMapper()
    subFloorMapper.SetInputConnection(subFloorComp.GetOutputPort())
    subFloorMapper.SetLookupTable(lut)
    subFloorMapper.SetScalarRange(sg.GetScalarRange())

    subFloorActor = vtk.vtkActor()

    subFloorActor.SetMapper(subFloorMapper)

    subFloor2Comp = vtk.vtkStructuredGridGeometryFilter()
    subFloor2Comp.SetExtent(0, 37, 60, 75, 22, 22)
    subFloor2Comp.SetInputData(sg)

    subFloor2Mapper = vtk.vtkPolyDataMapper()
    subFloor2Mapper.SetInputConnection(subFloor2Comp.GetOutputPort())
    subFloor2Mapper.SetLookupTable(lut)
    subFloor2Mapper.SetScalarRange(sg.GetScalarRange())

    subFloor2Actor = vtk.vtkActor()

    subFloor2Actor.SetMapper(subFloor2Mapper)

    postComp = vtk.vtkStructuredGridGeometryFilter()

    postComp.SetExtent(10, 10, 0, 75, 0, 37)
    postComp.SetInputData(sg)

    postMapper = vtk.vtkPolyDataMapper()
    postMapper.SetInputConnection(postComp.GetOutputPort())
    postMapper.SetLookupTable(lut)
    postMapper.SetScalarRange(sg.GetScalarRange())

    postActor = vtk.vtkActor()
    postActor.SetMapper(postMapper)
    postActor.GetProperty().SetColor(colors.GetColor3d("Beige"))

    fanComp = vtk.vtkStructuredGridGeometryFilter()
    fanComp.SetExtent(0, 37, 38, 38, 0, 37)
    fanComp.SetInputData(sg)

    fanMapper = vtk.vtkPolyDataMapper()
    fanMapper.SetInputConnection(fanComp.GetOutputPort())
    fanMapper.SetLookupTable(lut)
    fanMapper.SetScalarRange(sg.GetScalarRange())

    fanActor = vtk.vtkActor()

    fanActor.SetMapper(fanMapper)
    fanActor.GetProperty().SetColor(colors.GetColor3d("Beige"))

    # streamers
    #
    # spherical seed points
    rake = vtk.vtkPointSource()
    rake.SetCenter(-0.74, 0, 0.3)
    rake.SetNumberOfPoints(10)

    # a line of seed points
    seedsComp = vtk.vtkStructuredGridGeometryFilter()
    seedsComp.SetExtent(10, 10, 37, 39, 1, 35)
    seedsComp.SetInputData(sg)

    streamers = vtk.vtkStreamTracer()
    streamers.SetInputConnection(pl3d.GetOutputPort())

    # streamers SetSource [rake GetOutput]
    streamers.SetSourceConnection(seedsComp.GetOutputPort())
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

    # outline
    outline = vtk.vtkStructuredGridOutlineFilter()
    outline.SetInputData(sg)

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Beige"))

    # Create graphics stuff.
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(outlineActor)
    ren1.AddActor(floorActor)
    ren1.AddActor(subFloorActor)
    ren1.AddActor(subFloor2Actor)
    ren1.AddActor(postActor)
    ren1.AddActor(fanActor)
    ren1.AddActor(tubesActor)

    aCam = vtk.vtkCamera()
    aCam.SetFocalPoint(0.00657892, 0, 2.41026)
    aCam.SetPosition(-1.94838, -47.1275, 39.4607)
    aCam.SetViewUp(0.00653193, 0.617865, 0.786257)
    ren1.ResetCamera()
    aCam.Dolly(1.)
    aCam.SetClippingRange(1, 100)

    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    ren1.SetActiveCamera(aCam)
    renWin.SetSize(640, 480)

    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'LOx post CFD case study.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('xyz_file', help='postxyz.bin.')
    parser.add_argument('q_file', help='postq.bin.')
    args = parser.parse_args()
    return args.xyz_file, args.q_file


if __name__ == '__main__':
    main()
