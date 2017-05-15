from vtk import*


#Setup the coordinates of eight points
#(the two faces must be in counter clockwise order as viewd from the outside)
P0 = [0.0, 0.0, 0.0];
P1 = [1.0, 0.0, 0.0];
P2 = [1.0, 1.0, 0.0];
P3 = [0.0, 1.0, 0.0];
P4 = [0.0, 0.0, 1.0];
P5 = [1.0, 0.0, 1.0];
P6 = [1.0, 1.0, 1.0];
P7 = [0.0, 1.0, 1.0];


#Create the points
points = vtkPoints();
points.InsertNextPoint(P0);
points.InsertNextPoint(P1);
points.InsertNextPoint(P2);
points.InsertNextPoint(P3);
points.InsertNextPoint(P4);
points.InsertNextPoint(P5);
points.InsertNextPoint(P6);
points.InsertNextPoint(P7);

#Create a hexahedron from the points
hexa = vtkHexahedron();
hexa.GetPointIds().SetId(0,0);
hexa.GetPointIds().SetId(1,1);
hexa.GetPointIds().SetId(2,2);
hexa.GetPointIds().SetId(3,3);
hexa.GetPointIds().SetId(4,4);
hexa.GetPointIds().SetId(5,5);
hexa.GetPointIds().SetId(6,6);
hexa.GetPointIds().SetId(7,7);

#Add the hexahedron to a cell array
hexs = vtkCellArray();
hexs.InsertNextCell(hexa);

#Add the points and hexahedron to an unstructured grid
uGrid =vtkUnstructuredGrid();
uGrid.SetPoints(points);
uGrid.InsertNextCell(hexa.GetCellType(), hexa.GetPointIds());

surface=vtkDataSetSurfaceFilter()
surface.SetInput(uGrid)
surface.Update()



aBeamMapper = vtkDataSetMapper()
aBeamMapper.SetInput(surface.GetOutput())
aBeamActor = vtkActor()
aBeamActor.SetMapper(aBeamMapper)
aBeamActor.AddPosition(0,0,0)
aBeamActor.GetProperty().SetColor(1,1,0)
aBeamActor.GetProperty().SetOpacity(0.60)
aBeamActor.GetProperty().EdgeVisibilityOn()
aBeamActor.GetProperty().SetEdgeColor(1,1,1)
aBeamActor.GetProperty().SetLineWidth(1.5)

#create a plane to cut,here it cuts in the XZ direction (xz normal=(1,0,0);XY =(0,0,1),YZ =(0,1,0)
plane=vtkPlane()
plane.SetOrigin(0.5,0,0)
plane.SetNormal(1,0,0)

#create cutter
cutter=vtkCutter()
cutter.SetCutFunction(plane)
cutter.SetInput(aBeamActor.GetMapper().GetInput())
cutter.Update()
cutterMapper=vtkDataSetMapper()
cutterMapper.SetInputConnection( cutter.GetOutputPort())

#create plane actor
planeActor=vtkActor()
planeActor.GetProperty().SetColor(1,0.5,0.5)
planeActor.GetProperty().SetLineWidth(2)
planeActor.SetMapper(cutterMapper)




# Setup a renderer, render window, and interactor
renderer = vtkRenderer()
renderWindow = vtkRenderWindow()
#renderWindow.SetWindowName("Test")

renderWindow.AddRenderer(renderer);
renderWindowInteractor = vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

#Add the actor to the scene
renderer.AddActor(aBeamActor)
renderer.AddActor(planeActor)
renderer.SetBackground(0,0,0) # Background color white

#Render and interact
renderWindow.Render()
