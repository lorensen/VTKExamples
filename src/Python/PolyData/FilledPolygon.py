import vtk

# Create a cube
cube = vtk.vtkSphereSource()
cube.SetRadius(50)
cube.SetThetaResolution(100)
cube.SetPhiResolution(100)

cubeMapper = vtk.vtkPolyDataMapper()
cubeMapper.SetInputConnection(cube.GetOutputPort())

# create a plane to cut,here it cuts in the XZ direction (xz normal=(1,0,0);XY =(0,0,1),YZ =(0,1,0)
plane = vtk.vtkPlane()
plane.SetOrigin(20, 0, 0)
plane.SetNormal(1, 0, 0)

# create cutter
cutter = vtk.vtkCutter()
cutter.SetCutFunction(plane)
cutter.SetInputConnection(cube.GetOutputPort())
cutter.Update()

FeatureEdges = vtk.vtkFeatureEdges()
FeatureEdges.SetInputConnection(cutter.GetOutputPort())
FeatureEdges.BoundaryEdgesOn()
FeatureEdges.FeatureEdgesOff()
FeatureEdges.NonManifoldEdgesOff()
FeatureEdges.ManifoldEdgesOff()
FeatureEdges.Update()

cutStrips = vtk.vtkStripper()  # Forms loops (closed polylines) from cutter
cutStrips.SetInputConnection(cutter.GetOutputPort())
cutStrips.Update()
cutPoly = vtk.vtkPolyData()  # This trick defines polygons as polyline loop
cutPoly.SetPoints((cutStrips.GetOutput()).GetPoints())
cutPoly.SetPolys((cutStrips.GetOutput()).GetLines())

cutMapper = vtk.vtkPolyDataMapper()
# cutMapper.SetInput(FeatureEdges.GetOutput())
if vtk.VTK_MAJOR_VERSION <= 5:
    cutMapper.SetInput(cutPoly)
else:
    cutMapper.SetInputData(cutPoly)

cutActor = vtk.vtkActor()
cutActor.GetProperty().SetColor(1, 1, 0)
cutActor.GetProperty().SetEdgeColor(0, 1, 0)

cutActor.GetProperty().SetLineWidth(2)
cutActor.GetProperty().EdgeVisibilityOn()
# cutActor.GetProperty().SetOpacity(0.7)
cutActor.SetMapper(cutMapper)

# create renderers and add actors of plane and cube
ren = vtk.vtkRenderer()
ren.AddActor(cutActor)

# Add renderer to renderwindow and render
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(600, 600)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren.SetBackground(0, 0, 0)
ren.GetActiveCamera().SetPosition(223, -122, -91)
renWin.Render()
iren.Start()
