import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkConvexPointSet;
import vtk.vtkPoints;
import vtk.vtkUnstructuredGrid;
import vtk.vtkDataSetMapper;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyData;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkGlyph3DMapper;

 
public class ConvexPointSet 
{
  //private static final long serialVersionUID = 1L;
	 
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
    //For Point Actor Color
    double PointActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
		  
			   
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Cyan",ActorColor);
    //Change Color Name to Use your own Color for Change Point Actor Color
    Color.GetColor("OrangeRed",PointActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("DarkOrange",BgColor);

    vtkConvexPointSet CPS = new vtkConvexPointSet();
    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0, 0, 0);
    Points.InsertNextPoint(1, 0, 0);
    Points.InsertNextPoint(1, 1, 0);
    Points.InsertNextPoint(0, 1, 0);
    Points.InsertNextPoint(0, 0, 1);
    Points.InsertNextPoint(1, 0, 1);
    Points.InsertNextPoint(1, 1, 1);
    Points.InsertNextPoint(0, 1, 1);
    Points.InsertNextPoint(0.5, 0, 0);
    Points.InsertNextPoint(1, 0.5, 0);
    Points.InsertNextPoint(0.5, 1, 0);
    Points.InsertNextPoint(0, 0.5, 0);
    Points.InsertNextPoint(0.5, 0.5, 0);
		    
    for (int i = 0; i < 13; ++i)
    {
      CPS.GetPointIds().InsertId(i, i);
    }
		    
    vtkUnstructuredGrid UG = new vtkUnstructuredGrid();
    UG.Allocate(1, 1);
    UG.InsertNextCell(CPS.GetCellType(), CPS.GetPointIds());
    UG.SetPoints(Points);
		    
		    
    vtkDataSetMapper Mapper = new vtkDataSetMapper();
    Mapper.SetInputData(UG);   
		    
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(ActorColor);
    Actor.GetProperty().SetLineWidth(3.0);
    Actor.GetProperty().EdgeVisibilityOn();
		    
    // Glyph the points
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.SetRadius(0.03);
    Sphere.SetPhiResolution(21);
    Sphere.SetThetaResolution(21);
		    

    vtkPolyData PolyData = new vtkPolyData();
    PolyData.SetPoints(Points);
		    
    vtkGlyph3DMapper PointMapper = new vtkGlyph3DMapper();
    PointMapper.SetInputData(PolyData);
    PointMapper.SetSourceConnection(Sphere.GetOutputPort());

    vtkActor PointActor = new vtkActor();
    PointActor.SetMapper(PointMapper);
    PointActor.GetProperty().SetColor(PointActorColor);
		    
		    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
	        
    // Visualise the arrow
    ren.AddActor(Actor);
    ren.AddActor(PointActor);
    ren.SetBackground(BgColor);
    ren.ResetCamera();
    ren.GetActiveCamera().Azimuth(210);
    ren.GetActiveCamera().Elevation(30);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
