import vtk.*;

public class ColorAnActor {

  // Loading Native Libraries.
  // Now it works in eclipse without any issues.
  static {
	    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
	      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
	        if (!lib.IsLoaded()) {
	          System.out.println(lib.GetLibraryName() + " not loaded");
	        }
	      }
	    }
	    vtkNativeLibrary.DisableOutputWindow(null);
	  }

  public static void main(String[] args)
  {
    //Create a sphere
    vtkSphereSource sphereSource = 
      new vtkSphereSource();
    sphereSource.Update();

    //Create a mapper and actor
    vtkPolyDataMapper mapper = 
      new vtkPolyDataMapper();
    mapper.SetInputConnection(sphereSource.GetOutputPort());
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    //Set the color of the sphere
    actor.GetProperty().SetColor(1.0, 0.0, 0.0); //(R,G,B)
    
    //Create a renderer, render window, and interactor
    vtkRenderer renderer = 
      new vtkRenderer();
    vtkRenderWindow renderWindow = 
      new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);
    vtkRenderWindowInteractor renderWindowInteractor = 
      new vtkRenderWindowInteractor();
    renderWindowInteractor.SetRenderWindow(renderWindow);

    //Add the actor to the scene
    renderer.AddActor(actor);
    renderer.SetBackground(1,1,1); // Background color white

    //Render and interact
    renderWindow.Render();
    renderWindowInteractor.Start();
  }
}
