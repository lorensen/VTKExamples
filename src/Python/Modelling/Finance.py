#!/usr/bin/env python

"""
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    colors.SetColor("PopColor", [230, 230, 230, 255])

    fileName = get_program_parameters()

    keys = ['NUMBER_POINTS', 'MONTHLY_PAYMENT', 'INTEREST_RATE', 'LOAN_AMOUNT', 'TIME_LATE']

    # Read in the data and make an unstructured data set.
    dataSet = make_dataset(fileName, keys)

    # Construct the pipeline for the original population.
    popSplatter = vtk.vtkGaussianSplatter()
    popSplatter.SetInputData(dataSet)
    popSplatter.SetSampleDimensions(100, 100, 100)
    popSplatter.SetRadius(0.05)
    popSplatter.ScalarWarpingOff()

    popSurface = vtk.vtkContourFilter()
    popSurface.SetInputConnection(popSplatter.GetOutputPort())
    popSurface.SetValue(0, 0.01)

    popMapper = vtk.vtkPolyDataMapper()
    popMapper.SetInputConnection(popSurface.GetOutputPort())
    popMapper.ScalarVisibilityOff()

    popActor = vtk.vtkActor()
    popActor.SetMapper(popMapper)
    popActor.GetProperty().SetOpacity(0.3)
    popActor.GetProperty().SetColor(colors.GetColor3d("PopColor"))

    # Construct the pipeline for the delinquent population.
    lateSplatter = vtk.vtkGaussianSplatter()
    lateSplatter.SetInputData(dataSet)
    lateSplatter.SetSampleDimensions(50, 50, 50)
    lateSplatter.SetRadius(0.05)
    lateSplatter.SetScaleFactor(0.005)

    lateSurface = vtk.vtkContourFilter()
    lateSurface.SetInputConnection(lateSplatter.GetOutputPort())
    lateSurface.SetValue(0, 0.01)

    lateMapper = vtk.vtkPolyDataMapper()
    lateMapper.SetInputConnection(lateSurface.GetOutputPort())
    lateMapper.ScalarVisibilityOff()

    lateActor = vtk.vtkActor()
    lateActor.SetMapper(lateMapper)
    lateActor.GetProperty().SetColor(colors.GetColor3d("Red"))

    # Create axes.
    popSplatter.Update()
    bounds = popSplatter.GetOutput().GetBounds()

    axes = vtk.vtkAxes()
    axes.SetOrigin(bounds[0], bounds[2], bounds[4])
    axes.SetScaleFactor(popSplatter.GetOutput().GetLength() / 5)

    axesTubes = vtk.vtkTubeFilter()
    axesTubes.SetInputConnection(axes.GetOutputPort())
    axesTubes.SetRadius(axes.GetScaleFactor() / 25.0)
    axesTubes.SetNumberOfSides(6)

    axesMapper = vtk.vtkPolyDataMapper()
    axesMapper.SetInputConnection(axesTubes.GetOutputPort())

    axesActor = vtk.vtkActor()
    axesActor.SetMapper(axesMapper)

    # Graphics stuff.
    renderer = vtk.vtkRenderer()

    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(renderer)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renWin)

    # Set up the renderer.
    renderer.AddActor(lateActor)
    renderer.AddActor(axesActor)
    renderer.AddActor(popActor)
    renderer.SetBackground(colors.GetColor3d("Wheat"))
    renWin.SetSize(640, 480)

    renderer.ResetCamera()
    renderer.GetActiveCamera().Dolly(1.3)
    renderer.ResetCameraClippingRange()

    # Interact with the data.
    renWin.Render()
    interactor.Start()


def get_program_parameters():
    import argparse
    description = 'Visualization of multidimensional financial data.'
    epilogue = '''
    The gray/wireframe surface represents the total data population.
    The red surface represents data points delinquent on loan payment.
    '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='financial.txt.')
    args = parser.parse_args()
    return args.filename


def normalise(maximum, minimum, x):
    return minimum + x / (maximum - minimum)


def read_file(filename):
    """
    Read in the data set.
    :param filename:
    :return:
    """
    res = dict()

    with open(filename) as ifn:
        k = ''
        v = list()
        for line in ifn:
            cl = ' '.join(line.split()).split()  # Clean the line.
            if cl:
                if len(cl) == 2 and cl[0] == 'NUMBER_POINTS':
                    k = cl[0]
                    v = [int(cl[1])]
                    has_key = True
                    continue
                if len(cl) == 1 and not has_key:
                    has_key = True
                    k = cl[0]
                    v = list()
                else:
                    v += map(float, cl)
            else:
                if has_key:
                    # Normalise the data.
                    minimum = min(v)
                    maximum = max(v)
                    # Emulate the bug in the C++ code.
                    for i in v:
                        if i > minimum:
                            maximum = i
                    if maximum != minimum:
                        res[k] = list(map(lambda x: minimum + x / (maximum - minimum), v))
                    else:
                        res[k] = v
                    has_key = False
    return res


def make_dataset(filename, keys):
    res = read_file(filename)
    if res:
        newPts = vtk.vtkPoints()
        newScalars = vtk.vtkFloatArray()
        xyz = list(zip(res[keys[1]], res[keys[2]], res[keys[3]]))
        for i in range(0, res[keys[0]][0]):
            # print(xyz[i])
            newPts.InsertPoint(i, xyz[i])
            newScalars.InsertValue(i, res[keys[4]][i])

        dataset = vtk.vtkUnstructuredGrid()
        dataset.SetPoints(newPts)
        dataset.GetPointData().SetScalars(newScalars)
        return dataset


if __name__ == '__main__':
    main()
