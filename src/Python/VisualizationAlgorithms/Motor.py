#!/usr/bin/env python

# This code is based on the VTK file: /IO/Geometry/Testing/Python/motor.py.

import vtk


def main():
    colors = vtk.vtkNamedColors()

    textureFile, motorFile = get_program_parameters()

    # Create the Renderer, RenderWindow and RenderWindowInteractor.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create the cutting planes.
    planes = vtk.vtkPlanes()
    points = vtk.vtkPoints()
    norms = vtk.vtkFloatArray()

    norms.SetNumberOfComponents(3)
    points.InsertPoint(0, 0.0, 0.0, 0.0)
    norms.InsertTuple3(0, 0.0, 0.0, 1.0)
    points.InsertPoint(1, 0.0, 0.0, 0.0)
    norms.InsertTuple3(1, -1.0, 0.0, 0.0)
    planes.SetPoints(points)
    planes.SetNormals(norms)

    # Get the texture.
    texReader = vtk.vtkStructuredPointsReader()
    texReader.SetFileName(textureFile)
    texture = vtk.vtkTexture()
    texture.SetInputConnection(texReader.GetOutputPort())
    texture.InterpolateOff()
    texture.RepeatOff()

    # Set up the pipelines for the parts of the motor.
    # We will use lists of pipeline objects.
    numberOfParts = 5
    byu = list()
    normals = list()
    tex = list()
    byuMapper = list()
    byuActor = list()
    partColours = ['cold_grey', 'peacock', 'raw_sienna', 'banana', 'peach_puff']
    # Use this to control which parts to display.
    displayParts = [True] * numberOfParts
    # If displayParts[2] = False then an image like that in the VTK tests is produced.

    # Build the pipelines.
    for i in range(0, numberOfParts):
        byu.append(vtk.vtkBYUReader())
        byu[i].SetGeometryFileName(motorFile)
        byu[i].SetPartNumber(i + 1)

        normals.append(vtk.vtkPolyDataNormals())
        normals[i].SetInputConnection(byu[i].GetOutputPort())

        tex.append(vtk.vtkImplicitTextureCoords())
        tex[i].SetInputConnection(normals[i].GetOutputPort())
        tex[i].SetRFunction(planes)
        # tex[i].FlipTextureOn()

        byuMapper.append(vtk.vtkDataSetMapper())
        byuMapper[i].SetInputConnection(tex[i].GetOutputPort())

        byuActor.append(vtk.vtkActor())
        byuActor[i].SetMapper(byuMapper[i])
        byuActor[i].SetTexture(texture)
        byuActor[i].GetProperty().SetColor(colors.GetColor3d(partColours[i]))

        ren.AddActor(byuActor[i])
        if displayParts[i]:
            byuActor[i].VisibilityOn()
        else:
            byuActor[i].VisibilityOff()

    ren.SetBackground(colors.GetColor3d('AliceBlue'))

    renWin.SetSize(512, 512)

    camera = vtk.vtkCamera()
    camera.SetFocalPoint(0.0286334, 0.0362996, 0.0379685)
    camera.SetPosition(1.37067, 1.08629, -1.30349)
    camera.SetViewAngle(17.673)
    camera.SetClippingRange(1, 10)
    camera.SetViewUp(-0.376306, -0.5085, -0.774482)
    ren.SetActiveCamera(camera)

    # Render the image.
    iren.Initialize()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Texture clipping using a transparent texture map.'
    epilogue = '''
        Texture clipping using a transparent texture map.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('textureFile', help='The texture file: texThres2.vtk.')
    parser.add_argument('motorFile', help='The motor file: motor.g.')
    args = parser.parse_args()
    return args.textureFile, args.motorFile


if __name__ == '__main__':
    main()
