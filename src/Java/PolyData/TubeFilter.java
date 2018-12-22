import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkLineSource;
import vtk.vtkTubeFilter;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;


public class TubeFilter  
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
		/*
	     	* This example creates a tube around a line. 
	     	* This is helpful because when you zoom the camera, 
	     	* the thickness of a line remains constant, 
	     	* while the thickness of a tube varies.
	     	* */
		
		vtkNamedColors Color = new vtkNamedColors(); 
		 //For Actor
	      	double ActorColor[] = new double[4];
	   	//Renderer Background Color
	   	double BgColor[] = new double[4];
		 
	   	//Change Color Name to Use your own Color for Actor
	   	Color.GetColor("Red",ActorColor);
	   	//Change Color Name to Use your own Color for Renderer Background
	   	Color.GetColor("Gray",BgColor);
	   
	   	// Create a line
	   	vtkLineSource LineSource = new vtkLineSource();
	   	LineSource.SetPoint1(1.0, 0.0, 0.0);
	   	LineSource.SetPoint2(.0, 1.0, 0.0);

	   	// Create a mapper and actor
	   	vtkPolyDataMapper LineMapper = new vtkPolyDataMapper();
	   	LineMapper.SetInputConnection(LineSource.GetOutputPort());
	   

	   	vtkActor LineActor = new vtkActor();
	   	LineActor.SetMapper(LineMapper);
	   	LineActor.GetProperty().SetColor(ActorColor);
	   	LineActor.GetProperty().SetLineWidth(3);
	      
	   	vtkTubeFilter TubeFilter = new vtkTubeFilter();
	   	TubeFilter.SetInputConnection(LineSource.GetOutputPort());
	   	TubeFilter.SetRadius(0.025);
	   	TubeFilter.SetNumberOfSides(50);
	   	TubeFilter.Update();
	   
	   
	   	vtkPolyDataMapper TubeMapper = new vtkPolyDataMapper();
	   	TubeMapper.SetInputConnection(TubeFilter.GetOutputPort());

	   	vtkActor TubeActor = new vtkActor();
	   	TubeActor.SetMapper(TubeMapper);
	   	//Make the tube have some transparency.
	   	TubeActor.GetProperty().SetOpacity(0.5);


	   	// Create the renderer, render window and interactor.
	   	vtkRenderer ren = new vtkRenderer();
	   	vtkRenderWindow renWin = new vtkRenderWindow();
	   	renWin.AddRenderer(ren);
	   	vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
	   	iren.SetRenderWindow(renWin);
		    
	   	// Visualise the arrow
	   	ren.AddActor(LineActor);
	   	ren.AddActor(TubeActor);
	   	ren.SetBackground(BgColor);
	   	ren.ResetCamera();
	      
	   	renWin.SetSize(300,300);
	   	renWin.Render();
	
	   	iren.Initialize();
	   	iren.Start();
	  }
} 
