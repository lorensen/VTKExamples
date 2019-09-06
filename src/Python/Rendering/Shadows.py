#!/usr/bin/env python

import vtk


def get_program_parameters():
    import argparse
    description = 'Read a polydata file of a surface and display it with shadows.'
    epilogue = '''
If no file is entered a sphere is used.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', default=None, nargs='?', help='Enter a polydata file e.g cow.g.')
    args = parser.parse_args()
    return args.filename


def ReadPolyData(file_name):
    import os
    path, extension = os.path.splitext(file_name)
    extension = extension.lower()
    if extension == ".ply":
        reader = vtk.vtkPLYReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".vtp":
        reader = vtk.vtkXMLpoly_dataReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".obj":
        reader = vtk.vtkOBJReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".stl":
        reader = vtk.vtkSTLReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".vtk":
        reader = vtk.vtkpoly_dataReader()
        reader.SetFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    elif extension == ".g":
        reader = vtk.vtkBYUReader()
        reader.SetGeometryFileName(file_name)
        reader.Update()
        poly_data = reader.GetOutput()
    else:
        # Return a None if the extension is unknown.
        poly_data = None
    return poly_data


def main():
    fn = get_program_parameters()
    if fn:
        polyData = ReadPolyData(fn)
    else:
        # Use a sphere
        source = vtk.vtkSphereSource()
        source.SetThetaResolution(100)
        source.SetPhiResolution(100)
        source.Update()
        polyData = source.GetOutput()

    colors = vtk.vtkNamedColors()
    colors.SetColor('HighNoonSun', [255, 255, 251, 255])  # Color temp. 5400°K
    colors.SetColor('100W Tungsten', [255, 214, 170, 255])  # Color temp. 2850°K

    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d('Silver'))

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.SetSize(640, 480)
    renderWindow.AddRenderer(renderer)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    light1 = vtk.vtkLight()
    light1.SetFocalPoint(0, 0, 0)
    light1.SetPosition(0, 1, 0.2)
    light1.SetColor(colors.GetColor3d('HighNoonSun'))
    light1.SetIntensity(0.3)
    renderer.AddLight(light1)

    light2 = vtk.vtkLight()
    light2.SetFocalPoint(0, 0, 0)
    light2.SetPosition(1.0, 1.0, 1.0)
    light2.SetColor(colors.GetColor3d('100W Tungsten'))
    light2.SetIntensity(0.8)
    renderer.AddLight(light2)

    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(polyData)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetAmbientColor(colors.GetColor3d('SaddleBrown'))
    actor.GetProperty().SetDiffuseColor(colors.GetColor3d('Sienna'))
    actor.GetProperty().SetSpecularColor(colors.GetColor3d('White'))
    actor.GetProperty().SetSpecular(0.51)
    actor.GetProperty().SetDiffuse(0.7)
    actor.GetProperty().SetAmbient(0.7)
    actor.GetProperty().SetSpecularPower(30.0)
    actor.GetProperty().SetOpacity(1.0)
    renderer.AddActor(actor)

    # Add a plane
    bounds = polyData.GetBounds()

    rnge = [0] * 3
    rnge[0] = bounds[1] - bounds[0]
    rnge[1] = bounds[3] - bounds[2]
    rnge[2] = bounds[5] - bounds[4]
    print("range: ", ', '.join(["{0:0.6f}".format(i) for i in rnge]))
    expand = 1.0
    THICKNESS = rnge[2] * 0.1
    plane = vtk.vtkCubeSource()
    plane.SetCenter((bounds[1] + bounds[0]) / 2.0,
                    bounds[2] + THICKNESS / 2.0,
                    (bounds[5] + bounds[4]) / 2.0)
    plane.SetXLength(bounds[1] - bounds[0] + (rnge[0] * expand))
    plane.SetYLength(THICKNESS)
    plane.SetZLength(bounds[5] - bounds[4] + (rnge[2] * expand))

    planeMapper = vtk.vtkPolyDataMapper()
    planeMapper.SetInputConnection(plane.GetOutputPort())

    planeActor = vtk.vtkActor()
    planeActor.SetMapper(planeMapper)
    renderer.AddActor(planeActor)

    renderWindow.SetMultiSamples(0)

    shadows = vtk.vtkShadowMapPass()

    seq = vtk.vtkSequencePass()

    passes = vtk.vtkRenderPassCollection()
    passes.AddItem(shadows.GetShadowMapBakerPass())
    passes.AddItem(shadows)
    seq.SetPasses(passes)

    cameraP = vtk.vtkCameraPass()
    cameraP.SetDelegatePass(seq)

    # Tell the renderer to use our render pass pipeline
    glrenderer = renderer
    glrenderer.SetPass(cameraP)

    renderer.GetActiveCamera().SetPosition(-0.2, 0.2, 1)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0, 1, 0)
    renderer.ResetCamera()
    renderer.GetActiveCamera().Dolly(2.25)
    renderer.ResetCameraClippingRange()
    renderWindow.SetWindowName('Shadows')
    renderWindow.Render()

    interactor.Start()


if __name__ == '__main__':
    main()
