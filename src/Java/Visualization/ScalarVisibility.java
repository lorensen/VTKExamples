import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPointSource;


public class ScalarVisibility 
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
  
  public static void main(String s[]) 
  {
    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    colors.GetColor("Red", actorColor);
    
    vtkPointSource pointSource = new vtkPointSource();
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(pointSource.GetOutputPort());
    mapper.ScalarVisibilityOff();
    
    vtkActor actor = new vtkActor();
    actor.SetMapper( mapper );
    actor.GetProperty().SetColor(actorColor);
	    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(actor);
	   
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
