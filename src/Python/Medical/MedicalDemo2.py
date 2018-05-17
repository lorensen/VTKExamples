#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    colors.SetColor("SkinColor", [255, 125, 64, 255])
    colors.SetColor("BkgColor", [51, 77, 102, 255])

    # Create the renderer, the render window, and the interactor. The renderer
    # draws into the render window, the interactor enables mouse- and
    # keyboard-based interaction with the data within the render window.
    #
    aRenderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(aRenderer)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # The following reader is used to read a series of 2D slices (images)
    # that compose the volume. The slice dimensions are set, and the
    # pixel spacing. The data Endianness must also be specified. The reader
    # uses the FilePrefix in combination with the slice number to construct
    # filenames using the format FilePrefix.%d. (In this case the FilePrefix
    # is the root name of the file: quarter.)
    reader = vtk.vtkMetaImageReader()
    reader.SetFileName(fileName)

    # An isosurface, or contour value of 500 is known to correspond to the
    # skin of the patient.
    # The triangle stripper is used to create triangle strips from the
    # isosurface these render much faster on many systems.
    skinExtractor = vtk.vtkMarchingCubes()
    skinExtractor.SetInputConnection(reader.GetOutputPort())
    skinExtractor.SetValue(0, 500)

    skinStripper = vtk.vtkStripper()
    skinStripper.SetInputConnection(skinExtractor.GetOutputPort())

    skinMapper = vtk.vtkPolyDataMapper()
    skinMapper.SetInputConnection(skinStripper.GetOutputPort())
    skinMapper.ScalarVisibilityOff()

    skin = vtk.vtkActor()
    skin.SetMapper(skinMapper)
    skin.GetProperty().SetDiffuseColor(colors.GetColor3d("SkinColor"))
    skin.GetProperty().SetSpecular(.3)
    skin.GetProperty().SetSpecularPower(20)
    skin.GetProperty().SetOpacity(.5)

    # An isosurface, or contour value of 1150 is known to correspond to the
    # bone of the patient.
    # The triangle stripper is used to create triangle strips from the
    # isosurface these render much faster on may systems.
    boneExtractor = vtk.vtkMarchingCubes()
    boneExtractor.SetInputConnection(reader.GetOutputPort())
    boneExtractor.SetValue(0, 1150)

    boneStripper = vtk.vtkStripper()
    boneStripper.SetInputConnection(boneExtractor.GetOutputPort())

    boneMapper = vtk.vtkPolyDataMapper()
    boneMapper.SetInputConnection(boneStripper.GetOutputPort())
    boneMapper.ScalarVisibilityOff()

    bone = vtk.vtkActor()
    bone.SetMapper(boneMapper)
    bone.GetProperty().SetDiffuseColor(colors.GetColor3d("Ivory"))

    # An outline provides context around the data.
    #
    outlineData = vtk.vtkOutlineFilter()
    outlineData.SetInputConnection(reader.GetOutputPort())

    mapOutline = vtk.vtkPolyDataMapper()
    mapOutline.SetInputConnection(outlineData.GetOutputPort())

    outline = vtk.vtkActor()
    outline.SetMapper(mapOutline)
    outline.GetProperty().SetColor(colors.GetColor3d("Black"))

    # It is convenient to create an initial view of the data. The FocalPoint
    # and Position form a vector direction. Later on (ResetCamera() method)
    # this vector is used to position the camera to look at the data in
    # this direction.
    aCamera = vtk.vtkCamera()
    aCamera.SetViewUp(0, 0, -1)
    aCamera.SetPosition(0, -1, 0)
    aCamera.SetFocalPoint(0, 0, 0)
    aCamera.ComputeViewPlaneNormal()
    aCamera.Azimuth(30.0)
    aCamera.Elevation(30.0)

    # Actors are added to the renderer. An initial camera view is created.
    # The Dolly() method moves the camera towards the FocalPoint,
    # thereby enlarging the image.
    aRenderer.AddActor(outline)
    aRenderer.AddActor(skin)
    aRenderer.AddActor(bone)
    aRenderer.SetActiveCamera(aCamera)
    aRenderer.ResetCamera()
    aCamera.Dolly(1.5)

    # Set a background color for the renderer and set the size of the
    # render window (expressed in pixels).
    aRenderer.SetBackground(colors.GetColor3d("BkgColor"))
    renWin.SetSize(640, 480)

    # Note that when camera movement occurs (as it does in the Dolly()
    # method), the clipping planes often need adjusting. Clipping planes
    # consist of two planes: near and far along the view direction. The
    # near plane clips out objects in front of the plane the far plane
    # clips out objects behind the plane. This way only what is drawn
    # between the planes is actually rendered.
    aRenderer.ResetCameraClippingRange()

    # Initialize the event loop and then start it.
    iren.Initialize()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'The skin and bone is extracted from a CT dataset of the head.'
    epilogue = '''
    Derived from VTK/Examples/Cxx/Medical2.cxx
    This example reads a volume dataset, extracts two isosurfaces that
     represent the skin and bone, and then displays it.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='FullHead.mhd.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
