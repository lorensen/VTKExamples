import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderer;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkXMLPolyDataReader;

public class ReadVTP {

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

  public static void main(String[] args) {
    //parse command line arguments
    if (args.length != 1) {
      System.err.println("Usage: java -classpath ... ReadPolyData Filename(.vtp) e.g horse.vtp");
      return;
    }

    vtkNamedColors colors = new vtkNamedColors();

    double bkg[] = new double[4];
    double actorColor[] = new double[4];
    colors.GetColor("AliceBlue", bkg);
    colors.GetColor("Tan", actorColor);

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
    actor.GetProperty().SetColor(actorColor);

    //Create a renderer, render window, and interactor
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    //Add the actor to the scene
    ren.AddActor(actor);
    ren.SetBackground(bkg);

    //Render and interact

    iren.Initialize();
    renWin.Render();
    ren.GetActiveCamera().SetPosition(-0.5, 0.1, 0.0);
    ren.GetActiveCamera().SetViewUp(0.1, 0.0, 1.0);
    renWin.Render();
    iren.Start();
  }
}
