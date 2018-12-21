#!/usr/bin/env python

# Example of how to use Parallel Coordinates View to plot and compare
# data set attributes,  and then to use selections in the parallel coordinates
# view to extract and view data points associated with those selections
# Use the "u" character to toggle between "inspect modes" on the parallel
# coordinates view (i.e. between selecting data and manipulating axes)
# Note that no points will show up inside of the 3d box outline until you
# select some lines/curves in the parallel coordinates view

import vtk

# Generate an image data set with multiple attribute arrays to probe and view
rt = vtk.vtkRTAnalyticSource()
rt.SetWholeExtent(-3, 3, -3, 3, -3, 3)
grad = vtk.vtkImageGradient()
grad.SetDimensionality(3)
grad.SetInputConnection(rt.GetOutputPort())
brown = vtk.vtkBrownianPoints()
brown.SetMinimumSpeed(0.5)
brown.SetMaximumSpeed(1.0)
brown.SetInputConnection(grad.GetOutputPort())
elev = vtk.vtkElevationFilter()
elev.SetLowPoint(-3, -3, -3)
elev.SetHighPoint(3, 3, 3)
elev.SetInputConnection(brown.GetOutputPort())

# Updating here because I will need to probe scalar ranges before
# the render window updates the pipeline
elev.Update()

# Set up parallel coordinates representation to be used in View
rep = vtk.vtkParallelCoordinatesRepresentation()
if vtk.VTK_MAJOR_VERSION <= 5:
    rep.SetInput(elev.GetOutput())
else:
    rep.SetInputConnection(elev.GetOutputPort())
rep.SetInputArrayToProcess(0, 0, 0, 0, 'RTDataGradient')
rep.SetInputArrayToProcess(1, 0, 0, 0, 'RTData')
rep.SetInputArrayToProcess(2, 0, 0, 0, 'Elevation')
rep.SetInputArrayToProcess(3, 0, 0, 0, 'BrownianVectors')
rep.SetUseCurves(0)  # set to 1 to use smooth curves
rep.SetLineOpacity(0.5)

# Set up the Parallel Coordinates View and hook in representation
view = vtk.vtkParallelCoordinatesView()
view.SetRepresentation(rep)
view.SetInspectMode(1)  # VTK_INSPECT_SELECT_DATA = 1
view.SetBrushOperatorToReplace()
view.SetBrushModeToLasso()

# Create a annotation link to access selection in parallel coordinates view
annotationLink = vtk.vtkAnnotationLink()
# If you don't set the FieldType explicitly it ends up as UNKNOWN
# (as of 21 Feb 2010)
# See vtkSelectionNode doc for field and content type enum values
annotationLink.GetCurrentSelection().GetNode(0).SetFieldType(1)  # Point
annotationLink.GetCurrentSelection().GetNode(0).SetContentType(4)  # Indices
# Update before passing annotationLink to vtkExtractSelection
annotationLink.Update()
# Connect the annotation link to the parallel coordinates representation
rep.SetAnnotationLink(annotationLink)

# Extract portion of data corresponding to parallel coordinates selection
extract = vtk.vtkExtractSelection()
if vtk.VTK_MAJOR_VERSION <= 5:
    extract.SetInput(0, elev.GetOutput())
    extract.SetInput(1, annotationLink.GetOutputDataObject(2))
else:
    extract.SetInputConnection(0, elev.GetOutputPort())
    extract.SetInputConnection(1, annotationLink.GetOutputPort(2))


def UpdateRenderWindows(obj, event):

    # Handle updating of RenderWindow since it's not a "View"
    # and so not covered by vtkViewUpdater
    # ren.ResetCamera()
    renWin.Render()


# Set up callback to update 3d render window when selections are changed in
# parallel coordinates view
annotationLink.AddObserver("AnnotationChangedEvent", UpdateRenderWindows)


def ToggleInspectors(obj, event):

    if (view.GetInspectMode() == 0):
        view.SetInspectMode(1)
    else:
        view.SetInspectMode(0)


# Set up callback to toggle between inspect modes (manip axes & select data)
view.GetInteractor().AddObserver("UserEvent", ToggleInspectors)

# 3D outline of image data bounds
outline = vtk.vtkOutlineFilter()
outline.SetInputConnection(elev.GetOutputPort())
outlineMapper = vtk.vtkPolyDataMapper()
outlineMapper.SetInputConnection(outline.GetOutputPort())
outlineActor = vtk.vtkActor()
outlineActor.SetMapper(outlineMapper)

# Build the lookup table for the 3d data scalar colors (brown to white)
lut = vtk.vtkLookupTable()
lut.SetTableRange(0, 256)
lut.SetHueRange(0.1, 0.1)
lut.SetSaturationRange(1.0, 0.1)
lut.SetValueRange(0.4, 1.0)
lut.Build()

# Set up the 3d rendering parameters
# of the image data which is selected in parallel coordinates
coloring_by = 'Elevation'
dataMapper = vtk.vtkDataSetMapper()
dataMapper.SetInputConnection(extract.GetOutputPort())
dataMapper.SetScalarModeToUsePointFieldData()
dataMapper.SetColorModeToMapScalars()
data = elev.GetOutputDataObject(0).GetPointData()
dataMapper.ScalarVisibilityOn()
dataMapper.SetScalarRange(data.GetArray(coloring_by).GetRange())
dataMapper.SetLookupTable(lut)
dataMapper.SelectColorArray(coloring_by)
dataActor = vtk.vtkActor()
dataActor.SetMapper(dataMapper)
dataActor.GetProperty().SetRepresentationToPoints()
dataActor.GetProperty().SetPointSize(10)

# Set up the 3d render window and add both actors
ren = vtk.vtkRenderer()
ren.AddActor(outlineActor)
ren.AddActor(dataActor)
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren.ResetCamera()
renWin.Render()

# Finalize parallel coordinates view and start interaction event loop
view.GetRenderWindow().SetSize(600, 300)
view.ResetCamera()
view.Render()
view.GetInteractor().Start()
