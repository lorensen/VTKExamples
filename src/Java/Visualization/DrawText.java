import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkTextActor;

public class DrawText 
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
    vtkNamedColors colors = new vtkNamedColors();

    //For textActor Color
    double textactorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Tomato", textactorColor);
    colors.GetColor("White", Bgcolor);
    
    // Create a sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0 );
    sphereSource.SetRadius(5.0 );
    sphereSource.Update();
    
    // Create a mapper
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputData (sphereSource.GetOutput());
    
    vtkActor actor = new vtkActor();
    actor.SetMapper ( mapper );
	    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Setup the text and add it to the renderer
    vtkTextActor textActor = new vtkTextActor();
    textActor.SetInput("Hello world");
    textActor.SetPosition2(10, 40);
    textActor.GetTextProperty().SetFontSize (24);
    textActor.GetTextProperty().SetColor (textactorColor);
    ren.AddActor2D(textActor);
    
    // Visualise
    ren.AddActor(actor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
