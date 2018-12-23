import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkSphereSource;
import vtk.vtkOutlineFilter;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;

public class Outline 
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
		  
    //For Actor Color
    double ActorColor[] = new double[4];
    //For Outline Actor Color
    double OutlineActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
		  
			   
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("LightCoral",ActorColor);
    //Change Color Name to Use your own Color for Change Outline Actor Color
    Color.GetColor("Black",OutlineActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Cornsilk",BgColor);


    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.SetCenter(0.0,0.0,0.0);
    Sphere.SetRadius(5.0);
    Sphere.Update();
		  
    //Change Phi and Theta Value for Smooth Surface
    Sphere.SetPhiResolution(20);
    Sphere.SetThetaResolution(20);
		  
    //Create a Mapper and Actor for Sphere
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());


    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(ActorColor);

		    
    // Create the outline 
    vtkOutlineFilter OutLiner = new vtkOutlineFilter();
    OutLiner.SetInputConnection(Sphere.GetOutputPort());

    vtkPolyDataMapper OutlineMapper = new vtkPolyDataMapper();
    OutlineMapper.SetInputConnection(OutLiner.GetOutputPort());
		 
    vtkActor OutlineActor = new vtkActor();
    OutlineActor.SetMapper(OutlineMapper);
    OutlineActor.GetProperty().SetColor(OutlineActorColor);
		    
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
		    
    // Visualise the arrow
    ren.AddActor(Actor);
    ren.AddActor(OutlineActor);
    ren.SetBackground(BgColor);
    ren.GetActiveCamera().Azimuth(40);
    ren.GetActiveCamera().Elevation(30);
    ren.ResetCamera();
    ren.ResetCameraClippingRange();
		      
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
