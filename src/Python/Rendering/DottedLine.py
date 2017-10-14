import vtk

Line = vtk.vtkLineSource()
Line.SetPoint1(-50, 0, 0)
Line.SetPoint2(50, 0, 0)
Line.SetResolution(100)

Mapper = vtk.vtkPolyDataMapper()
Mapper.SetInputConnection(Line.GetOutputPort())

Actor = vtk.vtkActor()
Actor.SetMapper(Mapper)

# create renderers and add actors of plane and cube
ren = vtk.vtkRenderer()
ren.AddActor(Actor)
Actor.GetProperty().SetColor(1, 1, 0)
Actor.GetProperty().SetLineStipplePattern(0xf0f0)
Actor.GetProperty().SetLineStippleRepeatFactor(1)
Actor.GetProperty().SetPointSize(1)
Actor.GetProperty().SetLineWidth(1.5)

# Add renderer to renderwindow and render
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(600, 600)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren.SetBackground(0, 0, 0)
renWin.Render()
iren.Start()
