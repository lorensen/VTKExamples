#!/usr/bin/env python

"""
Modified from VTK/Examples/GUI/Python/StreamlinesWithLineWidget.py.
This program encompasses the functionality of
  StreamlinesWithLineWidget.tcl and LineWidget.tcl.
"""

import vtk


def main():
    colors = vtk.vtkNamedColors()

    fileName1, fileName2, numOfStreamLines, illustration = get_program_parameters()
    if illustration:
        numOfStreamLines = 25

    # Start by loading some data.
    pl3d = vtk.vtkMultiBlockPLOT3DReader()
    pl3d.SetXYZFileName(fileName1)
    pl3d.SetQFileName(fileName2)
    pl3d.SetScalarFunctionNumber(100)  # Density
    pl3d.SetVectorFunctionNumber(202)  # Momentum
    pl3d.Update()

    pl3d_output = pl3d.GetOutput().GetBlock(0)

    # Create the Renderer, RenderWindow and RenderWindowInteractor.
    ren = vtk.vtkRenderer()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # Needed by: vtkStreamTracer and vtkLineWidget.
    seeds = vtk.vtkPolyData()
    streamline = vtk.vtkActor()
    seeds2 = vtk.vtkPolyData()
    streamline2 = vtk.vtkActor()

    # The line widget is used seed the streamlines.
    lineWidget = vtk.vtkLineWidget()
    lineWidget.SetResolution(numOfStreamLines)
    lineWidget.SetInputData(pl3d_output)
    lineWidget.GetPolyData(seeds)
    if illustration:
        lineWidget.SetAlignToNone()
        lineWidget.SetPoint1(0.974678, 5.073630, 31.217961)
        lineWidget.SetPoint2(0.457544, -4.995921, 31.080175)
    else:
        lineWidget.SetAlignToYAxis()
    lineWidget.ClampToBoundsOn()
    lineWidget.PlaceWidget()
    # Associate the line widget with the interactor and setup callbacks.
    lineWidget.SetInteractor(iren)
    lineWidget.AddObserver("StartInteractionEvent", EnableActorCallback(streamline))
    lineWidget.AddObserver("InteractionEvent", GenerateStreamlinesCallback(seeds, renWin))

    # The second line widget is used seed more streamlines.
    lineWidget2 = vtk.vtkLineWidget()
    lineWidget2.SetResolution(numOfStreamLines)
    lineWidget2.SetInputData(pl3d_output)
    lineWidget2.GetPolyData(seeds2)
    lineWidget2.SetKeyPressActivationValue('L')
    lineWidget2.SetAlignToZAxis()
    lineWidget.ClampToBoundsOn()
    lineWidget2.PlaceWidget()
    # Associate the line widget with the interactor and setup callbacks.
    lineWidget2.SetInteractor(iren)
    lineWidget2.AddObserver("StartInteractionEvent", EnableActorCallback(streamline2))
    lineWidget2.AddObserver("InteractionEvent", GenerateStreamlinesCallback(seeds2, renWin))

    # Here we set up two streamlines.
    rk4 = vtk.vtkRungeKutta4()
    streamer = vtk.vtkStreamTracer()
    streamer.SetInputData(pl3d_output)
    streamer.SetSourceData(seeds)
    streamer.SetMaximumPropagation(100)
    streamer.SetInitialIntegrationStep(0.2)
    streamer.SetIntegrationDirectionToForward()
    streamer.SetComputeVorticity(1)
    streamer.SetIntegrator(rk4)
    rf = vtk.vtkRibbonFilter()
    rf.SetInputConnection(streamer.GetOutputPort())
    rf.SetWidth(0.1)
    rf.SetWidthFactor(5)
    streamMapper = vtk.vtkPolyDataMapper()
    streamMapper.SetInputConnection(rf.GetOutputPort())
    streamMapper.SetScalarRange(pl3d_output.GetScalarRange())
    streamline.SetMapper(streamMapper)
    streamline.VisibilityOff()

    streamer2 = vtk.vtkStreamTracer()
    streamer2.SetInputData(pl3d_output)
    streamer2.SetSourceData(seeds2)
    streamer2.SetMaximumPropagation(100)
    streamer2.SetInitialIntegrationStep(0.2)
    streamer2.SetIntegrationDirectionToForward()
    streamer2.SetComputeVorticity(1)
    streamer2.SetIntegrator(rk4)
    rf2 = vtk.vtkRibbonFilter()
    rf2.SetInputConnection(streamer2.GetOutputPort())
    rf2.SetWidth(0.1)
    rf2.SetWidthFactor(5)
    streamMapper2 = vtk.vtkPolyDataMapper()
    streamMapper2.SetInputConnection(rf2.GetOutputPort())
    streamMapper2.SetScalarRange(pl3d_output.GetScalarRange())
    streamline2.SetMapper(streamMapper2)
    streamline2.VisibilityOff()

    # Get an outline of the data set for context.
    outline = vtk.vtkStructuredGridOutlineFilter()
    outline.SetInputData(pl3d_output)
    outlineMapper = vtk.vtkPolyDataMapper()
    outlineMapper.SetInputConnection(outline.GetOutputPort())
    outlineActor = vtk.vtkActor()
    outlineActor.GetProperty().SetColor(colors.GetColor3d("Black"))
    outlineActor.SetMapper(outlineMapper)

    # Add the actors to the renderer, set the background and size.
    ren.AddActor(outlineActor)
    ren.AddActor(streamline)
    ren.AddActor(streamline2)
    renWin.SetSize(512, 512)
    cam = ren.GetActiveCamera()
    if illustration:
        # We need to directly display the streamlines in this case.
        lineWidget.EnabledOn()
        streamline.VisibilityOn()
        lineWidget.GetPolyData(seeds)
        renWin.Render()

        cam.SetClippingRange(14.216207, 68.382915)
        cam.SetFocalPoint(9.718210, 0.458166, 29.399900)
        cam.SetPosition(-15.827551, -16.997463, 54.003120)
        cam.SetViewUp(0.616076, 0.179428, 0.766979)
        ren.SetBackground(colors.GetColor3d("Silver"))
    else:
        cam.SetClippingRange(3.95297, 50)
        cam.SetFocalPoint(9.71821, 0.458166, 29.3999)
        cam.SetPosition(2.7439, -37.3196, 38.7167)
        cam.SetViewUp(-0.16123, 0.264271, 0.950876)
        ren.SetBackground(colors.GetColor3d("Silver"))

    iren.Initialize()
    renWin.Render()
    iren.Start()


