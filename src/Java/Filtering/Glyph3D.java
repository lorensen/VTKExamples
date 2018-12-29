import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkNamedColors;
import vtk.vtkRenderWindow;
import vtk.vtkRenderer;
import vtk.vtkPolyDataMapper;
import vtk.vtkActor;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkGlyph3D;
import vtk.vtkInteractorStyleImage;
import vtk.vtkCubeSource;

public class Glyph3D 
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
			
		//For Renderer Background Color
		double BgColor[] = new double[4];
		
		//For Actor Color
		double ActorColor[] = new double[4];
			
		//Change Color Name to Use your own Color for Renderer Background
		Color.GetColor("DarkSeaGreen",BgColor);
		
		//Change Color Name to Use your own Color for Actor
		Color.GetColor("Yellow",ActorColor);

		vtkPoints Points = new vtkPoints();
		Points.InsertNextPoint(0, 0, 0);
		Points.InsertNextPoint(1, 1, 1);
		Points.InsertNextPoint(2, 2, 2);
				  
		vtkPolyData PolyData = new vtkPolyData();
		PolyData.SetPoints(Points);
		
		// Create anything you want here, we will use a cube for the demo.
		vtkCubeSource CubeSource = new vtkCubeSource();

		vtkGlyph3D Glyph3D = new vtkGlyph3D();
		Glyph3D.SetSourceConnection(CubeSource.GetOutputPort());
		Glyph3D.SetInputData(PolyData);
		Glyph3D.Update();
						    		   
		vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		Mapper.SetInputConnection(Glyph3D.GetOutputPort());
		Mapper.Update();
				    				  
		vtkActor Actor = new vtkActor();
		Actor.SetMapper(Mapper);
		Actor.GetProperty().SetColor(ActorColor);
				    				  
		// Create the renderer, render window and interactor.
		vtkRenderer ren = new vtkRenderer();
		vtkRenderWindow renWin = new vtkRenderWindow();
		renWin.AddRenderer(ren);
		vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		iren.SetRenderWindow(renWin);

		// Visualise the arrow
		ren.AddActor(Actor);
		vtkInteractorStyleImage Style = new vtkInteractorStyleImage();
		iren.SetInteractorStyle(Style);
				    				    
		ren.SetBackground(BgColor);
		ren.ResetCamera();
						    			      
		renWin.SetSize(300,300);
		renWin.Render();

		iren.Initialize();
		iren.Start();
				    				  
	}
}

