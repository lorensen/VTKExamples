#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
The human data file is taken from:
  https://github.com/Slicer/Slicer/blob/master/Base/Logic/Resources/OrientationMarkers/Human.vtp
  Thanks to the Slicer people for providing this.
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # Create a rendering window, renderer and interactor.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(780, 780)
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Make an annotated cube actor with axes and then add it into an orientation marker widget.
    # Three of these need to be made.

    # Right Posterior Superior
    xyzLabels = ['X', 'Y', 'Z']
    scale = [1.5, -1.5, 1.5]
    axes = MakeCubeActor(scale, xyzLabels, colors)
    om = vtk.vtkOrientationMarkerWidget()
    om.SetOrientationMarker(axes)
    # Position upper left in the viewport.
    om.SetViewport(0.0, 0.8, 0.2, 1.0)
    om.SetInteractor(iren)
    om.EnabledOn()
    om.InteractiveOn()

    # Right, Anterior, Superior.
    scale = [1.5, 1.5, 1.5]
    axes1 = MakeCubeActor(scale, xyzLabels, colors)
    om1 = vtk.vtkOrientationMarkerWidget()
    om1.SetOrientationMarker(axes1)
    # Position lower left in the viewport.
    om1.SetViewport(0, 0, 0.2, 0.2)
    om1.SetInteractor(iren)
    om1.EnabledOn()
    om1.InteractiveOn()

    # Left, Posterior, Superior.
    scale = (-1.5, -1.5, 1.5)
    axes2 = MakeCubeActor(scale, xyzLabels, colors)
    om2 = vtk.vtkOrientationMarkerWidget()
    om2.SetOrientationMarker(axes2)
    # Position lower right in the viewport.
    om2.SetViewport(0.8, 0, 1.0, 0.2)
    om2.SetInteractor(iren)
    om2.EnabledOn()
    om2.InteractiveOn()

    # Finally create an annotated cube actor adding it into an orientation marker widget.
    axes3 = MakeAnnotatedCubeActor(colors)
    om3 = vtk.vtkOrientationMarkerWidget()
    om3.SetOrientationMarker(axes3)
    # Position upper right in the viewport.
    om3.SetViewport(0.8, 0.8, 1.0, 1.0)
    om3.SetInteractor(iren)
    om3.EnabledOn()
    om3.InteractiveOn()

    # Read in the model.
    reader = vtk.vtkXMLPolyDataReader()
    reader.SetFileName(fileName)
    reader.Update()

    humanMapper = vtk.vtkPolyDataMapper()
    humanMapper.SetInputConnection(reader.GetOutputPort())
    humanMapper.SetScalarModeToUsePointFieldData()
    humanMapper.SelectColorArray("Color")
    humanMapper.SetColorModeToDirectScalars()

    humanActor = vtk.vtkActor()
    humanActor.SetMapper(humanMapper)
    bounds = humanActor.GetBounds()
    # Scale the actor
    humanActor.SetScale(1.0 / max(bounds))
    ren.AddActor(humanActor)

    # Make the planes.
    actors = MakePlanesActors(colors)
    for actor in actors:
        ren.AddViewProp(actor)
    # Label them.
    textActors = AddTextToPlanes()
    for actor in textActors:
        ren.AddViewProp(actor)

    # Interact
    ren.SetBackground2(colors.GetColor3d('OldLace'))
    ren.SetBackground(colors.GetColor3d('MistyRose'))
    ren.GradientBackgroundOn()
    ren.ResetCamera()
    ren.GetActiveCamera().Zoom(1.6)
    ren.GetActiveCamera().SetPosition(-2.3, 4.1, 4.2)
    # ren.GetActiveCamera().SetPosition(-3.4, 5.5, 0.0)
    ren.GetActiveCamera().SetViewUp(0.0, 0.0, 1.0)
    ren.ResetCameraClippingRange()
    renWin.Render()
    # Call SetWindowName after renWin.Render() is called.
    renWin.SetWindowName("Anatomical Orientation")

    iren.Initialize()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Show a labelled set of anatomical planes transecting a human figure.'
    epilogue = '''
    Show a labelled set of anatomical planes transecting a human figure.
    Annotated cube actors and axes for the various coordinate systems are also shown.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='Human.vtp.')
    args = parser.parse_args()
    return args.filename


def MakeAxesActor(scale, xyzLabels):
    """
    :param scale: Sets the scale and direction of the axes.
    :param xyzLabels: Labels for the axes.
    :return: The axes actor.
    """
    axes = vtk.vtkAxesActor()
    axes.SetScale(scale)
    axes.SetShaftTypeToCylinder()
    axes.SetXAxisLabelText(xyzLabels[0])
    axes.SetYAxisLabelText(xyzLabels[1])
    axes.SetZAxisLabelText(xyzLabels[2])
    axes.SetCylinderRadius(0.5 * axes.GetCylinderRadius())
    axes.SetConeRadius(1.025 * axes.GetConeRadius())
    axes.SetSphereRadius(1.5 * axes.GetSphereRadius())
    tprop = axes.GetXAxisCaptionActor2D().GetCaptionTextProperty()
    tprop.ItalicOn()
    tprop.ShadowOn()
    tprop.SetFontFamilyToTimes()
    # Use the same text properties on the other two axes.
    axes.GetYAxisCaptionActor2D().GetCaptionTextProperty().ShallowCopy(tprop)
    axes.GetZAxisCaptionActor2D().GetCaptionTextProperty().ShallowCopy(tprop)
    return axes


def MakeAnnotatedCubeActor(colors):
    """
    :param colors: Used to determine the cube color.
    :return: The annotated cube actor.
    """
    # A cube with labeled faces.
    cube = vtk.vtkAnnotatedCubeActor()
    cube.SetXPlusFaceText('R')  # Right
    cube.SetXMinusFaceText('L')  # Left
    cube.SetYPlusFaceText('A')  # Anterior
    cube.SetYMinusFaceText('P')  # Posterior
    cube.SetZPlusFaceText('S')  # Superior/Cranial
    cube.SetZMinusFaceText('I')  # Inferior/Caudal
    cube.SetFaceTextScale(0.5)
    cube.GetCubeProperty().SetColor(colors.GetColor3d('Gainsboro'))

    cube.GetTextEdgesProperty().SetColor(colors.GetColor3d('LightSlateGray'))

    # Change the vector text colors.
    cube.GetXPlusFaceProperty().SetColor(colors.GetColor3d('Tomato'))
    cube.GetXMinusFaceProperty().SetColor(colors.GetColor3d('Tomato'))
    cube.GetYPlusFaceProperty().SetColor(colors.GetColor3d('DeepSkyBlue'))
    cube.GetYMinusFaceProperty().SetColor(colors.GetColor3d('DeepSkyBlue'))
    cube.GetZPlusFaceProperty().SetColor(colors.GetColor3d('SeaGreen'))
    cube.GetZMinusFaceProperty().SetColor(colors.GetColor3d('SeaGreen'))
    return cube


def MakeCubeActor(scale, xyzLabels, colors):
    """
    :param scale: Sets the scale and direction of the axes.
    :param xyzLabels: Labels for the axes.
    :param colors: Used to set the colors of the cube faces.
    :return: The combined axes and annotated cube prop.
    """
    # We are combining a vtk.vtkAxesActor and a vtk.vtkAnnotatedCubeActor
    # into a vtk.vtkPropAssembly
    cube = MakeAnnotatedCubeActor(colors)
    axes = MakeAxesActor(scale, xyzLabels)

    # Combine orientation markers into one with an assembly.
    assembly = vtk.vtkPropAssembly()
    assembly.AddPart(axes)
    assembly.AddPart(cube)
    return assembly


def MakePlane(resolution, origin, point1, point2, wxyz, translate):
    plane = vtk.vtkPlaneSource()
    plane.SetResolution(*resolution)
    plane.SetOrigin(origin)
    plane.SetPoint1(point1)
    plane.SetPoint2(point2)
    trnf = vtk.vtkTransform()
    trnf.RotateWXYZ(*wxyz)
    trnf.Translate(translate)
    tpdPlane = vtk.vtkTransformPolyDataFilter()
    tpdPlane.SetTransform(trnf)
    tpdPlane.SetInputConnection(plane.GetOutputPort())
    return tpdPlane


def MakePlanesActors(colors):
    """
    Make the traverse, coronal and saggital planes.
    :param colors: Used to set the color of the planes.
    :return: The planes actors.
    """
    planes = list()
    mappers = list()
    actors = list()

    # Parameters for a plane lying in the x-y plane.
    resolution = [10, 10]
    origin = [0.0, 0.0, 0.0]
    point1 = [1, 0, 0]
    point2 = [0, 1, 0]

    planes.append(MakePlane(resolution, origin, point1, point2, [0, 0, 0, 0], [-0.5, -0.5, 0]))  # x-y plane
    planes.append(MakePlane(resolution, origin, point1, point2, [-90, 1, 0, 0], [-0.5, -0.5, 0.0]))  # x-z plane
    planes.append(MakePlane(resolution, origin, point1, point2, [-90, 0, 1, 0], [-0.5, -0.5, 0.0]))  # y-z plane
    for plane in planes:
        mapper = vtk.vtkPolyDataMapper()
        mapper.SetInputConnection(plane.GetOutputPort())
        actor = vtk.vtkActor()
        actor.SetMapper(mapper)
        mappers.append(mapper)
        actors.append(actor)
    actors[0].GetProperty().SetColor(colors.GetColor3d('SeaGreen'))  # Transverse plane
    actors[1].GetProperty().SetColor(colors.GetColor3d('DeepSkyBlue'))  # Coronal plane
    actors[2].GetProperty().SetColor(colors.GetColor3d('Tomato'))  # Saggital plane
    return actors


def AddTextToPlanes():
    """
    Generate text to place on the planes.
    Careful placement is needed here.
    :return: The text actors.
    """
    textActors = list()
    scale = [0.04, 0.04, 0.04]

    text1 = vtk.vtkVectorText()
    text1.SetText("Transverse\nPlane\n\nSuperior\nCranial")
    trnf1 = vtk.vtkTransform()
    trnf1.RotateZ(-90)
    tpdPlane1 = vtk.vtkTransformPolyDataFilter()
    tpdPlane1.SetTransform(trnf1)
    tpdPlane1.SetInputConnection(text1.GetOutputPort())
    textMapper1 = vtk.vtkPolyDataMapper()
    textMapper1.SetInputConnection(tpdPlane1.GetOutputPort())
    textActor1 = vtk.vtkActor()
    textActor1.SetMapper(textMapper1)
    textActor1.SetScale(scale)
    textActor1.AddPosition(0.4, 0.49, 0.01)
    textActors.append(textActor1)

    text2 = vtk.vtkVectorText()
    text2.SetText("Transverse\nPlane\n\nInferior\n(Caudal)")
    trnf2 = vtk.vtkTransform()
    trnf2.RotateZ(270)
    trnf2.RotateWXYZ(*[180, 0, 1, 0])
    tpdPlane2 = vtk.vtkTransformPolyDataFilter()
    tpdPlane2.SetTransform(trnf2)
    tpdPlane2.SetInputConnection(text2.GetOutputPort())
    textMapper2 = vtk.vtkPolyDataMapper()
    textMapper2.SetInputConnection(tpdPlane2.GetOutputPort())
    textActor2 = vtk.vtkActor()
    textActor2.SetMapper(textMapper2)
    textActor2.SetScale(scale)
    textActor2.AddPosition(0.4, -0.49, -0.01)
    textActors.append(textActor2)

    text3 = vtk.vtkVectorText()
    text3.SetText("Sagittal\nPlane\n\nLeft")
    trnf3 = vtk.vtkTransform()
    trnf3.RotateX(90)
    trnf3.RotateWXYZ(*[-90, 0, 1, 0])
    tpdPlane3 = vtk.vtkTransformPolyDataFilter()
    tpdPlane3.SetTransform(trnf3)
    tpdPlane3.SetInputConnection(text3.GetOutputPort())
    textMapper3 = vtk.vtkPolyDataMapper()
    textMapper3.SetInputConnection(tpdPlane3.GetOutputPort())
    textActor3 = vtk.vtkActor()
    textActor3.SetMapper(textMapper3)
    textActor3.SetScale(scale)
    textActor3.AddPosition(-0.01, 0.49, 0.4)
    textActors.append(textActor3)

    text4 = vtk.vtkVectorText()
    text4.SetText("Sagittal\nPlane\n\nRight")
    trnf4 = vtk.vtkTransform()
    trnf4.RotateX(90)
    trnf4.RotateWXYZ(*[-270, 0, 1, 0])
    tpdPlane4 = vtk.vtkTransformPolyDataFilter()
    tpdPlane4.SetTransform(trnf4)
    tpdPlane4.SetInputConnection(text4.GetOutputPort())
    textMapper4 = vtk.vtkPolyDataMapper()
    textMapper4.SetInputConnection(tpdPlane4.GetOutputPort())
    textActor4 = vtk.vtkActor()
    textActor4.SetMapper(textMapper4)
    textActor4.SetScale(scale)
    textActor4.AddPosition(0.01, -0.49, 0.4)
    textActors.append(textActor4)

    text5 = vtk.vtkVectorText()
    text5.SetText("Coronal\nPlane\n\nAnterior")
    trnf5 = vtk.vtkTransform()
    trnf5.RotateY(-180)
    trnf5.RotateWXYZ(*[-90, 1, 0, 0])
    tpdPlane5 = vtk.vtkTransformPolyDataFilter()
    tpdPlane5.SetTransform(trnf5)
    tpdPlane5.SetInputConnection(text5.GetOutputPort())
    textMapper5 = vtk.vtkPolyDataMapper()
    textMapper5.SetInputConnection(tpdPlane5.GetOutputPort())
    textActor5 = vtk.vtkActor()
    textActor5.SetMapper(textMapper5)
    textActor5.SetScale(scale)
    textActor5.AddPosition(0.49, 0.01, 0.20)
    textActors.append(textActor5)

    text6 = vtk.vtkVectorText()
    text6.SetText("Coronal\nPlane\n\nPosterior")
    trnf6 = vtk.vtkTransform()
    trnf6.RotateWXYZ(*[90, 1, 0, 0])
    tpdPlane6 = vtk.vtkTransformPolyDataFilter()
    tpdPlane6.SetTransform(trnf6)
    tpdPlane6.SetInputConnection(text6.GetOutputPort())
    textMapper6 = vtk.vtkPolyDataMapper()
    textMapper6.SetInputConnection(tpdPlane6.GetOutputPort())
    textActor6 = vtk.vtkActor()
    textActor6.SetMapper(textMapper6)
    textActor6.SetScale(scale)
    textActor6.AddPosition(-0.49, -0.01, 0.3)
    textActors.append(textActor6)
    return textActors


if __name__ == "__main__":
    main()
