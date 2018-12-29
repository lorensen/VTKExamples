import vtk.vtkActor;
import vtk.vtkCellArray;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkPolygon;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;

public class Polygon  
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

    colors.GetColor("Red", actorColor);
    colors.GetColor("White", Bgcolor);

    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0.0,0.0,0.0);
    Points.InsertNextPoint(1.0,0.0,0.0);
    Points.InsertNextPoint(1.0,1.0,0.0);
    Points.InsertNextPoint(0.0,1.0,0.0);

          
    vtkPolygon Polygon = new vtkPolygon();
    Polygon.GetPointIds().SetNumberOfIds(4);
    Polygon.GetPointIds().SetId(0, 0);
    Polygon.GetPointIds().SetId(1, 1);
    Polygon.GetPointIds().SetId(2, 2);
    Polygon.GetPointIds().SetId(3, 3);

        
    vtkCellArray Polygons = new vtkCellArray();
    Polygons.InsertNextCell(Polygon);


    vtkPolyData PolygonPolyData = new vtkPolyData();
    PolygonPolyData.SetPoints(Points);
    PolygonPolyData.SetPolys(Polygons);


    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(PolygonPolyData);


    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor); 
    Actor.GetProperty().SetLineWidth(5);
        
    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();	  
       
  }
} 
