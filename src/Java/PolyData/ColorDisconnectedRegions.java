import vtk.vtkActor;
import vtk.vtkSphereSource;
import vtk.vtkAppendPolyData;
import vtk.vtkPolyDataConnectivityFilter;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;


public class ColorDisconnectedRegions 
{
	  
	  // -----------------------------------------------------------------
	  // Load VTK library and print which library was not properly loaded
	  static {
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
		    // Create some spheres
		    vtkSphereSource Sphere1 = new vtkSphereSource();
		    Sphere1.Update();
		    
		    vtkSphereSource Sphere2 = new vtkSphereSource();
		    Sphere2.SetCenter(5.0,0.0,0.0);
		    Sphere2.Update();
		    
		    
		    vtkSphereSource Sphere3 = new vtkSphereSource();
		    Sphere3.SetCenter(10.0,0.0,0.0);
		    Sphere3.Update();
		    
		   
		    vtkAppendPolyData AppendFilter = new vtkAppendPolyData();
			AppendFilter.AddInputConnection(Sphere1.GetOutputPort());
			AppendFilter.AddInputConnection(Sphere2.GetOutputPort());
			AppendFilter.AddInputConnection(Sphere3.GetOutputPort());
			AppendFilter.Update();
			  
			  
			vtkPolyDataConnectivityFilter ConnectivityFilter = new vtkPolyDataConnectivityFilter();
			ConnectivityFilter.SetInputConnection(AppendFilter.GetOutputPort());
			ConnectivityFilter.SetExtractionModeToAllRegions();
			ConnectivityFilter.ColorRegionsOn();
			ConnectivityFilter.Update();
			  
				  
			//Create a Mapper and Actor
			vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
			Mapper.SetInputConnection(ConnectivityFilter.GetOutputPort());
			Mapper.SetScalarRange(ConnectivityFilter.GetOutput().GetPointData().GetArray("RegionId").GetRange());
			Mapper.Update();
		
			  
			vtkActor Actor = new vtkActor();
			Actor.SetMapper(Mapper);


			// Create the renderer, render window and interactor.
		    vtkRenderer ren = new vtkRenderer();
		    vtkRenderWindow renWin = new vtkRenderWindow();
		    renWin.AddRenderer(ren);
		    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		    iren.SetRenderWindow(renWin);
				    
		    // Visualise the arrow
		    ren.AddActor(Actor);
		    ren.ResetCamera();
			      
		    renWin.SetSize(300,300);
		    renWin.Render();

		    iren.Initialize();
		    iren.Start();
			
		
	  }
}
