import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkXMLPolyDataReader;
import vtk.vtkDataSetMapper;

public class ReadPolyData {
  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
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
  // -----------------------------------------------------------------

  public static void main(String args[]) {

    //parse command line arguments
    if (args.length != 1) {
      System.err.println("Usage: java -classpath ... Filename(.vtp) e.g Torso.vtp");
      return;
    }
    String inputFilename = args[0];

    vtkNamedColors Color = new vtkNamedColors();

    //Renderer Background Color
    double Bkg[] = new double[4];
    double ActorColor[] = new double[4];

    Color.GetColor("Teal", Bkg);
    Color.GetColor("BurlyWood", ActorColor);

    vtkXMLPolyDataReader reader = new vtkXMLPolyDataReader();
    reader.SetFileName(inputFilename);
    reader.Update();

    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputConnection(reader.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetColor(ActorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    ren.AddActor(actor);
    ren.SetBackground(Bkg);
    ren.GetActiveCamera().Pitch(90);
    ren.GetActiveCamera().SetViewUp(0, 0, 1);
    ren.ResetCamera();

    renWin.SetSize(600, 600);
    renWin.Render();
    renWin.SetWindowName("ReadPolyData");

    iren.Initialize();
    iren.Start();

  }
}
