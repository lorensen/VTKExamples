import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkInteractorStyleSwitch;

public class StyleSwitch 
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

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("White", Bgcolor);
	
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.Update();
    
    // Create a mapper
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());
    
    // Create an actor
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Add the actors to the scene
	ren.AddActor(Actor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();
    
    vtkInteractorStyleSwitch style = new vtkInteractorStyleSwitch();
    iren.SetInteractorStyle(style);

    iren.Initialize();
    iren.Start();
  }
}
