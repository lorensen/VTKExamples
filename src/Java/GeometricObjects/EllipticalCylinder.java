
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPoints;
import vtk.vtkPolyLine;
import vtk.vtkCellArray;
import vtk.vtkLinearExtrusionFilter;
import vtk.vtkPolyDataMapper;
import vtk.vtkProperty;
import vtk.vtkCamera;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyData;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;



public class EllipticalCylinder  
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
		    //For Line Actor Color
		    double LineActorColor[] = new double[4];
		    //For Back Color
		    double BackColor[] = new double[4];
		    //Renderer Background Color
		    double BgColor[] = new double[4];
		  
			   
		    //Change Color Name to Use your own Color for Change Actor Color
		    Color.GetColor("Cyan",ActorColor);
		    //Change Color Name to Use your own Color for Change line Actor Color
		    Color.GetColor("OrangeRed",LineActorColor);
		    //Change Color Name to Use your own Color for Back
		    Color.GetColor("OrangeRed",BackColor);
		    //Change Color Name to Use your own Color for Renderer Background
		    Color.GetColor("DimGray",BgColor);
		    
		    
		    double angle = 0;
		    double r1, r2;
		    double centerX, centerY;
		    r1 = 50;
		    r2 = 30;
		    centerX = 10.0;
		    centerY = 5.0;
		    

		    vtkPoints Points = new vtkPoints();
		    int id = 0;
		    while (angle <= 2.0 * Math.PI + (Math.PI / 60.0))
		    {
		      Points.InsertNextPoint(r1 * Math.cos(angle)+centerX,r2 * Math.sin(angle)+ centerY, 0.0);
		      angle = angle + (Math.PI / 60.0);
		      ++id;
		    }
		    
		    vtkPolyLine Line = new vtkPolyLine();
		    Line.GetPointIds().SetNumberOfIds(id);
		    for(int i = 0; i <id; ++i)
	    	  {
	    	    Line.GetPointIds().SetId(i, i);
	    	  }
		    vtkCellArray Lines = new vtkCellArray();
		    Lines.InsertNextCell(Line);
		    
		    vtkPolyData PolyData = new vtkPolyData();
		    PolyData.SetPoints(Points);
		    PolyData.SetLines(Lines);
		    
		    vtkLinearExtrusionFilter Extrude = new vtkLinearExtrusionFilter();
		    Extrude.SetInputData(PolyData);
		    Extrude.SetExtrusionTypeToNormalExtrusion();
		    Extrude.SetVector(0, 0, 100);
		    Extrude.Update();
		    
		    vtkPolyDataMapper LineMapper = new vtkPolyDataMapper();
		    LineMapper.SetInputData(PolyData);
		    
		    vtkActor LineActor = new vtkActor();
		    LineActor.SetMapper(LineMapper);
		    LineActor.GetProperty().SetColor(LineActorColor);

		    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		    Mapper.SetInputConnection(Extrude.GetOutputPort());
		    
		    
		    vtkProperty Back = new vtkProperty();
		    Back.SetColor(BackColor);
		    
		    vtkActor Actor = new vtkActor();
		    Actor.SetMapper(Mapper);
		    Actor.GetProperty().SetColor(ActorColor);
		    Actor.SetBackfaceProperty(Back);
		    
		    vtkCamera Camera = new vtkCamera();
		    Camera.SetPosition(0, 1, 0);
		    Camera.SetFocalPoint(0, 0, 0);
		    Camera.SetViewUp(0, 0, 1);
		    Camera.Azimuth(30);
		    Camera.Elevation(30);
		    
		    
		    // Create the renderer, render window and interactor.
	        vtkRenderer ren = new vtkRenderer();
	        vtkRenderWindow renWin = new vtkRenderWindow();
	        renWin.AddRenderer(ren);
	        vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
	        iren.SetRenderWindow(renWin);
	        
	        // Visualise the arrow
	        ren.AddActor(Actor);
	        ren.AddActor(LineActor);
	        ren.SetBackground(BgColor);
	        ren.SetActiveCamera(Camera);
	        ren.ResetCamera();
	        ren.ResetCameraClippingRange();

	        renWin.SetSize(300, 300);
	        renWin.Render();
	    

	        iren.Initialize();
	        iren.Start();

	  }
}
