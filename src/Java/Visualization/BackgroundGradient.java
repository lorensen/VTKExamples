import vtk.vtkActor;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;

import vtk.vtkRenderWindow;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;

public class BackgroundGradient
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
	
	public static void main(String args[]) 
	{
		vtkNamedColors colors = new vtkNamedColors();

		//For Actor Color
		double actorColor[] = new double[4];
		
		//Renderer Background Color
		double Bgcolor[] = new double[4];
		
		//Renderer Background Color
		double Bgcolor_2[] = new double[4];
        
		colors.GetColor("MediumSpringGreen", actorColor);
		colors.GetColor("Banana", Bgcolor);
		colors.GetColor("Tomato", Bgcolor_2);
        
		//Create a Sphere
		vtkSphereSource Sphere = new vtkSphereSource();
		Sphere.Update();

		//Create a Mapper and Actor
		vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		Mapper.SetInputConnection(Sphere.GetOutputPort());

		vtkActor Actor = new vtkActor();
		Actor.SetMapper(Mapper);
		Actor.GetProperty().SetColor(actorColor);
        
		        
		// Create the renderer, render window and interactor.
		vtkRenderer ren = new vtkRenderer();
		vtkRenderWindow renWin = new vtkRenderWindow();
		renWin.AddRenderer(ren);
		vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		iren.SetRenderWindow(renWin);

		// Visualise the arrow
		ren.AddActor(Actor);
		
		//Setting up the background gradient
		ren.GradientBackgroundOn();
		ren.SetBackground(Bgcolor);
		ren.SetBackground2(Bgcolor_2);

		renWin.SetSize(300, 300);
		renWin.Render();

		iren.Initialize();
		iren.Start();
	}
}
