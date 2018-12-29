import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkDelaunay2D;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkVertexGlyphFilter;

public class Delaunay2D 
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

    //For PointActor Color 
    double PointActorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];
    //MeshActorColor
    double MeshActorColor[] = new double[4];

    colors.GetColor("Coral", PointActorColor);
    colors.GetColor("DimGray", Bgcolor);
    colors.GetColor("Aquamarine", MeshActorColor);

    //Create a set of heighs on a grid.
    // This is often called a "terrain map".

    vtkPoints Points = new vtkPoints();  
    
    int GridSize = 10;
    for(int x = 0; x < GridSize; x++)
    {
      for(int y = 0; y < GridSize; y++)
      {
        Points.InsertNextPoint(x, y, (x+y)/(y+1));
      }
    }
    
    //Add the grid points to a polydata object
    vtkPolyData PolyData = new vtkPolyData();
    PolyData.SetPoints(Points);
    
    
    //Triangulate the grid points
    vtkDelaunay2D Delaunay = new vtkDelaunay2D();
    Delaunay.SetInputData(PolyData);

    vtkPolyDataMapper MeshMapper = new vtkPolyDataMapper();
    MeshMapper.SetInputConnection(Delaunay.GetOutputPort());

    vtkActor MeshActor = new vtkActor();
    MeshActor.SetMapper(MeshMapper);
    MeshActor.GetProperty().SetColor(MeshActorColor);
    MeshActor.GetProperty().EdgeVisibilityOn();


    vtkVertexGlyphFilter GlyphFilter = new vtkVertexGlyphFilter();
    GlyphFilter.SetInputData(PolyData);

    vtkPolyDataMapper PointMapper = new vtkPolyDataMapper();
    PointMapper.SetInputConnection(GlyphFilter.GetOutputPort());

    vtkActor PointActor = new vtkActor();
    PointActor.GetProperty().SetColor(PointActorColor);
    PointActor.GetProperty().SetPointSize(5);
    PointActor.SetMapper(PointMapper);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(PointActor);
    ren.AddActor(MeshActor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
      
  }	
}
