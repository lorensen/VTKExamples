import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkCellArray;
import vtk.vtkPolyData;
import vtk.vtkTriangle;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;


public class Triangle  
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

    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];

         
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Gold",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("SpringGreen",BgColor);


    // Create a triangle
    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(1.0,0.0,0.0);
    Points.InsertNextPoint(0.0,0.0,0.0);
    Points.InsertNextPoint(0.0,1.0,0.0);

    vtkTriangle Triangle = new vtkTriangle();
    Triangle.GetPointIds().SetId(0, 0);
    Triangle.GetPointIds().SetId(1, 1);
    Triangle.GetPointIds().SetId(2, 2);

    vtkCellArray CellArray = new vtkCellArray();
    CellArray.InsertNextCell(Triangle);


    // Create a polydata object
    vtkPolyData TrianglePolyData = new vtkPolyData();
    // Add the geometry and topology to the polydata
    TrianglePolyData.SetPoints(Points);
    TrianglePolyData.SetPolys(CellArray);

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(TrianglePolyData);

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().EdgeVisibilityOn();
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
