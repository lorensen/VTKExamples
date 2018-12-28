import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkCellArray;
import vtk.vtkPolyData;
import vtk.vtkTriangleStrip;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;

public class TriangleStrip  
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

        
  public static void main(String s[]) 
  {	 

    vtkNamedColors Color = new vtkNamedColors();


    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
          
             
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Lime",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Aqua",BgColor);


    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0.0,0.0,0.0);
    Points.InsertNextPoint(0.0,1.0,0.0);
    Points.InsertNextPoint(1.0,0.0,0.0);
    Points.InsertNextPoint(1.5,1.0,0.0);

    vtkTriangleStrip TriangleStrip = new vtkTriangleStrip();
    TriangleStrip.GetPointIds().SetNumberOfIds(4);
    TriangleStrip.GetPointIds().SetId(0, 0);
    TriangleStrip.GetPointIds().SetId(1, 1);
    TriangleStrip.GetPointIds().SetId(2, 2);
    TriangleStrip.GetPointIds().SetId(3, 3);


    vtkCellArray CellArray = new vtkCellArray();
    CellArray.InsertNextCell(TriangleStrip);

    vtkPolyData TrianglePolyData = new vtkPolyData();
    TrianglePolyData.SetPoints(Points);
    TrianglePolyData.SetPolys(CellArray);

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(TrianglePolyData);


    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().EdgeVisibilityOn();
    Actor.GetProperty().SetColor(ActorColor); 
    Actor.GetProperty().SetLineWidth(2.5);

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
