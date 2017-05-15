import vtk

P0 = [0.0, 0.0, 0.0] 
P1 = [1.0, 0.0, 0.0]
P2 = [1.0, 1.0, 0.0]
P3 = [0.0, 1.0, 0.0]
P4 = [0.0, 0.0, 1.0]
P5 = [1.0, 0.0, 1.0]
P6 = [1.0, 1.0, 1.0]
P7 = [0.0, 1.0, 1.0]
 
 
# Create the points
points = vtk.vtkPoints()
points.InsertNextPoint(P0)
points.InsertNextPoint(P1)
points.InsertNextPoint(P2)
points.InsertNextPoint(P3)
points.InsertNextPoint(P4)
points.InsertNextPoint(P5)
points.InsertNextPoint(P6)
points.InsertNextPoint(P7)
 
# Create a hexahedron from the points
hex = vtk.vtkHexahedron() 
hex.GetPointIds().SetId(0,0)
hex.GetPointIds().SetId(1,1)
hex.GetPointIds().SetId(2,2)
hex.GetPointIds().SetId(3,3)
hex.GetPointIds().SetId(4,4)
hex.GetPointIds().SetId(5,5)
hex.GetPointIds().SetId(6,6)
hex.GetPointIds().SetId(7,7)
 
# Add the hexahedron to a cell array
hexs = vtk.vtkCellArray()
hexs.InsertNextCell(hex)
 
# Add the points and hexahedron to an unstructured grid
uGrid = vtk.vtkUnstructuredGrid()
uGrid.SetPoints(points)
uGrid.InsertNextCell(hex.GetCellType(), hex.GetPointIds())
 
# Visualize
mapper = vtk.vtkDataSetMapper()
mapper.SetInput(uGrid)
 
actor = vtk.vtkActor()
actor.SetMapper(mapper)
 
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)
 
renderer.AddActor(actor)
renderer.SetBackground(.2, .3, .4)
 
renderWindow.Render()
renderWindowInteractor.Start()
