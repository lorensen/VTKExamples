##!/usr/bin/env python

import vtk


def main():
    fileName = get_program_parameters()

    colors = vtk.vtkNamedColors()

    # Set the background color.
    colors.SetColor("BkgColor", [60, 93, 144, 255])

    # Read in an image and compute a luminance value. The image is extracted
    # as a set of polygons (vtkImageDataGeometryFilter). We then will
    # warp the plane using the scalar (luminance) values.
    #
    reader = vtk.vtkBMPReader()
    reader.SetFileName(fileName)
    # Convert the image to a grey scale.
    luminance = vtk.vtkImageLuminance()
    luminance.SetInputConnection(reader.GetOutputPort())
    # Pass the data to the pipeline as polygons.
    geometry = vtk.vtkImageDataGeometryFilter()
    geometry.SetInputConnection(luminance.GetOutputPort())
    # Warp the data in a direction perpendicular to the image plane.
    warp = vtk.vtkWarpScalar()
    warp.SetInputConnection(geometry.GetOutputPort())
    warp.SetScaleFactor(-0.1)

    # Use vtkMergeFilter to combine the original image with the warped geometry.
    merge = vtk.vtkMergeFilter()
    merge.SetGeometryConnection(warp.GetOutputPort())
    merge.SetScalarsConnection(reader.GetOutputPort())
    mapper = vtk.vtkDataSetMapper()
    mapper.SetInputConnection(merge.GetOutputPort())
    mapper.SetScalarRange(0, 255)
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Create the rendering window, renderer, and interactive renderer.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size.
    ren.AddActor(actor)
    ren.ResetCamera()
    ren.SetBackground(colors.GetColor3d("BkgColor"))
    # ren.GetActiveCamera().Azimuth(20)
    # ren.GetActiveCamera().Elevation(30)
    # ren.ResetCameraClippingRange()
    # ren.GetActiveCamera().Zoom(1.3)
    ren.GetActiveCamera().SetPosition(-100, -130, 325)
    ren.GetActiveCamera().SetFocalPoint(105, 114, -29)
    ren.GetActiveCamera().SetViewUp(0.51, 0.54, 0.67)
    ren.ResetCameraClippingRange()

    renWin.SetSize(512, 512)

    # Render the image.
    iren.Initialize()
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'ImageWarp.'
    epilogue = '''
This example shows how to combine data from both the imaging
 and graphics pipelines. The vtkMergeData filter is used to
 merge the data from each together.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filePrefix', help='Path to the masonry.bmp file.')
    args = parser.parse_args()
    return args.filePrefix


if __name__ == '__main__':
    main()
