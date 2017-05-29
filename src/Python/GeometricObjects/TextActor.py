import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

# create a text actor
txt = vtk.vtkTextActor()
txt.SetInput("Hello World!")
txtprop=txt.GetTextProperty()
txtprop.SetFontFamilyToArial()
txtprop.SetFontSize(18)
txtprop.SetColor(1,1,1)
txt.SetDisplayPosition(20,30)

# assign actor to the renderer
ren.AddActor(txt)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
