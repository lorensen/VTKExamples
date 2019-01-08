import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPoints;
import vtk.vtkVertexGlyphFilter;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper2D;
import vtk.vtkActor2D;

public class Actor2D 
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
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Lime", actorColor);
    colors.GetColor("DarkSlateGray", Bgcolor);

    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(10, 10, 0);
    Points.InsertNextPoint(100, 100, 0);
    Points.InsertNextPoint(200, 200, 0);

    vtkPolyData PolyData = new vtkPolyData();
    PolyData.SetPoints(Points);

    vtkVertexGlyphFilter GlyphFilter = new vtkVertexGlyphFilter();
    GlyphFilter.SetInputData(PolyData);
    GlyphFilter.Update();

    vtkPolyDataMapper2D Mapper = new vtkPolyDataMapper2D();
    Mapper.SetInputConnection(GlyphFilter.GetOutputPort());
    Mapper.Update();

    vtkActor2D Actor = new vtkActor2D();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor);
    Actor.GetProperty().SetPointSize(8);

    // Create the renderer, render window and Interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Add the actor to the scene
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
