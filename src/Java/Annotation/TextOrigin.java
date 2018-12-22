import vtk.vtkNativeLibrary;
import vtk.vtkActor;
import vtk.vtkAxes;
import vtk.vtkVectorText;
import vtk.vtkPolyDataMapper;
import vtk.vtkFollower;
import vtk.vtkNamedColors;

import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;


public class TextOrigin  {
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
			  
			   //For Text Actor Color
			   double TextActorColor[] = new double[4];
			   //For Renderer Background Color
			   double BgColor[] = new double[4];
			   
			   
			   //Change Color Name to Use your own Color for Change Actor Color
			   Color.GetColor("IndianRed",TextActorColor);
			   //Change Color Name to Use your own Color for Renderer Background
			   Color.GetColor("LightGrey",BgColor);
			
			   
			   // Create the axes and the associated mapper and actor.
			   vtkAxes Axes = new vtkAxes();
			   Axes.SetOrigin(0, 0, 0);
			   
			   vtkPolyDataMapper AxesMapper = new vtkPolyDataMapper();
			   AxesMapper.SetInputConnection(Axes.GetOutputPort());
			   
			   vtkActor AxesActor = new vtkActor();
			   AxesActor.SetMapper(AxesMapper);
			  
			  // Create the 3D text and the associated mapper and follower (a type of actor).  
			  //Position the text so it is displayed over the origin of the axes.
			  vtkVectorText aText = new vtkVectorText();
			  aText.SetText("Origin");
			  
			  
			  vtkPolyDataMapper TextMapper = new vtkPolyDataMapper();
			  TextMapper.SetInputConnection(aText.GetOutputPort());
			  
			  
			  vtkFollower TextActor = new vtkFollower();
			  TextActor.SetMapper(TextMapper);
			  TextActor.SetScale(0.2, 0.2, 0.2);
			  TextActor.AddPosition(0, -0.1, 0);
			  TextActor.GetProperty().SetColor(TextActorColor);
			  
		  
			  // Create the renderer, render window and interactor.
			  vtkRenderer ren = new vtkRenderer();
			  vtkRenderWindow renWin = new vtkRenderWindow();
			  renWin.AddRenderer(ren);
			  vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
			  iren.SetRenderWindow(renWin);
	        
			  // Visualise the arrow
			  ren.AddActor(TextActor);
			  ren.AddActor(AxesActor);
			  ren.SetBackground(BgColor);
			  ren.ResetCamera();
			  ren.ResetCameraClippingRange();
			  ren.GetActiveCamera().Zoom(1.6);

			  renWin.SetSize(300, 300);
			  renWin.Render();
		
			  iren.Initialize();
			  iren.Start();
	    
	  }
	} 
