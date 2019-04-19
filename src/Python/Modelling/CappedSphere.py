#!/usr/bin/env python

import math

import vtk


def get_program_parameters():
    import argparse
    description = 'Display a capped sphere.'
    epilogue = '''
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('angle', default=90, type=float, nargs='?',
                        help='The length of the arc in degrees from +z to -z in the +x direction in the x-z plane.')
    parser.add_argument('step', default=1, type=float, nargs='?', help='Step size in degrees.')
    parser.add_argument('radius', default=1, type=float, nargs='?', help='Radius of the arc.')
    parser.add_argument('-u', '--uncapped', action='store_true', help='Uncap the sphere.')
    parser.add_argument('-s', '--show_line', action='store_true',
                        help='Show the line that is rotationally extruded to make the surface.')
    args = parser.parse_args()
    return args.angle, args.step, args.radius, args.uncapped, args.show_line


def main():
    angle, step, radius, uncapped, show_line = get_program_parameters()
    angle = math.radians(abs(angle))
    step = math.radians(abs(step))
    radius = abs(radius)
    # With default settings set this to 45 and you get a bowl with a flat bottom.
    start = math.radians(90)

    pts = get_line(angle, step, radius, uncapped, start)

    # Setup points and lines
    points = vtk.vtkPoints()
    lines = vtk.vtkCellArray()
    for pt in pts:
        pt_id = points.InsertNextPoint(pt)
        if pt_id < len(pts) - 1:
            line = vtk.vtkLine()
            line.GetPointIds().SetId(0, pt_id)
            line.GetPointIds().SetId(1, pt_id + 1)
            lines.InsertNextCell(line)

    polydata = vtk.vtkPolyData()
    polydata.SetPoints(points)
    polydata.SetLines(lines)

    # Extrude the profile to make the capped sphere
    extrude = vtk.vtkRotationalExtrusionFilter()
    extrude.SetInputData(polydata)
    extrude.SetResolution(60)

    #  Visualize
    colors = vtk.vtkNamedColors()

    # To see the line
    lineMapper = vtk.vtkPolyDataMapper()
    lineMapper.SetInputData(polydata)

    lineActor = vtk.vtkActor()
    lineActor.SetMapper(lineMapper)
    lineActor.GetProperty().SetLineWidth(4)
    lineActor.GetProperty().SetColor(colors.GetColor3d("Red"))

    # To see the surface
    surfaceMapper = vtk.vtkPolyDataMapper()
    surfaceMapper.SetInputConnection(extrude.GetOutputPort())

    surfaceActor = vtk.vtkActor()
    surfaceActor.SetMapper(surfaceMapper)
    surfaceActor.GetProperty().SetColor(colors.GetColor3d('Khaki'))

    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    ren.AddActor(surfaceActor)
    if show_line:
        ren.AddActor(lineActor)
    ren.SetBackground(colors.GetColor3d('LightSlateGray'))

    ren.ResetCamera()
    ren.GetActiveCamera().Azimuth(0)
    ren.GetActiveCamera().Elevation(60)
    ren.ResetCameraClippingRange()

    renWin.SetSize(600, 600)
    renWin.Render()
    renWin.SetWindowName('CappedSphere')
    iren.Start()


def get_line(angle, step, radius, uncapped, start):
    """
    Get the points for a line.

    :param angle: Length of the arc in degrees.
    :param step: Step size in degrees.
    :param radius: Radius of the arc.
    :param uncapped: True if uncapped.
    :param start: Starting angle.
    :return: A vector of points.
    """
    precision = 1.0e-6
    pts = list()
    # Do the curved line
    theta = 0.0
    while theta <= angle:
        x = radius * math.cos(start - theta)
        z = radius * math.sin(theta - start)
        if x < 0:
            x = 0
            pts.append((x, 0, z))
            break
        if abs(x) < precision:
            x = 0
        if abs(z) < precision:
            z = 0
        pts.append((x, 0, z))
        theta += step

    if not uncapped:
        # Drop a perpendicular from the last point to the x-axis
        if len(pts) > 1:
            if pts[-1][0] > 0:
                last_point = pts[-1]
                num_pts = 10
                interval = float(num_pts) / radius
                for i in range(1, num_pts):
                    x = last_point[0] - i / interval
                    z = last_point[2]
                    if x < 0:
                        x = 0
                        pts.append((x, 0, z))
                        break
                    if abs(x) < precision:
                        x = 0
                    if abs(z) < precision:
                        z = 0
                    pts.append((x, 0, z))
            if pts[-1][0] > precision:
                pts.append((0, 0, pts[-1][2]))
    return pts


if __name__ == '__main__':
    main()
