import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkVertexGlyphFilter;

public class VertexGlyphFilter 
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

    colors.GetColor("Black", actorColor);
    colors.GetColor("Gold", Bgcolor);

    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0.0, 0.0, 0.0);
    Points.InsertNextPoint(1.0, 1.0, 1.0);
    Points.InsertNextPoint(2.0, 2.0, 2.0);

    vtkPolyData PolyData = new vtkPolyData();
    PolyData.SetPoints(Points);

    vtkVertexGlyphFilter VGF = new vtkVertexGlyphFilter();
    VGF.AddInputData(PolyData);
    VGF.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(VGF.GetOutputPort());
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetColor(actorColor);
    actor.GetProperty().SetPointSize(10);

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
