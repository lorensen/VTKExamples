import java.awt.Cursor;
import vtk.vtkActor;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;


public class CursorShape
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
    
    //For Cursor Actor Color
    double CursorActorColor[] = new double[4];
   
   //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("LightPink", actorColor);
    colors.GetColor("Brown", CursorActorColor);
    colors.GetColor("MediumSpringGreen", Bgcolor);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualize the actor
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.Render();
    //This must occur after the above Render() call or it does not work 
    renWin.SetCurrentCursor(Cursor.HAND_CURSOR);

    ren.ResetCamera();
    iren.Start();	
  }		  
}
