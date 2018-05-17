#!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()

    fran = vtk.vtkPolyDataReader()
    fran.SetFileName(fileName)

    normals = vtk.vtkPolyDataNormals()
    normals.SetInputConnection(fran.GetOutputPort())
    normals.FlipNormalsOn()

    franMapper = vtk.vtkPolyDataMapper()
    franMapper.SetInputConnection(normals.GetOutputPort())

    franActor = vtk.vtkActor()
    franActor.SetMapper(franMapper)
    franActor.GetProperty().SetColor(colors.GetColor3d("Flesh"))

    # We subsample the dataset because we want to glyph just a subset of
    # the points. Otherwise the display is cluttered and cannot be easily
    # read. The RandomModeOn and SetOnRatio combine to random select one out
    # of every 10 points in the dataset.
    #
    ptMask = vtk.vtkMaskPoints()
    ptMask.SetInputConnection(normals.GetOutputPort())
    ptMask.SetOnRatio(10)
    ptMask.RandomModeOn()

    # In this case we are using a cone as a glyph. We transform the cone so
    # its base is at 0,0,0. This is the point where glyph rotation occurs.
    cone = vtk.vtkConeSource()
    cone.SetResolution(6)

    transform = vtk.vtkTransform()
    transform.Translate(0.5, 0.0, 0.0)

    transformF = vtk.vtkTransformPolyDataFilter()
    transformF.SetInputConnection(cone.GetOutputPort())
    transformF.SetTransform(transform)

    # vtkGlyph3D takes two inputs: the input point set (SetInputConnection)
    # which can be any vtkDataSet and the glyph (SetSourceConnection) which
    # must be a vtkPolyData.  We are interested in orienting the glyphs by the
    # surface normals that we previously generated.
    glyph = vtk.vtkGlyph3D()
    glyph.SetInputConnection(ptMask.GetOutputPort())
    glyph.SetSourceConnection(transformF.GetOutputPort())
    glyph.SetVectorModeToUseNormal()
    glyph.SetScaleModeToScaleByVector()
    glyph.SetScaleFactor(0.004)

    spikeMapper = vtk.vtkPolyDataMapper()
    spikeMapper.SetInputConnection(glyph.GetOutputPort())

    spikeActor = vtk.vtkActor()
    spikeActor.SetMapper(spikeMapper)
    spikeActor.GetProperty().SetColor(colors.GetColor3d("Emerald_Green"))

    # Create the RenderWindow, Renderer and Interactor.
    #
    ren1 = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren1)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size.
    #
    ren1.AddActor(franActor)
    ren1.AddActor(spikeActor)

    renWin.SetSize(640, 480)
    ren1.SetBackground(colors.GetColor3d("SlateGray"))

    # Render the image.
    #
    renWin.Render()

    ren1.GetActiveCamera().Zoom(1.4)
    ren1.GetActiveCamera().Azimuth(110)
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'This example demonstrates the use of glyphing.'
    epilogue = '''
    We also use a mask filter to select a subset of points to glyph.
    
    About the data file:
      This originally was a Cyberware laser digitizer scan
      of Fran J.'s face. Surface normals are generated based on local geometry
      (i.e., the polygon normals surrounding each point are averaged). We flip
      the normals because we want them to point out from Fran's face.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='fran_cut.vtk.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
