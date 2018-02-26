#!/usr/bin/env python
# -*- coding: utf-8 -*-

import vtk

def main(filename):
    print("Loading", filename)
    reader = vtk.vtkUnstructuredGridReader()
    reader.SetFileName(filename)

    edges = vtk.vtkExtractEdges()
    edges.SetInputConnection(reader.GetOutputPort())

    tubes = vtk.vtkTubeFilter()
    tubes.SetInputConnection(edges.GetOutputPort())
    tubes.SetRadius(0.0625)
    tubes.SetVaryRadiusToVaryRadiusOff()
    tubes.SetNumberOfSides(32)

    tubesMapper = vtk.vtkPolyDataMapper()
    tubesMapper.SetInputConnection(tubes.GetOutputPort())
    tubesMapper.SetScalarRange(0.0, 26.0)

    tubesActor = vtk.vtkActor()
    tubesActor.SetMapper(tubesMapper)

    gradients = vtk.vtkGradientFilter()
    gradients.SetInputConnection(reader.GetOutputPort())

    vectors = vtk.vtkAssignAttribute()
    vectors.SetInputConnection(gradients.GetOutputPort())
    vectors.Assign("Gradients", vtk.vtkDataSetAttributes.VECTORS, \
        vtk.vtkAssignAttribute.POINT_DATA)

    arrow = vtk.vtkArrowSource()

    glyphs = vtk.vtkGlyph3D()
    glyphs.SetInputConnection(0, vectors.GetOutputPort())
    glyphs.SetInputConnection(1, arrow.GetOutputPort())
    glyphs.ScalingOn()
    glyphs.SetScaleModeToScaleByVector()
    glyphs.SetScaleFactor(0.25)
    glyphs.OrientOn()
    glyphs.ClampingOff()
    glyphs.SetVectorModeToUseVector()
    glyphs.SetIndexModeToOff()

    glyphMapper = vtk.vtkPolyDataMapper()
    glyphMapper.SetInputConnection(glyphs.GetOutputPort())
    glyphMapper.ScalarVisibilityOff()

    glyphActor = vtk.vtkActor()
    glyphActor.SetMapper(glyphMapper)

    renderer = vtk.vtkRenderer()
    renderer.AddActor(tubesActor)
    renderer.AddActor(glyphActor)
    renderer.SetBackground(0.328125, 0.347656, 0.425781)

    renwin = vtk.vtkRenderWindow()
    renwin.AddRenderer(renderer)
    renwin.SetSize(350, 500)

    renderer.ResetCamera()
    camera = renderer.GetActiveCamera()
    camera.Elevation(-80.0)
    camera.OrthogonalizeViewUp()
    camera.Azimuth(135.0)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renwin)
    iren.Initialize()
    iren.Start()
    return 1

def get_program_parameters():
    import argparse
    description = 'Computes the gradient of a scalar field defined on the points of a data set.'
    epilogue = '''
    filename=./src/Testing/Data/uGridEx.vtk
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='Filename.vtk')
    args = parser.parse_args()
    return args.filename

if __name__ == "__main__":
    main(get_program_parameters())
