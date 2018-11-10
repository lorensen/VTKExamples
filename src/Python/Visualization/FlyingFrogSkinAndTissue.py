#!/usr/bin/env python

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName1, fileName2, useMarchingCubes, noSkin, noSkeleton = get_program_parameters()
    if useMarchingCubes:
        print('Using vtkMarchingCubes.')
    else:
        print('Using vtkFlyingEdges3D.')

    colorLut = CreateFrogLut()

    # Setup render window, renderer, and interactor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    if not noSkin:
        # The skin.
        skinActor = CreateFrogSkinActor(fileName1, useMarchingCubes)
        skinActor.GetProperty().SetColor(colors.GetColor3d('LimeGreen'))
        skinActor.GetProperty().SetOpacity(0.4)

        renderer.AddActor(skinActor)
        print('Tissue: skin')

    # Now for the tissues.
    # Use this list to ensure that the tissues are selected in this order.
    tissues = ['blood', 'brain', 'duodenum', 'eyeRetina', 'eyeWhite', 'heart', 'ileum', 'kidney', 'intestine', 'liver',
               'lung', 'nerve', 'skeleton', 'spleen', 'stomach']
    for i, tissue in enumerate(tissues):
        if noSkeleton:
            if tissue == 'skeleton':
                continue
        tissueNumber = i + 1
        actor = CreateFrogActor(fileName2, tissueNumber, useMarchingCubes)
        actor.GetProperty().SetDiffuseColor(colorLut.GetTableValue(tissueNumber)[:3])
        actor.GetProperty().SetSpecular(.5)
        actor.GetProperty().SetSpecularPower(10)
        renderer.AddActor(actor)
        print('Tissue:', tissue, ', Label:', tissueNumber)

    renderer.GetActiveCamera().SetViewUp(0, 0, -1)
    renderer.GetActiveCamera().SetPosition(0, -1, 0)

    renderer.GetActiveCamera().Azimuth(210)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCamera()
    renderer.ResetCameraClippingRange()
    renderer.GetActiveCamera().Dolly(1.5)
    renderer.SetBackground(colors.GetColor3d('SlateGray'))

    renderWindow.SetSize(640, 480)
    renderWindow.SetWindowName('Frog')
    renderWindow.Render()

    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Display all frog parts and translucent skin.'
    epilogue = '''
    Either vtkFlyingEdges3D or vtkMarchingCubes is used to generate the data.
    
    You can also omit the skin and/or skeleton in order to get different views of the frog.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='frog.mhd.')
    parser.add_argument('filename2', help='frogtissue.mhd.')
    parser.add_argument('-useMarchingCubes', '--useMarchingCubes', action='store_true',
                        help='Use vtkMarchingCubes instead of vtkFlyingEdges3D.')
    parser.add_argument('-noSkin', '--noSkin', action='store_true',
                        help='Omit the skin.')
    parser.add_argument('-noSkeleton', '--noSkeleton', action='store_true',
                        help='Omit the skeleton.')
    args = parser.parse_args()
    return args.filename1, args.filename2, args.useMarchingCubes, args.noSkin, args.noSkeleton


def CreateFrogLut():
    colors = vtk.vtkNamedColors()

    colorLut = vtk.vtkLookupTable()
    colorLut.SetNumberOfColors(17)
    colorLut.SetTableRange(0, 16)
    colorLut.Build()

    colorLut.SetTableValue(0, colors.GetColor4d('black'))
    colorLut.SetTableValue(1, colors.GetColor4d('salmon'))  # blood
    colorLut.SetTableValue(2, colors.GetColor4d('beige'))  # brain
    colorLut.SetTableValue(3, colors.GetColor4d('orange'))  # duodenum
    colorLut.SetTableValue(4, colors.GetColor4d('misty_rose'))  # retina
    colorLut.SetTableValue(5, colors.GetColor4d('white'))  # eye_white
    colorLut.SetTableValue(6, colors.GetColor4d('tomato'))  # heart
    colorLut.SetTableValue(7, colors.GetColor4d('raspberry'))  # ileum
    colorLut.SetTableValue(8, colors.GetColor4d('banana'))  # kidney
    colorLut.SetTableValue(9, colors.GetColor4d('peru'))  # l_intestine
    colorLut.SetTableValue(10, colors.GetColor4d('pink'))  # liver
    colorLut.SetTableValue(11, colors.GetColor4d('powder_blue'))  # lung
    colorLut.SetTableValue(12, colors.GetColor4d('carrot'))  # nerve
    colorLut.SetTableValue(13, colors.GetColor4d('wheat'))  # skeleton
    colorLut.SetTableValue(14, colors.GetColor4d('violet'))  # spleen
    colorLut.SetTableValue(15, colors.GetColor4d('plum'))  # stomach

    return colorLut


def CreateFrogSkinActor(fileName, useMarchingCubes):
    reader = vtk.vtkMetaImageReader()
    reader.SetFileName(fileName)
    reader.Update()

    isoValue = 20.5
    mcubes = vtk.vtkMarchingCubes()
    flyingEdges = vtk.vtkFlyingEdges3D()
    smoother = vtk.vtkWindowedSincPolyDataFilter()
    if useMarchingCubes:
        mcubes.SetInputConnection(reader.GetOutputPort())
        mcubes.ComputeScalarsOff()
        mcubes.ComputeGradientsOff()
        mcubes.ComputeNormalsOff()
        mcubes.SetValue(0, isoValue)
        smoother.SetInputConnection(mcubes.GetOutputPort())
    else:
        flyingEdges.SetInputConnection(reader.GetOutputPort())
        flyingEdges.ComputeScalarsOff()
        flyingEdges.ComputeGradientsOff()
        flyingEdges.ComputeNormalsOff()
        flyingEdges.SetValue(0, isoValue)
        smoother.SetInputConnection(flyingEdges.GetOutputPort())

    smoothingIterations = 5
    passBand = 0.001
    featureAngle = 60.0
    smoother.SetNumberOfIterations(smoothingIterations)
    smoother.BoundarySmoothingOff()
    smoother.FeatureEdgeSmoothingOff()
    smoother.SetFeatureAngle(featureAngle)
    smoother.SetPassBand(passBand)
    smoother.NonManifoldSmoothingOn()
    smoother.NormalizeCoordinatesOn()
    smoother.Update()

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(smoother.GetOutputPort())
    normals.SetFeatureAngle(featureAngle)

    stripper = vtk.vtkStripper()
    stripper.SetInputConnection(normals.GetOutputPort())

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(stripper.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    return actor


def CreateFrogActor(fileName, tissue, useMarchingCubes):
    reader = vtk.vtkMetaImageReader()
    reader.SetFileName(fileName)
    reader.Update()

    selectTissue = vtk.vtkImageThreshold()
    selectTissue.ThresholdBetween(tissue, tissue)
    selectTissue.SetInValue(255)
    selectTissue.SetOutValue(0)
    selectTissue.SetInputConnection(reader.GetOutputPort())

    gaussianRadius = 1
    gaussianStandardDeviation = 2.0
    gaussian = vtk.vtkImageGaussianSmooth()
    gaussian.SetStandardDeviations(gaussianStandardDeviation, gaussianStandardDeviation, gaussianStandardDeviation)
    gaussian.SetRadiusFactors(gaussianRadius, gaussianRadius, gaussianRadius)
    gaussian.SetInputConnection(selectTissue.GetOutputPort())

    isoValue = 127.5
    smoother = vtk.vtkWindowedSincPolyDataFilter()
    mcubes = vtk.vtkMarchingCubes()
    flyingEdges = vtk.vtkFlyingEdges3D()
    if useMarchingCubes:
        mcubes.SetInputConnection(gaussian.GetOutputPort())
        mcubes.ComputeScalarsOff()
        mcubes.ComputeGradientsOff()
        mcubes.ComputeNormalsOff()
        mcubes.SetValue(0, isoValue)
        smoother.SetInputConnection(mcubes.GetOutputPort())
    else:
        flyingEdges.SetInputConnection(gaussian.GetOutputPort())
        flyingEdges.ComputeScalarsOff()
        flyingEdges.ComputeGradientsOff()
        flyingEdges.ComputeNormalsOff()
        flyingEdges.SetValue(0, isoValue)
        smoother.SetInputConnection(flyingEdges.GetOutputPort())

    smoothingIterations = 5
    passBand = 0.001
    featureAngle = 60.0
    smoother.SetNumberOfIterations(smoothingIterations)
    smoother.BoundarySmoothingOff()
    smoother.FeatureEdgeSmoothingOff()
    smoother.SetFeatureAngle(featureAngle)
    smoother.SetPassBand(passBand)
    smoother.NonManifoldSmoothingOn()
    smoother.NormalizeCoordinatesOn()
    smoother.Update()

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(smoother.GetOutputPort())
    normals.SetFeatureAngle(featureAngle)

    stripper = vtk.vtkStripper()
    stripper.SetInputConnection(normals.GetOutputPort())

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(stripper.GetOutputPort())

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    return actor


if __name__ == '__main__':
    main()
