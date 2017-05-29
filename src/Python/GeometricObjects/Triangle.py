import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

# create points
points = vtk.vtkPoints()
points.InsertNextPoint(1.0,0.0,0.0)
points.InsertNextPoint(0.0,0.0,0.0)
points.InsertNextPoint(0.0,1.0,0.0)

triangle = vtk.vtkTriangle()
triangle.GetPointIds().SetId(0,0)
triangle.GetPointIds().SetId(1,1)
triangle.GetPointIds().SetId(2,2)

triangles = vtk.vtkCellArray()
triangles.InsertNextCell(triangle)

# polydata object
trianglePolyData = vtk.vtkPolyData()
trianglePolyData.SetPoints( points )
trianglePolyData.SetPolys( triangles )

# mapper
mapper = vtk.vtkPolyDataMapper()
if vtk.VTK_MAJOR_VERSION <= 5:
    mapper.SetInput(trianglePolyData)
else:
    mapper.SetInputData(trianglePolyData)

# actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# assign actor to the renderer
ren.AddActor(actor)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
