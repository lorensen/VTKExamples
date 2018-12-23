import vtk.*;

public class ReadPolyData
{

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
    //parse command line arguments
    if(args.length != 1)
    {
      System.err.println("Usage: java -classpath ... ReadPolyData Filename(.vtp)");
      return;
    }

    String filename = args[0];

    //read all the data from the file
    vtkXMLPolyDataReader reader = new vtkXMLPolyDataReader();
    reader.SetFileName(filename);
    reader.Update();

    //Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(reader.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    //Create a renderer, render window, and interactor
    vtkRenderer renderer = new vtkRenderer();
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);
    vtkRenderWindowInteractor renderWindowInteractor = 
      new vtkRenderWindowInteractor();
    renderWindowInteractor.SetRenderWindow(renderWindow);

    //Add the actor to the scene
    renderer.AddActor(actor);
    renderer.SetBackground(.3, .6, .3); // Background color green

    //Render and interact
    renderWindow.Render();
    renderWindowInteractor.Start();
  }
}
