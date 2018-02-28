#!/usr/bin/env python

import vtk


def main():
    def NumberOfTriangles(pd):
        """
        Count the number of triangles.
        :param pd: vtkPolyData.
        :return: The number of triangles.
        """
        cells = pd.GetPolys()
        numOfTriangles = 0
        idList = vtk.vtkIdList()
        for i in range(0, cells.GetNumberOfCells()):
            cells.GetNextCell(idList)
            # If a cell has three points it is a triangle.
            if idList.GetNumberOfIds() == 3:
                numOfTriangles += 1
        return numOfTriangles

    colors = vtk.vtkNamedColors()

    fileName = get_program_parameters()

    # Create the pipeline.
    reader = vtk.vtkMCubesReader()
    reader.SetFileName(fileName)
    reader.FlipNormalsOff()
    reader.Update()
    print("Before Decimation.")
    print("There are: ", NumberOfTriangles(reader.GetOutput()), "triangles")

    deci = vtk.vtkDecimatePro()
    deci.SetInputConnection(reader.GetOutputPort())
    deci.SetTargetReduction(0.9)
    deci.SetAbsoluteError(0.0005)
    deci.MaximumIterations = 6
    deci.SetFeatureAngle(30)
    deci.SetErrorIsAbsolute(1)
    deci.AccumulateErrorOn()
    # deci.SplittingOff()
    deci.Update()
    print("After Decimation.")
    print("There are: ", NumberOfTriangles(deci.GetOutput()), "triangles")

    connect = vtk.vtkConnectivityFilter()
    connect.SetInputConnection(deci.GetOutputPort())
    connect.SetExtractionModeToLargestRegion()
    connect.Update()
    print("After Connectivity.")
    print("There are: ", NumberOfTriangles(connect.GetOutput()), "triangles")

    isoMapper = vtk.vtkDataSetMapper()
    isoMapper.SetInputConnection(connect.GetOutputPort())
    isoMapper.ScalarVisibilityOff()
    isoActor = vtk.vtkActor()
    isoActor.SetMapper(isoMapper)
    isoActor.GetProperty().SetColor(colors.GetColor3d("raw_sienna"))

    #  Get an outline of the data set for context.
    outline = vtk.vtkOutlineFilter()
    outline.SetInputConnection(reader.GetOutputPort())
    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())
    outlineActor = vtk.vtkActor()
    outlineActor.SetMapper(outlineMapper)
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))

    #  Create the Renderer, RenderWindow and RenderWindowInteractor.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Add the actors to the renderer, set the background and size.
    ren.AddActor(outlineActor)
    ren.AddActor(isoActor)
    ren.SetBackground(1, 1, 1)
    # renWin.SetSize(750, 750)
    renWin.SetSize(512, 512)
    ren.SetBackground(colors.GetColor3d("SlateGray"))

    # render the image

    cam = ren.GetActiveCamera()
    cam.SetFocalPoint(40.6018, 37.2813, 50.1953)
    cam.SetPosition(40.6018, -280.533, 47.0172)
    cam.ComputeViewPlaneNormal()
    cam.SetClippingRange(26.1073, 1305.36)
    cam.SetViewAngle(20.9219)
    cam.SetViewUp(0.0, 0.0, 1.0)

    iren.Initialize()
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Applying connectivity and decimation filters to remove noisy isosurfaces and reduce data size.'
    epilogue = '''
        Applying connectivity and decimation filters to remove noisy isosurfaces and reduce data size..

This example demonstrates how to use the vtkConnectivityFilter and vtkDecimate.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename', help='pine_root.tri.')
    args = parser.parse_args()
    return args.filename


if __name__ == '__main__':
    main()
