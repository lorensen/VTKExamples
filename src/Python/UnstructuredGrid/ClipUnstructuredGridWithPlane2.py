#!/usr/bin/env python

import collections

import vtk


def get_program_parameters():
    import argparse
    description = 'Use a vtkClipDataSet to clip a vtkUnstructuredGrid..'
    epilogue = '''
 Use a vtkClipDataSet to clip a vtkUnstructuredGrid..
 The resulting output and clipped output are presented in yellow and red respectively.
 To illustrate the clipped interfaces, the example uses a vtkTransform to rotate each
    output about their centers.
 Note: This clipping filter does not retain the original cells if they are not clipped.
   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='treemesh.vtk.')
    args = parser.parse_args()
    return args.filename


def main():
    filename = get_program_parameters()

    # Create the reader for the data.
    reader = vtk.vtkUnstructuredGridReader()
    reader.SetFileName(filename)
    reader.Update()

    bounds = reader.GetOutput().GetBounds()
    center = reader.GetOutput().GetCenter()

    colors = vtk.vtkNamedColors()
    renderer = vtk.vtkRenderer()
    renderer.SetBackground(colors.GetColor3d("Wheat"))
    renderer.UseHiddenLineRemovalOn()

    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetSize(640, 480)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(renderWindow)

    xnorm = [-1.0, -1.0, 1.0]

    clipPlane = vtk.vtkPlane()
    clipPlane.SetOrigin(reader.GetOutput().GetCenter())
    clipPlane.SetNormal(xnorm)

    clipper = vtk.vtkClipDataSet()
    clipper.SetClipFunction(clipPlane)
    clipper.SetInputData(reader.GetOutput())
    clipper.SetValue(0.0)
    clipper.GenerateClippedOutputOn()
    clipper.Update()

    insideMapper = vtk.vtkDataSetMapper()
    insideMapper.SetInputData(clipper.GetOutput())
    insideMapper.ScalarVisibilityOff()

    insideActor = vtk.vtkActor()
    insideActor.SetMapper(insideMapper)
    insideActor.GetProperty().SetDiffuseColor(colors.GetColor3d("banana"))
    insideActor.GetProperty().SetAmbient(.3)
    insideActor.GetProperty().EdgeVisibilityOn()

    clippedMapper = vtk.vtkDataSetMapper()
    clippedMapper.SetInputData(clipper.GetClippedOutput())
    clippedMapper.ScalarVisibilityOff()

    clippedActor = vtk.vtkActor()
    clippedActor.SetMapper(clippedMapper)
    clippedActor.GetProperty().SetDiffuseColor(colors.GetColor3d("tomato"))
    insideActor.GetProperty().SetAmbient(.3)
    clippedActor.GetProperty().EdgeVisibilityOn()

    # Create transforms to make a better visualization
    insideTransform = vtk.vtkTransform()
    insideTransform.Translate(-(bounds[1] - bounds[0]) * 0.75, 0, 0)
    insideTransform.Translate(center[0], center[1], center[2])
    insideTransform.RotateY(-120.0)
    insideTransform.Translate(-center[0], -center[1], -center[2])
    insideActor.SetUserTransform(insideTransform)

    clippedTransform = vtk.vtkTransform()
    clippedTransform.Translate((bounds[1] - bounds[0]) * 0.75, 0, 0)
    clippedTransform.Translate(center[0], center[1], center[2])
    clippedTransform.RotateY(60.0)
    clippedTransform.Translate(-center[0], -center[1], -center[2])
    clippedActor.SetUserTransform(clippedTransform)

    renderer.AddViewProp(clippedActor)
    renderer.AddViewProp(insideActor)

    renderer.ResetCamera()
    renderer.GetActiveCamera().Dolly(1.4)
    renderer.ResetCameraClippingRange()
    renderWindow.Render()
    renderWindow.SetWindowName('ClipUnstructuredGridWithPlane2')
    renderWindow.Render()

    interactor.Start()

    # Generate a report
    numberOfCells = clipper.GetOutput().GetNumberOfCells()
    print("------------------------")
    print("The inside dataset contains a \n", clipper.GetOutput().GetClassName(), " that has ", numberOfCells, " cells")
    cellMap = dict()
    for i in range(0, numberOfCells):
        cellMap.setdefault(clipper.GetOutput().GetCellType(i), 0)
        cellMap[clipper.GetOutput().GetCellType(i)] += 1
    # Sort by key and put into an OrderedDict.
    # An OrderedDict remembers the order in which the keys have been inserted.
    for k, v in collections.OrderedDict(sorted(cellMap.items())).items():
        print("\tCell type ", vtk.vtkCellTypes.GetClassNameFromTypeId(k), " occurs ", v, " times.")

    numberOfCells = clipper.GetClippedOutput().GetNumberOfCells()
    print("------------------------")
    print("The clipped dataset contains a \n", clipper.GetClippedOutput().GetClassName(), " that has ", numberOfCells,
          " cells")
    outsideCellMap = dict()
    for i in range(0, numberOfCells):
        outsideCellMap.setdefault(clipper.GetClippedOutput().GetCellType(i), 0)
        outsideCellMap[clipper.GetClippedOutput().GetCellType(i)] += 1
    for k, v in collections.OrderedDict(sorted(outsideCellMap.items())).items():
        print("\tCell type ", vtk.vtkCellTypes.GetClassNameFromTypeId(k), " occurs ", v, " times.")


if __name__ == "__main__":
    main()
