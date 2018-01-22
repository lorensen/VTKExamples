#!/usr/bin/env python

"""
"""

import vtk

def view_frog(fileName, tissues):
    colors = vtk.vtkNamedColors()

    tissueMap = CreateTissueMap()
    colorLut = CreateFrogLut()

    # Setup render window, renderer, and interactor.
    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    for tissue in tissues:
        actor = CreateFrogActor(fileName, tissueMap[tissue])
        actor.GetProperty().SetDiffuseColor( colorLut.GetTableValue(tissueMap[tissue])[:3])
        actor.GetProperty().SetSpecular(.5)
        actor.GetProperty().SetSpecularPower(10)
        renderer.AddActor(actor)
        # print("Tissue:", tissue, ", Label:", tissueMap[tissue])


    renderer.GetActiveCamera().SetViewUp(0, 0, -1)
    renderer.GetActiveCamera().SetPosition(0, -1, 0)

    renderer.GetActiveCamera().Azimuth(210)
    renderer.GetActiveCamera().Elevation(30)
    renderer.ResetCamera()
    renderer.ResetCameraClippingRange()
    renderer.GetActiveCamera().Dolly(1.5)
    renderer.SetBackground(colors.GetColor3d("SlateGray"))

    renderWindow.SetSize(640, 480)
    renderWindow.Render()

    renderWindowInteractor.Start()

def main():
    fileName, tissues = get_program_parameters()
    view_frog(fileName, tissues)


def get_program_parameters():
    import argparse
    description = 'The complete frog without skin.'
    epilogue = '''
    For Figure 12-9b in the VTK Book:
    Specify these tissues as parameters after the file name:
      blood brain duodenum eyeRetina eyeWhite heart ileum kidney intestine liver lung nerve skeleton spleen stomach    
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='frogtissue.mhd.')
    parser.add_argument('tissues', nargs='+',  help='List of one or more tissues.')
    args = parser.parse_args()
    return args.filename, args.tissues


def CreateFrogLut():
    colors = vtk.vtkNamedColors()

    colorLut = vtk.vtkLookupTable()
    colorLut.SetNumberOfColors(17)
    colorLut.SetTableRange(0, 16)
    colorLut.Build()

    colorLut.SetTableValue(0, 0, 0, 0, 0)
    colorLut.SetTableValue(1, colors.GetColor4d("salmon"))  # blood
    colorLut.SetTableValue(2, colors.GetColor4d("beige"))  # brain
    colorLut.SetTableValue(3, colors.GetColor4d("orange"))  # duodenum
    colorLut.SetTableValue(4, colors.GetColor4d("misty_rose"))  # eye_retina
    colorLut.SetTableValue(5, colors.GetColor4d("white"))  # eye_white
    colorLut.SetTableValue(6, colors.GetColor4d("tomato"))  # heart
    colorLut.SetTableValue(7, colors.GetColor4d("raspberry"))  # ileum
    colorLut.SetTableValue(8, colors.GetColor4d("banana"))  # kidney
    colorLut.SetTableValue(9, colors.GetColor4d("peru"))  # l_intestine
    colorLut.SetTableValue(10, colors.GetColor4d("pink"))  # liver
    colorLut.SetTableValue(11, colors.GetColor4d("powder_blue"))  # lung
    colorLut.SetTableValue(12, colors.GetColor4d("carrot"))  # nerve
    colorLut.SetTableValue(13, colors.GetColor4d("wheat"))  # skeleton
    colorLut.SetTableValue(14, colors.GetColor4d("violet"))  # spleen
    colorLut.SetTableValue(15, colors.GetColor4d("plum"))  # stomach

    return colorLut


def CreateTissueMap():
    tissueMap = dict()
    tissueMap["blood"] = 1
    tissueMap["brain"] = 2
    tissueMap["duodenum"] = 3
    tissueMap["eyeRetina"] = 4
    tissueMap["eyeWhite"] = 5
    tissueMap["heart"] = 6
    tissueMap["ileum"] = 7
    tissueMap["kidney"] = 8
    tissueMap["intestine"] = 9
    tissueMap["liver"] = 10
    tissueMap["lung"] = 11
    tissueMap["nerve"] = 12
    tissueMap["skeleton"] = 13
    tissueMap["spleen"] = 14
    tissueMap["stomach"] = 15

    return tissueMap


def CreateFrogActor(fileName, tissue):
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
    mcubes = vtk.vtkMarchingCubes()
    mcubes.SetInputConnection(gaussian.GetOutputPort())
    mcubes.ComputeScalarsOff()
    mcubes.ComputeGradientsOff()
    mcubes.ComputeNormalsOff()
    mcubes.SetValue(0, isoValue)

    smoothingIterations = 5
    passBand = 0.001
    featureAngle = 60.0
    smoother = vtk.vtkWindowedSincPolyDataFilter()
    smoother.SetInputConnection(mcubes.GetOutputPort())
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
