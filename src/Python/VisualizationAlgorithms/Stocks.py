#!/usr/bin/env python

"""
"""

import os

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileNames = get_program_parameters()

    # Set up the stocks
    renderers = list()
    topRenderer = vtk.vtkRenderer()
    bottomRenderer = vtk.vtkRenderer()
    renderers.append(topRenderer)
    renderers.append(bottomRenderer)

    zPosition = 0.0
    for fn in fileNames:
        zPosition = AddStock(renderers, fn, os.path.basename((os.path.splitext(fn)[0])), zPosition)
        
    # Setup the render window and interactor.
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderers[0])
    renderWindow.AddRenderer(renderers[1])

    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderers[0].SetViewport(0.0, 0.4, 1.0, 1.0)
    renderers[1].SetViewport(0.0, 0.0, 1.0, 0.4)

    renderers[0].GetActiveCamera().SetViewAngle(5.0)
    renderers[0].ResetCamera()
    renderers[0].GetActiveCamera().Zoom(1.4)
    renderers[0].ResetCameraClippingRange()
    renderers[0].SetBackground(colors.GetColor3d("SteelBlue"))

    renderers[1].GetActiveCamera().SetViewUp(0, 0, -1)
    renderers[1].GetActiveCamera().SetPosition(0, 1, 0)
    renderers[1].GetActiveCamera().SetViewAngle(5.0)
    renderers[1].ResetCamera()
    renderers[1].GetActiveCamera().Zoom(2.2)
    renderers[1].ResetCameraClippingRange()
    renderers[1].SetBackground(colors.GetColor3d("LightSteelBlue"))

    renderWindow.SetSize(500, 800)
    renderWindow.Render()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Two views from the stock visualization script.'
    epilogue = '''
    The top shows closing price over time; the bottom shows volume over time.  
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filenames', nargs='+', help='List of one or more filenames corresponding to stocks.')
    args = parser.parse_args()
    return args.filenames


def AddStock(renderers, filename, name, zPosition):
    print("Adding", name)

    # Read the data
    PolyDataRead = vtk.vtkPolyDataReader()
    PolyDataRead.SetFileName(filename)
    PolyDataRead.Update()

    # Create the labels.
    TextSrc = vtk.vtkVectorText()
    TextSrc.SetText(name)

    numberOfPoints = PolyDataRead.GetOutput().GetNumberOfPoints()

    nameIndex = int((numberOfPoints - 1) * 0.8)

    nameLocation = PolyDataRead.GetOutput().GetPoint(nameIndex)

    x = nameLocation[0] * 0.15
    y = nameLocation[1] + 5.0
    z = zPosition

    RibbonFilter = vtk.vtkRibbonFilter()
    RibbonFilter.SetInputConnection(PolyDataRead.GetOutputPort())
    RibbonFilter.VaryWidthOn()
    RibbonFilter.SetWidthFactor(5)
    RibbonFilter.SetDefaultNormal(0, 1, 0)
    RibbonFilter.UseDefaultNormalOn()

    Extrude = vtk.vtkLinearExtrusionFilter()
    Extrude.SetInputConnection(RibbonFilter.GetOutputPort())
    Extrude.SetVector(0, 1, 0)
    Extrude.SetExtrusionType(1)
    Extrude.SetScaleFactor(0.7)

    Transform = vtk.vtkTransform()
    Transform.Translate(0, 0, zPosition)
    Transform.Scale(0.15, 1, 1)

    TransformFilter = vtk.vtkTransformPolyDataFilter()
    TransformFilter.SetInputConnection(Extrude.GetOutputPort())
    TransformFilter.SetTransform(Transform)

    for r in range(0, len(renderers)):
        LabelMapper = vtk.vtkPolyDataMapper()
        LabelMapper.SetInputConnection(TextSrc.GetOutputPort())

        LabelActor = vtk.vtkFollower()
        LabelActor.SetMapper(LabelMapper)
        LabelActor.SetPosition(x, y, z)
        LabelActor.SetScale(2, 2, 2)
        LabelActor.SetOrigin(TextSrc.GetOutput().GetCenter())

        # Increment zPosition.
        zPosition += 8.0

        StockMapper = vtk.vtkPolyDataMapper()
        StockMapper.SetInputConnection(TransformFilter.GetOutputPort())
        StockMapper.SetScalarRange(0, 8000)
        StockActor = vtk.vtkActor()
        StockActor.SetMapper(StockMapper)

        renderers[r].AddActor(StockActor)
        renderers[r].AddActor(LabelActor)
        LabelActor.SetCamera(renderers[r].GetActiveCamera())
    return zPosition


if __name__ == '__main__':
    main()
