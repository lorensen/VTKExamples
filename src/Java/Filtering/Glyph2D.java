import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkNamedColors;
import vtk.vtkRenderWindow;
import vtk.vtkRenderer;
import vtk.vtkPolyDataMapper;
import vtk.vtkActor;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkGlyph2D;
import vtk.vtkInteractorStyleImage;
import vtk.vtkRegularPolygonSource;

public class Glyph2D 
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
    vtkNamedColors Color = new vtkNamedColors(); 

    //For Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("IndianRed",BgColor);

    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0, 0, 0);
    Points.InsertNextPoint(1, 1, 0);
    Points.InsertNextPoint(2, 2, 0);

    vtkPolyData PolyData = new vtkPolyData();
    PolyData.SetPoints(Points);

    vtkRegularPolygonSource PolygonSource = new vtkRegularPolygonSource();

    vtkGlyph2D Glyph2D = new vtkGlyph2D();
    Glyph2D.SetSourceConnection(PolygonSource.GetOutputPort());
    Glyph2D.SetInputData(PolyData);
    Glyph2D.Update();

    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Glyph2D.GetOutputPort());
    Mapper.Update();

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise 
    ren.AddActor(Actor);
    vtkInteractorStyleImage Style = new vtkInteractorStyleImage();
    iren.SetInteractorStyle(Style);

    ren.SetBackground(BgColor);
    ren.ResetCamera();

    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