def get_program_parameters():
    import argparse
    description = 'Produce streamlines in the combustor dataset.'
    epilogue = '''
        Produce streamlines in the combustor dataset.

This example demonstrates how to use the vtkLineWidget to seed and
manipulate streamlines. Two line widgets are created. The first is invoked
by pressing 'i', the second by pressing 'L' (capital). Both can exist
together.

If the fourth parameter is non-zero, it is used to generate
 an image with streamlines:
 1) The third parameter value is changed to 25.
 2) The camera position and first line widget are positioned differently.
 3) The streamlines are displayed running from the first line widget.
 4) The second line widget is still available.

   '''
    parser = argparse.ArgumentParser(description=description, epilog=epilogue,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('filename1', help='combxyz.bin.')
    parser.add_argument('filename2', help='combq.bin.')
    parser.add_argument('numOfStreamLines', default=25, type=int, nargs='?', help='The number of stream lines.')
    parser.add_argument('illustration', default=0, type=int, nargs='?',
                        help='If non-zero, reproduce Fig 7-39 of the VTK Textbook.')
    args = parser.parse_args()
    return args.filename1, args.filename2, args.numOfStreamLines, args.illustration

class EnableActorCallback(object):
    def __init__(self, actor):
        self.actor = actor
    def __call__(self, caller, ev):
        self.actor.VisibilityOn()

class GenerateStreamlinesCallback(object):
    def __init__(self, polyData, renWin):
        self.polyData = polyData
        self.renWin = renWin
    def __call__(self, caller, ev):
        caller.GetPolyData(self.polyData)
        self.renWin.Render()


if __name__ == '__main__':
    main()
