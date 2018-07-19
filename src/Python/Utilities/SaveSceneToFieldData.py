#!/usr/bin/env python

import vtk


def main():
    pd_fn = get_program_parameters()

    colors = vtk.vtkNamedColors()

    polyData = ReadPolyData(pd_fn)
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputData(polyData)

    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetDiffuseColor(colors.GetColor3d("Crimson"))
    actor.GetProperty().SetSpecular(.6)
    actor.GetProperty().SetSpecularPower(30)

    renderer = vtk.vtkRenderer()
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindowInteractor = vtk.vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("Silver"))

    # Interact to change camera.
    renderWindow.Render()
    renderWindowInteractor.Start()

    # After the interaction is done, save the scene.
    SaveSceneToFieldData(polyData, actor, renderer.GetActiveCamera())
    renderWindow.Render()
    renderWindowInteractor.Start()

    # After interaction , restore the scene.
    RestoreSceneFromFieldData(polyData, actor, renderer.GetActiveCamera())
    renderWindow.Render()
    renderWindowInteractor.Start()


def get_program_parameters():
    import argparse
    description = 'Saving a scene to field data.'
    epilogue = '''
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('data_file', help='A polydata file e.g. Armadillo.ply.')
    args = parser.parse_args()
    return args.data_file


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


def SaveSceneToFieldData(data, actor, camera):
    # Actor
    #   Position, orientation, origin, scale, usrmatrix, usertransform
    # Camera
    #   FocalPoint, Position, ViewUp, ViewAngle, ClippingRange

    fp_format = '{0:.6f}'
    res = dict()
    res['Camera:FocalPoint'] = ', '.join(fp_format.format(n) for n in camera.GetFocalPoint())
    res['Camera:Position'] = ', '.join(fp_format.format(n) for n in camera.GetPosition())
    res['Camera:ViewUp'] = ', '.join(fp_format.format(n) for n in camera.GetViewUp())
    res['Camera:ViewAngle'] = fp_format.format(camera.GetViewAngle())
    res['Camera:ClippingRange'] = ', '.join(fp_format.format(n) for n in camera.GetClippingRange())
    buffer = ''
    for k, v in res.items():
        buffer += k + ' ' + v + '\n'
    cameraArray = vtk.vtkStringArray()
    cameraArray.SetNumberOfValues(1)
    cameraArray.SetValue(0, buffer)
    cameraArray.SetName("Camera")
    data.GetFieldData().AddArray(cameraArray)


def RestoreSceneFromFieldData(data, actor, camera):
    import re

    # Some regular expressions.

    reCP = re.compile(r'^Camera:Position')
    reCFP = re.compile(r'^Camera:FocalPoint')
    reCVU = re.compile(r'^Camera:ViewUp')
    reCVA = re.compile(r'^Camera:ViewAngle')
    reCCR = re.compile(r'^Camera:ClippingRange')
    keys = [reCP, reCFP, reCVU, reCVA, reCCR]

    # float_number = re.compile(r'[^0-9.\-]*([0-9e.\-]*[^,])[^0-9.\-]*([0-9e.\-]*[^,])[^0-9.\-]*([0-9e.\-]*[^,])')
    # float_scalar = re.compile(r'[^0-9.\-]*([0-9.\-e]*[^,])')

    buffer = data.GetFieldData().GetAbstractArray("Camera").GetValue(0).split('\n')
    res = dict()
    for line in buffer:
        if not line.strip():
            continue
        line = line.strip().replace(',', '').split()
        for i in keys:
            m = re.match(i, line[0])
            if m:
                k = m.group(0)
                if m:
                    #  Convert the rest of the line to floats.
                    v = list(map(lambda x: float(x), line[1:]))
                    if len(v) == 1:
                        res[k] = v[0]
                    else:
                        res[k] = v
    for k, v in res.items():
        if re.match(reCP, k):
            camera.SetPosition(v)
        elif re.match(reCFP, k):
            camera.SetFocalPoint(v)
        elif re.match(reCVU, k):
            camera.SetViewUp(v)
        elif re.match(reCVA, k):
            camera.SetViewAngle(v)
        elif re.match(reCCR, k):
            camera.SetClippingRange(v)


if __name__ == '__main__':
    main()
