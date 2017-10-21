# Contributed by Eric E Monson

import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

cube = vtk.vtkCubeSource()
cube.SetXLength(200)
cube.SetYLength(200)
cube.SetZLength(200)
cube.Update()
cm = vtk.vtkPolyDataMapper()
cm.SetInputConnection(cube.GetOutputPort())
ca = vtk.vtkActor()
ca.SetMapper(cm)

# assign actor to the renderer
ren.AddActor(ca)

axesActor = vtk.vtkAnnotatedCubeActor()
axesActor.SetXPlusFaceText('R')
axesActor.SetXMinusFaceText('L')
axesActor.SetYMinusFaceText('H')
axesActor.SetYPlusFaceText('F')
axesActor.SetZMinusFaceText('P')
axesActor.SetZPlusFaceText('A')
axesActor.GetTextEdgesProperty().SetColor(1, 1, 0)
axesActor.GetTextEdgesProperty().SetLineWidth(2)
axesActor.GetCubeProperty().SetColor(0, 0, 1)
axes = vtk.vtkOrientationMarkerWidget()
axes.SetOrientationMarker(axesActor)
axes.SetInteractor(iren)
axes.EnabledOn()
axes.InteractiveOn()
ren.ResetCamera()

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
