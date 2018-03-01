#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk


def main():
    colors = vtk.vtkNamedColors()

    # Set the colors.
    colors.SetColor("AzimuthArrowColor", [255, 77, 77, 255])
    colors.SetColor("ElevationArrowColor", [77, 255, 77, 255])
    colors.SetColor("RollArrowColor", [255, 255, 77, 255])
    colors.SetColor("SpikeColor", [255, 77, 255, 255])
    colors.SetColor("UpSpikeColor", [77, 255, 255, 255])

    # Create a rendering window, renderer and interactor.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create a camera model.
    camCS = vtk.vtkConeSource()
    camCS.SetHeight(1.5)
    camCS.SetResolution(12)
    camCS.SetRadius(0.4)

    camCBS = vtk.vtkCubeSource()
    camCBS.SetXLength(1.5)
    camCBS.SetZLength(0.8)
    camCBS.SetCenter(0.4, 0, 0)

    camAPD = vtk.vtkAppendPolyData()
    camAPD.AddInputConnection(camCBS.GetOutputPort())
    camAPD.AddInputConnection(camCS.GetOutputPort())

    camMapper = vtk.vtkPolyDataMapper()
    camMapper.SetInputConnection(camAPD.GetOutputPort())
    camActor = vtk.vtkLODActor()
    camActor.SetMapper(camMapper)
    camActor.SetScale(2, 2, 2)

    # Draw the arrows.
    pd = vtk.vtkPolyData()
    ca = vtk.vtkCellArray()
    pts = vtk.vtkPoints()
    pts.InsertNextPoint(0, 1, 0)
    pts.InsertNextPoint(8, 1, 0)
    pts.InsertNextPoint(8, 2, 0)
    pts.InsertNextPoint(10, 0, 0)
    pts.InsertNextPoint(8, -2, 0)
    pts.InsertNextPoint(8, -1, 0)
    pts.InsertNextPoint(0, -1, 0)
    ca.InsertNextCell(7)
    ca.InsertCellPoint(0)
    ca.InsertCellPoint(1)
    ca.InsertCellPoint(2)
    ca.InsertCellPoint(3)
    ca.InsertCellPoint(4)
    ca.InsertCellPoint(5)
    ca.InsertCellPoint(6)
    pd.SetPoints(pts)
    pd.SetPolys(ca)

    pd2 = vtk.vtkPolyData()
    ca2 = vtk.vtkCellArray()
    pts2 = vtk.vtkPoints()
    pts2.InsertNextPoint(0, 1, 0)
    pts2.InsertNextPoint(8, 1, 0)
    pts2.InsertNextPoint(8, 2, 0)
    pts2.InsertNextPoint(10, 0.01, 0)
    ca2.InsertNextCell(4)
    ca2.InsertCellPoint(0)
    ca2.InsertCellPoint(1)
    ca2.InsertCellPoint(2)
    ca2.InsertCellPoint(3)
    pd2.SetPoints(pts2)
    pd2.SetLines(ca2)

    arrowIM = vtk.vtkImplicitModeller()
    arrowIM.SetInputData(pd)
    arrowIM.SetSampleDimensions(50, 20, 8)

    arrowCF = vtk.vtkContourFilter()
    arrowCF.SetInputConnection(arrowIM.GetOutputPort())
    arrowCF.SetValue(0, 0.2)

    arrowWT = vtk.vtkWarpTo()
    arrowWT.SetInputConnection(arrowCF.GetOutputPort())
    arrowWT.SetPosition(5, 0, 5)
    arrowWT.SetScaleFactor(0.85)
    arrowWT.AbsoluteOn()

    arrowT = vtk.vtkTransform()
    arrowT.RotateY(60)
    arrowT.Translate(-1.33198, 0, -1.479)
    arrowT.Scale(1, 0.5, 1)

    arrowTF = vtk.vtkTransformFilter()
    arrowTF.SetInputConnection(arrowWT.GetOutputPort())
    arrowTF.SetTransform(arrowT)

    arrowMapper = vtk.vtkDataSetMapper()
    arrowMapper.SetInputConnection(arrowTF.GetOutputPort())
    arrowMapper.ScalarVisibilityOff()

    # Draw the azimuth arrows.
    a1Actor = vtk.vtkLODActor()
    a1Actor.SetMapper(arrowMapper)
    a1Actor.SetPosition(-9, 0, -1)
    a1Actor.GetProperty().SetColor(colors.GetColor3d("AzimuthArrowColor"))
    a1Actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    a1Actor.GetProperty().SetSpecular(0.3)
    a1Actor.GetProperty().SetSpecularPower(20)
    a1Actor.GetProperty().SetAmbient(0.2)
    a1Actor.GetProperty().SetDiffuse(0.8)

    a2Actor = vtk.vtkLODActor()
    a2Actor.SetMapper(arrowMapper)
    a2Actor.RotateX(180)
    a2Actor.SetPosition(-9, 0, 1)
    a2Actor.GetProperty().SetColor(colors.GetColor3d("AzimuthArrowColor"))
    a2Actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    a2Actor.GetProperty().SetSpecular(0.3)
    a2Actor.GetProperty().SetSpecularPower(20)
    a2Actor.GetProperty().SetAmbient(0.2)
    a2Actor.GetProperty().SetDiffuse(0.8)

    # Draw the elevation arrows.
    a3Actor = vtk.vtkLODActor()
    a3Actor.SetMapper(arrowMapper)
    a3Actor.RotateX(-90)
    a3Actor.SetPosition(-9, -1, 0)
    a3Actor.GetProperty().SetColor(colors.GetColor3d("ElevationArrowColor"))
    a3Actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    a3Actor.GetProperty().SetSpecular(0.3)
    a3Actor.GetProperty().SetSpecularPower(20)
    a3Actor.GetProperty().SetAmbient(0.2)
    a3Actor.GetProperty().SetDiffuse(0.8)

    a4Actor = vtk.vtkLODActor()
    a4Actor.SetMapper(arrowMapper)
    a4Actor.RotateX(90)
    a4Actor.SetPosition(-9, 1, 0)
    a4Actor.GetProperty().SetColor(colors.GetColor3d("ElevationArrowColor"))
    a4Actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    a4Actor.GetProperty().SetSpecular(0.3)
    a4Actor.GetProperty().SetSpecularPower(20)
    a4Actor.GetProperty().SetAmbient(0.2)
    a4Actor.GetProperty().SetDiffuse(0.8)

    # Draw the DOP.
    arrowT2 = vtk.vtkTransform()
    arrowT2.Scale(1, 0.6, 1)
    arrowT2.RotateY(90)

    arrowTF2 = vtk.vtkTransformPolyDataFilter()
    arrowTF2.SetInputData(pd2)
    arrowTF2.SetTransform(arrowT2)

    arrowREF = vtk.vtkRotationalExtrusionFilter()
    arrowREF.SetInputConnection(arrowTF2.GetOutputPort())
    arrowREF.CappingOff()
    arrowREF.SetResolution(30)

    spikeMapper = vtk.vtkPolyDataMapper()
    spikeMapper.SetInputConnection(arrowREF.GetOutputPort())

    a5Actor = vtk.vtkLODActor()
    a5Actor.SetMapper(spikeMapper)
    a5Actor.SetScale(0.3, 0.3, 0.6)
    a5Actor.RotateY(-90)
    a5Actor.SetPosition(-8, 0, 0)
    a5Actor.GetProperty().SetColor(colors.GetColor3d("SpikeColor"))
    a5Actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    a5Actor.GetProperty().SetSpecular(0.3)
    a5Actor.GetProperty().SetAmbient(0.2)
    a5Actor.GetProperty().SetDiffuse(0.8)
    a5Actor.GetProperty().SetSpecularPower(20)

    a7Actor = vtk.vtkLODActor()
    a7Actor.SetMapper(spikeMapper)
    a7Actor.SetScale(0.2, 0.2, 0.7)
    a7Actor.RotateZ(90)
    a7Actor.RotateY(-90)
    a7Actor.SetPosition(-9, 1, 0)
    a7Actor.GetProperty().SetColor(colors.GetColor3d("UpSpikeColor"))
    a7Actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    a7Actor.GetProperty().SetSpecular(0.3)
    a7Actor.GetProperty().SetAmbient(0.2)
    a7Actor.GetProperty().SetDiffuse(0.8)
    a7Actor.GetProperty().SetSpecularPower(20)

    # Focal point.
    ss = vtk.vtkSphereSource()
    ss.SetRadius(0.5)
    fpMapper = vtk.vtkPolyDataMapper()
    fpMapper.SetInputConnection(ss.GetOutputPort())
    fpActor = vtk.vtkLODActor()
    fpActor.SetMapper(fpMapper)
    fpActor.SetPosition(-9, 0, 0)
    fpActor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    fpActor.GetProperty().SetSpecular(0.3)
    fpActor.GetProperty().SetAmbient(0.2)
    fpActor.GetProperty().SetDiffuse(0.8)
    fpActor.GetProperty().SetSpecularPower(20)

    # Create the roll arrows.
    arrowWT2 = vtk.vtkWarpTo()
    arrowWT2.SetInputConnection(arrowCF.GetOutputPort())
    arrowWT2.SetPosition(5, 0, 2.5)
    arrowWT2.SetScaleFactor(0.95)
    arrowWT2.AbsoluteOn()

    arrowT3 = vtk.vtkTransform()
    arrowT3.Translate(-2.50358, 0, -1.70408)
    arrowT3.Scale(0.5, 0.3, 1)

    arrowTF3 = vtk.vtkTransformFilter()
    arrowTF3.SetInputConnection(arrowWT2.GetOutputPort())
    arrowTF3.SetTransform(arrowT3)

    arrowMapper2 = vtk.vtkDataSetMapper()
    arrowMapper2.SetInputConnection(arrowTF3.GetOutputPort())
    arrowMapper2.ScalarVisibilityOff()

    # Draw the roll arrows.
    a6Actor = vtk.vtkLODActor()
    a6Actor.SetMapper(arrowMapper2)
    a6Actor.RotateZ(90)
    a6Actor.SetPosition(-4, 0, 0)
    a6Actor.SetScale(1.5, 1.5, 1.5)
    a6Actor.GetProperty().SetColor(colors.GetColor3d("RollArrowColor"))
    a6Actor.GetProperty().SetSpecularColor(colors.GetColor3d("White"))
    a6Actor.GetProperty().SetSpecular(0.3)
    a6Actor.GetProperty().SetSpecularPower(20)
    a6Actor.GetProperty().SetAmbient(0.2)
    a6Actor.GetProperty().SetDiffuse(0.8)

    # Add the actors to the renderer, set the background and size.
    ren.AddActor(camActor)
    ren.AddActor(a1Actor)
    ren.AddActor(a2Actor)
    ren.AddActor(a3Actor)
    ren.AddActor(a4Actor)
    ren.AddActor(a5Actor)
    ren.AddActor(a6Actor)
    ren.AddActor(a7Actor)
    ren.AddActor(fpActor)
    ren.SetBackground(colors.GetColor3d("SlateGray"))
    renWin.SetSize(640, 480)

    # Render the image.

    cam1 = (ren.GetActiveCamera())
    ren.ResetCamera()
    cam1.Azimuth(150)
    cam1.Elevation(30)
    cam1.Dolly(1.5)
    ren.ResetCameraClippingRange()

    # Create a TextActor for Yaw  (a1 and a2 actor's color).
    text = vtk.vtkTextActor()
    text.SetInput("Yaw")
    tprop = text.GetTextProperty()
    tprop.SetFontFamilyToArial()
    tprop.ShadowOff()
    tprop.SetLineSpacing(1.0)
    tprop.SetFontSize(36)
    tprop.SetColor(a1Actor.GetProperty().GetColor())
    text.SetDisplayPosition(20, 50)
    ren.AddActor2D(text)

    # Create a TextActor for Pitch  (a3 and a4 actor's color).
    text2 = vtk.vtkTextActor()
    text2.SetInput("Pitch")
    tprop = text2.GetTextProperty()
    tprop.SetFontFamilyToArial()
    tprop.ShadowOff()
    tprop.SetLineSpacing(1.0)
    tprop.SetFontSize(36)
    tprop.SetColor(a3Actor.GetProperty().GetColor())
    text2.SetDisplayPosition(20, 100)
    ren.AddActor2D(text2)

    # Create a TextActor for roll (a6 actor's color).
    text3 = vtk.vtkTextActor()
    text3.SetInput("Roll")
    tprop = text3.GetTextProperty()
    tprop.SetFontFamilyToArial()
    tprop.ShadowOff()
    tprop.SetLineSpacing(1.0)
    tprop.SetFontSize(36)
    tprop.SetColor(a6Actor.GetProperty().GetColor())
    text3.SetDisplayPosition(20, 150)
    ren.AddActor2D(text3)

    iren.Initialize()
    iren.Start()


if __name__ == "__main__":
    main()
