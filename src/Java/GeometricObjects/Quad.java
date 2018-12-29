import vtk.vtkActor;
import vtk.vtkCellArray;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkQuad;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;

public class Quad 
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
    Color.GetColor("DarkMagenta",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Coral",BgColor);

    //Create four points (must be in counter clockwise order)
    double p0[] = new double[] {0.0, 0.0, 0.0};
    double p1[] = new double[] {1.0, 0.0, 0.0};
    double p2[] = new double[] {1.0, 1.0, 0.0};
    double p3[] = new double[] {0.0, 1.0, 0.0};
      

    //// Add the points to a vtkPoints object
    vtkPoints Points = new vtkPoints(); 
    Points.InsertNextPoint(p0);
    Points.InsertNextPoint(p1);
    Points.InsertNextPoint(p2);
    Points.InsertNextPoint(p3);

    //Create a quad on the four points	  
    vtkQuad Quad = new vtkQuad();
    Quad.GetPointIds().SetId(0, 0);
    Quad.GetPointIds().SetId(1, 1);
    Quad.GetPointIds().SetId(2, 2);
    Quad.GetPointIds().SetId(3, 3);

    //Create a cell array to store the Quad
    vtkCellArray Quads = new vtkCellArray();
    Quads.InsertNextCell(Quad);

    //Create a polydata to store Points and Quad
    vtkPolyData QuadData = new vtkPolyData();
    //Add the points and Quad to the dataset
    QuadData.SetPoints(Points);
    QuadData.SetPolys(Quads);

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(QuadData);

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(ActorColor); 
    Actor.GetProperty().SetLineWidth(5);
     
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
