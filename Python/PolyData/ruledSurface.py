import vtk
 
# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
 
# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
 
#Create the points fot the lines.
points = vtk.vtkPoints()
points.InsertPoint(0, 0, 0, 1)
points.InsertPoint(1, 1, 0, 0)
points.InsertPoint(2, 0, 1, 0)
points.InsertPoint(3, 1, 1, 1)

#Create line1
line1 = vtk.vtkLine()
line1.GetPointIds().SetId(0,0)
line1.GetPointIds().SetId(1,1)
 
#Create line2
line2 = vtk.vtkLine()
line2.GetPointIds().SetId(0,2)
line2.GetPointIds().SetId(1,3)

#Create a cellArray containing the lines
lines =vtk.vtkCellArray()
lines.InsertNextCell(line1)
lines.InsertNextCell(line2)
 
#Create the vtkPolyData to contain the points and cellArray with the lines
polydata = vtk.vtkPolyData()
polydata.SetPoints(points)
polydata.SetLines(lines)
 
#Create the ruledSurfaceFilter from the polydata containing the lines
ruledSurfaceFilter = vtk.vtkRuledSurfaceFilter()
ruledSurfaceFilter.SetInput(polydata)
ruledSurfaceFilter.SetResolution(21, 21)
ruledSurfaceFilter.SetRuledModeToResample()

#Create the mapper with the ruledSufaceFilter as input
mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(ruledSurfaceFilter.GetOutput())

#create the actor with the mapper
actor = vtk.vtkActor()
actor.SetMapper(mapper)

#add the actor to the display
ren.AddActor(actor)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
