import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkTextActor;
import vtk.vtkNamedColors;

public class TextActor  
{
  //-----------------------------------------------------------------
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
  //-----------------------------------------------------------------
	  

  public static void main(String s[]) 
  {
    vtkNamedColors Color = new vtkNamedColors(); 
    //For Actor Color
    double ActorColor[] = new double[4];
    //For Renderer Background Color
    double Bgcolor[] = new double[4];


    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Red",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Black",Bgcolor);

    vtkTextActor Text = new vtkTextActor();
    Text.SetInput("Hello World");
    Text.SetDisplayPosition(20, 30);
    Text.GetTextProperty().SetFontSize(40);
    Text.GetTextProperty().SetFontFamilyToArial();
    Text.GetTextProperty().BoldOn();
    Text.GetTextProperty().ShadowOn();
    Text.GetTextProperty().GetShadowOffset();
    Text.GetTextProperty().SetColor(ActorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualize the Actor
    ren.AddActor(Text);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
} 
