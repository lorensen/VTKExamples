#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Create the RenderWindow, Renderer and Interactor.
    #
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Generate the tensors.
    ptLoad = vtk.vtkPointLoad()
    ptLoad.SetLoadValue(100.0)
    ptLoad.SetSampleDimensions(20, 20, 20)
    ptLoad.ComputeEffectiveStressOn()
    ptLoad.SetModelBounds(-10, 10, -10, 10, -10, 10)
    ptLoad.Update()

    # Generate the hyperstreamlines.
    s1 = vtk.vtkHyperStreamline()
    s1.SetInputData(ptLoad.GetOutput())
    s1.SetStartPosition(9, 9, -9)
    s1.IntegrateMinorEigenvector()
    s1.SetMaximumPropagationDistance(18.0)
    s1.SetIntegrationStepLength(0.1)
    s1.SetStepLength(0.01)
    s1.SetRadius(0.25)
    s1.SetNumberOfSides(18)
    s1.SetIntegrationDirectionToIntegrateBothDirections()
    s1.Update()

    # Map the hyperstreamlines.
    lut = vtk.vtkLogLookupTable()
    lut.SetHueRange(.6667, 0.0)

    s1Mapper = vtk.vtkPolyDataMapper()
    s1Mapper.SetInputConnection(s1.GetOutputPort())
    s1Mapper.SetLookupTable(lut)
    s1Mapper.SetScalarRange(ptLoad.GetOutput().GetScalarRange())

    s1Actor = vtk.vtkActor()
    s1Actor.SetMapper(s1Mapper)

    s2 = vtk.vtkHyperStreamline()
    s2.SetInputData(ptLoad.GetOutput())
    s2.SetStartPosition(-9, -9, -9)
    s2.IntegrateMinorEigenvector()
    s2.SetMaximumPropagationDistance(18.0)
    s2.SetIntegrationStepLength(0.1)
    s2.SetStepLength(0.01)
    s2.SetRadius(0.25)
    s2.SetNumberOfSides(18)
    s2.SetIntegrationDirectionToIntegrateBothDirections()
    s2.Update()

    s2Mapper = vtk.vtkPolyDataMapper()
    s2Mapper.SetInputConnection(s2.GetOutputPort())
    s2Mapper.SetLookupTable(lut)
    s2Mapper.SetScalarRange(ptLoad.GetOutput().GetScalarRange())

    s2Actor = vtk.vtkActor()
    s2Actor.SetMapper(s2Mapper)

    s3 = vtk.vtkHyperStreamline()
    s3.SetInputData(ptLoad.GetOutput())
    s3.SetStartPosition(9, -9, -9)
    s3.IntegrateMinorEigenvector()
    s3.SetMaximumPropagationDistance(18.0)
    s3.SetIntegrationStepLength(0.1)
    s3.SetStepLength(0.01)
    s3.SetRadius(0.25)
    s3.SetNumberOfSides(18)
    s3.SetIntegrationDirectionToIntegrateBothDirections()
    s3.Update()

    s3Mapper = vtk.vtkPolyDataMapper()
    s3Mapper.SetInputConnection(s3.GetOutputPort())
    s3Mapper.SetLookupTable(lut)
    s3Mapper.SetScalarRange(ptLoad.GetOutput().GetScalarRange())

    s3Actor = vtk.vtkActor()
    s3Actor.SetMapper(s3Mapper)

    s4 = vtk.vtkHyperStreamline()
    s4.SetInputData(ptLoad.GetOutput())
    s4.SetStartPosition(-9, 9, -9)
    s4.IntegrateMinorEigenvector()
    s4.SetMaximumPropagationDistance(18.0)
    s4.SetIntegrationStepLength(0.1)
    s4.SetStepLength(0.01)
    s4.SetRadius(0.25)
    s4.SetNumberOfSides(18)
    s4.SetIntegrationDirectionToIntegrateBothDirections()
    s4.Update()

    s4Mapper = vtk.vtkPolyDataMapper()
    s4Mapper.SetInputConnection(s4.GetOutputPort())
    s4Mapper.SetLookupTable(lut)
    s4Mapper.SetScalarRange(ptLoad.GetOutput().GetScalarRange())

    s4Actor = vtk.vtkActor()
    s4Actor.SetMapper(s4Mapper)

    # A plane for context.
    #
    g = vtk.vtkImageDataGeometryFilter()
    g.SetInputData(ptLoad.GetOutput())
    g.SetExtent(0, 100, 0, 100, 0, 0)
    g.Update()  # for scalar range

    gm = vtk.vtkPolyDataMapper()
    gm.SetInputConnection(g.GetOutputPort())
    gm.SetScalarRange(g.GetOutput().GetScalarRange())

    ga = vtk.vtkActor()
    ga.SetMapper(gm)

    # Create an outline around the data.
    #
    outline = vtk.vtkOutlineFilter()
    outline.SetInputData(ptLoad.GetOutput())

    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())

    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    # Create a cone indicating the application of the load.
    #
    coneSrc = vtk.vtkConeSource()
    coneSrc.SetRadius(.5)
    coneSrc.SetHeight(2)

    coneMap = vtk.vtkPolyDataMapper()
    coneMap.SetInputConnection(coneSrc.GetOutputPort())

    coneActor = vtk.vtkActor()
    coneActor.SetMapper(coneMap)
    coneActor.SetPosition(0, 0, 11)
    coneActor.RotateY(90)
    coneActor.GetProperty().SetColor(colors.GetColor3d("Tomato"))

    camera = vtk.vtkCamera()
    camera.SetFocalPoint(0.113766, -1.13665, -1.01919)
    camera.SetPosition(-29.4886, -63.1488, 26.5807)
    camera.SetViewAngle(24.4617)
    camera.SetViewUp(0.17138, 0.331163, 0.927879)
    camera.SetClippingRange(1, 100)

    ren1.AddActor(s1Actor)
    ren1.AddActor(s2Actor)
    ren1.AddActor(s3Actor)
    ren1.AddActor(s4Actor)
    ren1.AddActor(outlineActor)
    ren1.AddActor(coneActor)
    ren1.AddActor(ga)
    ren1.SetBackground(colors.GetColor3d("SlateGray"))
    ren1.SetActiveCamera(camera)

    renWin.SetSize(640, 480)
    renWin.Render()
    iren.Start()


if __name__ == '__main__':
    main()
