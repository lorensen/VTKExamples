import vtk.vtkNativeLibrary;
import vtk.vtkActor;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkSphereSource;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkCompassRepresentation;
import vtk.vtkCompassWidget;
import vtk.vtkRenderWindow;
import vtk.vtkRenderer;


public class CompassWidget  {
	 // private static final long serialVersionUID = 1L;
	  

	  // -----------------------------------------------------------------
	  // Load VTK library and print which library was not properly loaded
	  static {
	    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
	      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
	        if (!lib.IsLoaded()) {
	          System.out.println(lib.GetLibraryName() + " not loaded");
	        }
	      }
	    }
	    vtkNativeLibrary.DisableOutputWindow(null);
	  }
	  // -----------------------------------------------------------------
	  
	  public static void main(String s[]) {
		 
		  
		  vtkNamedColors Color = new vtkNamedColors(); 

		   //For Renderer Background Color
		   double BgColor[] = new double[4];
		   	   //Change Color Name to Use your own Color for Renderer Background
		   Color.GetColor("Black",BgColor);
		   
		   
		   //Create a Sphere
		   vtkSphereSource Sphere = new vtkSphereSource();
		   Sphere.SetCenter(0.0,0.0,0.0);
		   Sphere.SetRadius(4.0);
		   Sphere.Update();
		   
		   //Create a Mapper and Actor
		   vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		   Mapper.SetInputConnection(Sphere.GetOutputPort());

		   vtkActor Actor = new vtkActor();
		   Actor.SetMapper(Mapper);
		
		   // An interactor
		  vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		  
		  vtkCompassRepresentation CompassRepresentation = new vtkCompassRepresentation();
		  vtkCompassWidget CompassWidget = new vtkCompassWidget();
		  CompassWidget.SetRepresentation(CompassRepresentation);
		  CompassWidget.EnabledOn();
		  CompassWidget.SetInteractor(iren);
		  
		  
		  // Create the renderer, render window and interactor.
	    vtkRenderer ren = new vtkRenderer();
	    vtkRenderWindow renWin = new vtkRenderWindow();
	    renWin.AddRenderer(ren);
	    renWin.SetInteractor(iren);
	    iren.SetRenderWindow(renWin);
	        
	    // Visualise the arrow
	    ren.AddActor(Actor);
	    ren.SetBackground(BgColor);
	    ren.ResetCamera();
	        
	    CompassWidget.EnabledOn();

	    renWin.SetSize(300, 300);
	    renWin.Render();
	        
		  iren.Start();
	     iren.Initialize();

	  }
	} 
