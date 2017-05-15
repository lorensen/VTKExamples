from vtk import*


#Create a sphere
textSource = vtkVectorText();
textSource.SetText("Hello");
textSource.Update();

#Create a mapper and actor
mapper = vtkPolyDataMapper();
mapper.SetInputConnection(textSource.GetOutputPort());

actor =vtkActor();
actor.SetMapper(mapper);
actor.GetProperty().SetColor(1.0, 0.0, 0.0);

#Create a renderer, render window, and interactor
renderer = vtkRenderer();
renderWindow = vtkRenderWindow();
renderWindow.AddRenderer(renderer);
renderWindowInteractor = vtkRenderWindowInteractor();
renderWindowInteractor.SetRenderWindow(renderWindow);

#Add the actor to the scene
renderer.AddActor(actor);
renderer.SetBackground(1,1,1); # Background color white

#Render and interact
renderWindow.Render();
renderWindowInteractor.Start();
