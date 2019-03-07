import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkSimplePointsReader;

public class SimplePointsReader 
{
  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
  static 
  {
    if (!vtkNativeLibrary.LoadAllNativeLibraries()) 
    {
      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) 
      {
        if (!lib.IsLoaded()) 
        {
          System.out.println(lib.GetLibraryName() + " not loaded");
        }
      }
    }
    vtkNativeLibrary.DisableOutputWindow(null);
  }
  // -----------------------------------------------------------------

  public static void main(String args[]) 
  {
    
    //parse command line arguments
    if (args.length != 1) 
    {
      System.err.println("Usage: java -classpath ... Filename(.xyz) e.g simple.xyz");
      return;
    }
    String inputFilename = args[0];
    
    vtkNamedColors Color = new vtkNamedColors(); 

    //Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Seagreen",BgColor);

    vtkSimplePointsReader reader = new vtkSimplePointsReader();
    reader.SetFileName(inputFilename);
    reader.Update();
   	
    // Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(reader.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetPointSize(5);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    ren.AddActor(actor);
    ren.SetBackground(BgColor);

    renWin.SetSize(300,300);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();

  }
}
