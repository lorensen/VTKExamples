#!/usr/bin/env python
from __future__ import print_function
import vtk

tse = vtk.vtkTimeSourceExample()
ex = tse.GetExecutive()
tse.UpdateInformation()

# inspect available time range and time steps
print(ex.GetOutputInformation())

# make it grow because bounds are easy to inspect
# tse.SetGrowing(1)

ex.SetUpdateTimeStep(0, 0.0)
tse.Update()
print(tse.GetOutput().GetBounds())

# pick some other time inside the time range
ex.SetUpdateTimeStep(0, 0.5)
tse.Update()
print(tse.GetOutput().GetBounds())

grid = tse.GetOutput()
print(grid)

tri = vtk.vtkDataSetTriangleFilter()
tri.SetInputData(grid)
tri.SetTetrahedraOnly(1)
tri.Update()
output = tri.GetOutput()

iss = output.GetPointData().SetActiveScalars("Point Label")
# iss = gridMapper.GetInput().GetCellData().SetActiveScalars(options.scalarName)
assert(iss > -1)

drange = [0, 1]

# Create transfer mapping scalar value to opacity.
opacityFunction = vtk.vtkPiecewiseFunction()
opacityFunction.AddPoint(drange[0], 0.0)
opacityFunction.AddPoint(drange[1], 1.0)

# Create transfer mapping scalar value to color.
colorFunction = vtk.vtkColorTransferFunction()
colorFunction.SetColorSpaceToHSV()
colorFunction.HSVWrapOff()
colorFunction.AddRGBPoint(drange[0], 0.0, 0.0, 1.0)
colorFunction.AddRGBPoint(drange[1], 1.0, 0.0, 0.0)

volumeProperty = vtk.vtkVolumeProperty()
volumeProperty.SetScalarOpacity(opacityFunction)
volumeProperty.SetColor(colorFunction)
volumeProperty.ShadeOff()
volumeProperty.SetInterpolationTypeToLinear()
# volumeProperty.SetScalarOpacityUnitDistance(options.unit)

volumeMapper = vtk.vtkUnstructuredGridVolumeRayCastMapper()
# volumeMapper = vtk.vtkUnstructuredGridVolumeZSweepMapper()
# volumeMapper = vtk.vtkProjectedTetrahedraMapper()
# volumeMapper.SetBlendModeToMaximumIntensity()
volumeMapper.SetInputData(output)

volume = vtk.vtkVolume()
volume.SetMapper(volumeMapper)
volume.SetProperty(volumeProperty)

# create a rendering window and renderer
renderer = vtk.vtkRenderer()
renderer.SetBackground(0, 0, 0)

window = vtk.vtkRenderWindow()
window.SetSize(512, 512)
window.AddRenderer(renderer)

interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(window)

style = vtk.vtkInteractorStyleTrackballCamera()
interactor.SetInteractorStyle(style)

renderer.AddVolume(volume)

scalarBar = vtk.vtkScalarBarActor()
scalarBar.SetLookupTable(colorFunction)
scalarBar.SetOrientationToVertical()
scalarBar.SetPosition(0.85, 0.7)
scalarBar.SetPosition2(0.1, 0.3)
propT = vtk.vtkTextProperty()
propL = vtk.vtkTextProperty()
propT.SetFontFamilyToArial()
propT.ItalicOff()
propT.BoldOn()
propL.BoldOff()
scalarBar.SetTitleTextProperty(propT)
scalarBar.SetLabelTextProperty(propL)
scalarBar.SetLabelFormat("%5.2f")
renderer.AddActor(scalarBar)

# setup the text and add it to the window
textActor = vtk.vtkTextActor()
textActor.GetTextProperty().SetFontSize(12)
textActor.SetPosition2(10, 40)
renderer.AddActor2D(textActor)
textActor.SetInput("time = ")
textActor.GetTextProperty().SetColor(1.0, 1.0, 1.0)

renderer.ResetCameraClippingRange()
renderer.ResetCamera()

counter = 1
time = 0
while time <= 1:
    print("time = ", time)
    textActor.SetInput("time = %g" % time)

    window.Render()

    # TODO FIXME if this block is not here than the volume renders wrongly
    # renderer.RemoveVolume(volume)
    # del volume
    volume = vtk.vtkVolume()
    volume.SetMapper(volumeMapper)
    volume.SetProperty(volumeProperty)
    renderer.AddVolume(volume)

    counter = counter + 1
    time = time + 1. / 10
    ex.SetUpdateTimeStep(0, time)
    tse.Modified()
    if output.GetPointData().GetScalars():
        print(output.GetPointData().GetScalars().GetRange())
    # if grid.GetPointData().GetScalars():
    # 	print(grid.GetPointData().GetScalars().GetRange())
    # print(grid.GetPointData().GetScalars())

# while True:
    # window.Render()
