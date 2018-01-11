#!/usr/bin/env python

"""
Create an iso-surface of the Lorenz attractor.

Here we visualize a Lorenz strange attractor by integrating the Lorenz equations in a volume.
The number of visits in each voxel is recorded as a scalar function.
The surface is extracted via marching cubes using a visit value of 50.
The number of integration steps is 10 million, in a volume of dimensions 200 x 200 x 200.
The surface roughness is caused by the discrete nature of the evaluation function.

"""
import vtk


def main():
    colors = vtk.vtkNamedColors()

    Pr = 10.0  # The Lorenz parameters
    b = 2.667
    r = 28.0
    # x = 0.0
    # y = 0.0
    # z = 0.0  # starting (and current) x, y, z
    h = 0.01  # integration step size
    resolution = 200  # slice resolution
    iterations = 10000000  # number of iterations
    xmin = -30.0  # x, y, z range for voxels
    xmax = 30.0
    ymin = -30.0
    ymax = 30.0
    zmin = -10.0
    zmax = 60.0

    # Take a stab at an integration step size.
    xIncr = resolution / (xmax - xmin)
    yIncr = resolution / (ymax - ymin)
    zIncr = resolution / (zmax - zmin)

    print("The Lorenz Attractor\n")
    print(" Pr =", Pr)
    print(" b =", b)
    print(" r =", r)
    print(" integration step size =", h)
    print(" slice resolution =", resolution)
    print(" # of iterations =", iter)
    print(" specified range:")
    print("     x: {:f}, {:f}".format(xmin, xmax))
    print("     y: {:f}, {:f}".format(ymin, ymax))
    print("     z: {:f}, {:f}".format(zmin, zmax))

    x = vtk.vtkMath.Random(xmin, xmax)
    y = vtk.vtkMath.Random(ymin, ymax)
    z = vtk.vtkMath.Random(zmin, zmax)
    print(" starting at {:f}, {:f}, {:f}".format(x, y, z))
    # allocate memory for the slices
    sliceSize = resolution * resolution
    numPts = sliceSize * resolution
    scalars = vtk.vtkShortArray()
    for i in range(0, numPts):
        scalars.InsertTuple1(i, 0)
    for j in range(0, iterations):
        # Integrate to the next time step.
        xx = x + h * Pr * (y - x)
        yy = y + h * (x * (r - z) - y)
        zz = z + h * (x * y - (b * z))

        x = xx
        y = yy
        z = zz

        # Calculate the voxel index.
        if xmax > x > xmin and ymax > y > ymin and zmax > z > zmin:
            xxx = int(float(xx - xmin) * xIncr)
            yyy = int(float(yy - ymin) * yIncr)
            zzz = int(float(zz - zmin) * zIncr)
            index = xxx + yyy * resolution + zzz * sliceSize
            scalars.SetTuple1(index, scalars.GetTuple1(index) + 1)

    volume = vtk.vtkStructuredPoints()
    volume.GetPointData().SetScalars(scalars)
    volume.SetDimensions(resolution, resolution, resolution)
    volume.SetOrigin(xmin, ymin, zmin)
    volume.SetSpacing((xmax - xmin) / resolution, (ymax - ymin) / resolution, (zmax - zmin) / resolution)

    print(" contouring...")
    # Do the graphics dance.
    renderer = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Create iso-surface
    contour = vtk.vtkContourFilter()
    contour.SetInputData(volume)
    contour.SetValue(0, 50)

    # Create mapper.
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(contour.GetOutputPort())
    mapper.ScalarVisibilityOff()

    # Create actor.
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(colors.GetColor3d("PaleTurquoise"))

    renderer.AddActor(actor)
    renderer.SetBackground(colors.GetColor3d("PeachPuff"))

    renWin.SetSize(640, 480)

    # interact with data
    renWin.Render()

    iren.Start()


if __name__ == '__main__':
    main()
