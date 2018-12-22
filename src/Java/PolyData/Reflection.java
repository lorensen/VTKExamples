import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkConeSource;
import vtk.vtkReflectionFilter;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkDataSetMapper;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;

public class Reflection  {
	  
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
		   
		   //For Cone Actor
		   double ConeActorColor[] = new double[4];
		   
		   //For Reflection Actor
		   double ReflectionActorColor[] = new double[4];
		   
		   //Renderer Background Color	   
		   double BgColor[] = new double[4];
		   
		   
		   //Change Color Name to Use your own Color for Cone Actor
		   Color.GetColor("Mint",ConeActorColor);
		   
		 //Change Color Name to Use your own Color for Reflection Actor
		   Color.GetColor("Tomato",ReflectionActorColor);
		   
		   
		   //Change Color Name to Use your own Color for Renderer Background
		   Color.GetColor("Wheat",BgColor);

		   // Create a Cone
		   vtkConeSource ConeSource = new vtkConeSource();
		   ConeSource.Update();
	
		   // Create a mapper and actor
		   vtkPolyDataMapper ConeMapper = new vtkPolyDataMapper();
		   ConeMapper.SetInputConnection(ConeSource.GetOutputPort());
		   
	
		   vtkActor ConeActor = new vtkActor();
		   ConeActor.SetMapper(ConeMapper);
		   ConeActor.GetProperty().SetColor(ConeActorColor);

		   // Reflection
		   vtkReflectionFilter ReflectionFilter = new vtkReflectionFilter();
		   ReflectionFilter.SetInputConnection(ConeSource.GetOutputPort());
		   ReflectionFilter.CopyInputOff();
		   ReflectionFilter.Update();
		   
		   vtkDataSetMapper ReflectionMapper = new vtkDataSetMapper();
		   ReflectionMapper.SetInputConnection(ReflectionFilter.GetOutputPort());

		   vtkActor ReflectionActor = new vtkActor();
		   ReflectionActor.SetMapper(ReflectionMapper);
		   ReflectionActor.GetProperty().SetColor(ReflectionActorColor);

	
		   // Create the renderer, render window and interactor.
		   vtkRenderer ren = new vtkRenderer();
		   vtkRenderWindow renWin = new vtkRenderWindow();
		   renWin.AddRenderer(ren);
		   vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		   iren.SetRenderWindow(renWin);
			    
		   // Visualise the arrow
		   ren.AddActor(ConeActor);
		   ren.AddActor(ReflectionActor);
		   ren.SetBackground(BgColor);
		   ren.ResetCamera();
		      
		   renWin.SetSize(300,300);
		   renWin.Render();

		   iren.Initialize();
		   iren.Start();
	
	  }
	} 
