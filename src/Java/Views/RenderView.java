import vtk.vtkActor;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderView;
import vtk.vtkNamedColors;

public class RenderView
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
        
    colors.GetColor("Crimson", actorColor);
    colors.GetColor("MidnightBlue", Bgcolor);
        
		//Create a Sphere
		vtkSphereSource Sphere = new vtkSphereSource();
		Sphere.SetCenter(0.0,0.0,0.0);
		Sphere.SetRadius(1.0);
		Sphere.Update();
		
		//Create a Mapper and Actor
		vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		Mapper.SetInputConnection(Sphere.GetOutputPort());
		
		vtkActor Actor = new vtkActor();
		Actor.SetMapper(Mapper);
		Actor.GetProperty().SetColor(actorColor);
		
		vtkRenderView RenderView = new vtkRenderView();
		RenderView.SetInteractionModeTo3D();
		RenderView.GetRenderer().AddActor(Actor);
		RenderView.GetRenderer().SetBackground(Bgcolor);
		RenderView.Update();

		RenderView.ResetCamera();
		RenderView.GetInteractor().Start();
	}		  
}
