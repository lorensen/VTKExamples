import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkVertex;
import vtk.vtkCellArray;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;


public class Vertex
{
  //-----------------------------------------------------------------
  //Load VTK library and print which library was not properly loaded
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

  public static void main(String s[]) 
  {
      
    vtkNamedColors Color = new vtkNamedColors();

    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];

         
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("OrangeRed",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("DarkSlateGray",BgColor);


    //Create a 3D Point
    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0.0,0.0,0.0);

    //Create A Vertex Which in turn represents a 3D point
    vtkVertex Vertex = new vtkVertex();
    Vertex.GetPointIds().SetId(0, 0);

    //Create a Cell Array -  a raw integer list that explicitly represents cell connectivity
    vtkCellArray Vertices = new vtkCellArray();
    Vertices.InsertNextCell(Vertex);

    //Create a PolyData  which represents a geometric structure 
    //consisting of vertices, lines, polygons, and/or triangle strips
    vtkPolyData PolyData = new vtkPolyData();
    PolyData.SetPoints(Points);
    PolyData.SetVerts(Vertices);

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(PolyData);

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetPointSize(15);
    Actor.GetProperty().SetColor(ActorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(BgColor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}  
