import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkPerlinNoise;
import vtk.vtkSampleFunction;
import vtk.vtkContourFilter;

public class PerlinNoise 
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
  // -----------------------------------------------------------------

  public static void main(String args[]) 
  {

    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Chartreuse", actorColor);
    colors.GetColor("DarkSalmon", Bgcolor);

    vtkPerlinNoise perlinNoise = new vtkPerlinNoise();
    perlinNoise.SetFrequency(2, 1.25,1.5);
    perlinNoise.SetPhase(0, 0, 0);

    vtkSampleFunction Sample = new vtkSampleFunction();
    Sample.SetImplicitFunction(perlinNoise);
    Sample.SetSampleDimensions(65, 65, 20);
    Sample.ComputeNormalsOff();

    vtkContourFilter Surface = new vtkContourFilter();
    Surface.SetInputConnection(Sample.GetOutputPort());
    Surface.SetValue(0, 0);

    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(Surface.GetOutputPort());
    mapper.ScalarVisibilityOff();

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetColor(actorColor);
    
    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualize the actor
    ren.AddActor(actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }

}
