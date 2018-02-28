#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName1, fileName2, fileName3 = get_program_parameters()
    aRenderer = vtk.vtkRenderer()
    aRenderWindow = vtk.vtkRenderWindow()
    aRenderWindow.AddRenderer(aRenderer)
    anInteractor = vtk.vtkRenderWindowInteractor()
    anInteractor.SetRenderWindow(aRenderWindow)
    aRenderWindow.SetSize(300, 300)

    # Read the geometry file containing the letter v.
    letterV = vtk.vtkPolyDataReader()
    letterV.SetFileName(fileName1)

    # Read the geometry file containing the letter t.
    letterT = vtk.vtkPolyDataReader()
    letterT.SetFileName(fileName2)

    # Read the geometry file containing the letter k.
    letterK = vtk.vtkPolyDataReader()
    letterK.SetFileName(fileName3)

    # Create a transform and transform filter for each letter.
    VTransform = vtk.vtkTransform()
    VTransformFilter = vtk.vtkTransformPolyDataFilter()
    VTransformFilter.SetInputConnection(letterV.GetOutputPort())
    VTransformFilter.SetTransform(VTransform)

    TTransform = vtk.vtkTransform()
    TTransformFilter = vtk.vtkTransformPolyDataFilter()
    TTransformFilter.SetInputConnection(letterT.GetOutputPort())
    TTransformFilter.SetTransform(TTransform)

    KTransform = vtk.vtkTransform()
    KTransformFilter = vtk.vtkTransformPolyDataFilter()
    KTransformFilter.SetInputConnection(letterK.GetOutputPort())
    KTransformFilter.SetTransform(KTransform)

    # Now append them all.
    appendAll = vtk.vtkAppendPolyData()
    appendAll.AddInputConnection(VTransformFilter.GetOutputPort())
    appendAll.AddInputConnection(TTransformFilter.GetOutputPort())
    appendAll.AddInputConnection(KTransformFilter.GetOutputPort())

    # Create normals.
    logoNormals = vtk.vtkPolyDataNormals()
    logoNormals.SetInputConnection(appendAll.GetOutputPort())
    logoNormals.SetFeatureAngle(60)

    # Map to rendering primitives.
    logoMapper = vtk.vtkPolyDataMapper()
    logoMapper.SetInputConnection(logoNormals.GetOutputPort())

    # Now an actor.
    logo = vtk.vtkActor()
    logo.SetMapper(logoMapper)

    # Now create an implicit model of the same letter.
    blobbyLogoImp = vtk.vtkImplicitModeller()
    blobbyLogoImp.SetInputConnection(appendAll.GetOutputPort())
    blobbyLogoImp.SetMaximumDistance(.075)
    blobbyLogoImp.SetSampleDimensions(64, 64, 64)
    blobbyLogoImp.SetAdjustDistance(0.05)

    # Extract an iso surface.
    blobbyLogoIso = vtk.vtkContourFilter()
    blobbyLogoIso.SetInputConnection(blobbyLogoImp.GetOutputPort())
    blobbyLogoIso.SetValue(1, 1.5)

    # Map to rendering primitives.
    blobbyLogoMapper = vtk.vtkPolyDataMapper()
    blobbyLogoMapper.SetInputConnection(blobbyLogoIso.GetOutputPort())
    blobbyLogoMapper.ScalarVisibilityOff()

    tomato = vtk.vtkProperty()
    tomato.SetDiffuseColor(colors.GetColor3d("tomato"))
    tomato.SetSpecular(.3)
    tomato.SetSpecularPower(20)

    banana = vtk.vtkProperty()
    banana.SetDiffuseColor(colors.GetColor3d("banana"))
    banana.SetDiffuse(.7)
    banana.SetSpecular(.4)
    banana.SetSpecularPower(20)

    # Now an actor.
    blobbyLogo = vtk.vtkActor()
    blobbyLogo.SetMapper(blobbyLogoMapper)
    blobbyLogo.SetProperty(banana)

    # Position the letters.

    VTransform.Translate(-16.0, 0.0, 12.5)
    VTransform.RotateY(40)

    KTransform.Translate(14.0, 0.0, 0.0)
    KTransform.RotateY(-40)

    # Move the polygonal letters to the front.
    logo.SetProperty(tomato)
    logo.SetPosition(0, 0, 6)

    aRenderer.AddActor(logo)
    aRenderer.AddActor(blobbyLogo)

    aRenderer.SetBackground(colors.GetColor3d("SlateGray"))

    aRenderWindow.Render()

    # Interact with the data.
    anInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Use implicit modeller to create the VTK logo.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue)
    parser.add_argument('filename1', help='v.vtk.')
    parser.add_argument('filename2', help='t.vtk.')
    parser.add_argument('filename3', help='k.vtk.')
    args = parser.parse_args()
    return args.filename1, args.filename2, args.filename3


if __name__ == '__main__':
    main()
