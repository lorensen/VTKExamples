import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkSphereSource;

public class NoShading
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
  
    vtkNamedColors Color = new vtkNamedColors(); 

    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
       
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Red",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("White",BgColor);
    
    vtkSphereSource sphereSource = new vtkSphereSource();  
   
    // Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(sphereSource.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    actor.SetMapper(mapper);
    actor.GetProperty().SetColor(ActorColor); //red
    actor.GetProperty().SetAmbient(1);
    actor.GetProperty().SetDiffuse(0);
    actor.GetProperty().SetSpecular(0);
           
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(actor);
    ren.SetBackground(1,1,1); // Background color white
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
