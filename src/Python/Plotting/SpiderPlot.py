#!/usr/bin/env python

import vtk
import random

numTuples = 12

bitter = vtk.vtkFloatArray()
bitter.SetNumberOfTuples(numTuples)

crispy = vtk.vtkFloatArray()
crispy.SetNumberOfTuples(numTuples)

crunchy = vtk.vtkFloatArray()
crunchy.SetNumberOfTuples(numTuples)

salty = vtk.vtkFloatArray()
salty.SetNumberOfTuples(numTuples)

oily = vtk.vtkFloatArray()
oily.SetNumberOfTuples(numTuples)

for i in range(numTuples):
    bitter.SetTuple1(i, random.randint(1, 10))
    crispy.SetTuple1(i, random.randint(-1, 1))
    crunchy.SetTuple1(i, random.randint(1, 100))
    salty.SetTuple1(i, random.randint(0, 10))
    oily.SetTuple1(i, random.randint(5, 25))

dobj = vtk.vtkDataObject()
dobj.GetFieldData().AddArray(bitter)
dobj.GetFieldData().AddArray(crispy)
dobj.GetFieldData().AddArray(crunchy)
dobj.GetFieldData().AddArray(salty)
dobj.GetFieldData().AddArray(oily)

actor = vtk.vtkSpiderPlotActor()
actor.SetInputData(dobj)
actor.SetTitle("spider plot")
actor.SetIndependentVariablesToColumns()
actor.GetPositionCoordinate().SetValue(0.05, 0.1, 0.0)
actor.GetPosition2Coordinate().SetValue(0.95, 0.85, 0.0)
actor.GetProperty().SetColor(1, 0, 0)

actor.SetAxisLabel(0, "Bitter")
actor.SetAxisRange(0, 1, 10)

actor.SetAxisLabel(1, "Crispy")
actor.SetAxisRange(1, -1, 1)

actor.SetAxisLabel(2, "Crunchy")
actor.SetAxisRange(2, 1, 100)

actor.SetAxisLabel(3, "Salty")
actor.SetAxisRange(3, 0, 10)

actor.SetAxisLabel(4, "Oily")
actor.SetAxisRange(4, 5, 25)
actor.GetLegendActor().SetNumberOfEntries(numTuples)

for i in range(numTuples):
    actor.SetPlotColor(i, random.random(), random.random(), random.random())

actor.LegendVisibilityOn()

#  // Set text colors (same as actor for backward compat with test)
#  actor.GetTitleTextProperty().SetColor(1, 1, 0)
#  actor.GetLabelTextProperty().SetColor(1, 0, 0)

ren1 = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren1)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren1.AddActor(actor)
ren1.SetBackground(0, 0, 0)
renWin.SetSize(500, 500)

iren.Initialize()
renWin.Render()
iren.Start()
