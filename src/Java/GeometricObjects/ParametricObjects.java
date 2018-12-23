import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkParametricFunctionSource;
import vtk.vtkProperty;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;


import vtk.vtkParametricFigure8Klein;
//Uncomment one of the following includes that correspond
//import vtk.vtkParametricBoy;
//import vtk.vtkParametricConicSpiral;
//import vtk.vtkParametricCrossCap ;
//import vtk.vtkParametricDini ;
//import vtk.vtkParametricEllipsoid;
//import vtk.vtkParametricEnneper;
//import vtk.vtkParametricKlein;
//import vtk.vtkParametricMobius;
//import vtk.vtkParametricRandomHills;
//import vtk.vtkParametricRoman;
//import vtk.vtkParametricSpline;
//import vtk.vtkParametricSuperEllipsoid;
//import vtk.vtkParametricSuperToroid;
//import vtk.vtkParametricTorus;



 
public class ParametricObjects 
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
		    
    //For Back Color
    double BackColor[] = new double[4];
    //For Diffuse Color
    double DiffuseColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
		  
			   
		   
    //Change Color Name to Use your own Color for Change Back Color
    Color.GetColor("Navy",BackColor);
    //Change Color Name to Use your own Color for Change Diffuse Color
    Color.GetColor("Red",DiffuseColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Cornsilk",BgColor);

		    
    vtkParametricFigure8Klein ParametricObject = new vtkParametricFigure8Klein();
		    
    // Uncomment one of the following and
    // ensure the matching include (above) is umcommented).
    //vtkParametricBoy parametricObject = new vtkParametricBoy();
    //vtkParametricConicSpiral parametricObject = new vtkParametricConicSpiral();
    //vtkParametricCrossCap parametricObject = new vtkParametricCrossCap();
    //vtkParametricDini parametricObject = new vtkParametricDini();
    //vtkParametricEllipsoid parametricObject = new vtkParametricEllipsoid();
    //vtkParametricEnneper parametricObject = new vtkParametricEnneper();
    //vtkParametricKlein parametricObject = new vtkParametricKlein();
    //vtkParametricMobius parametricObject = new vtkParametricMobius();
    //vtkParametricRandomHills parametricObject = new vtkParametricRandomHills();
    //vtkParametricRoman parametricObject = new vtkParametricRoman();
    //vtkParametricSpline parametricObject = new vtkParametricSpline();
    //vtkParametricSuperEllipsoid parametricObject = new vtkParametricSuperEllipsoid();
    //vtkParametricSuperToroid parametricObject = new vtkParametricSuperToroid();
    //vtkParametricToru parametricObject = new vtkParametricToru();
		    
		    
		    
    vtkParametricFunctionSource parametricFunctionSource = new vtkParametricFunctionSource();
    parametricFunctionSource.SetParametricFunction(ParametricObject);
    parametricFunctionSource.Update();

		    
    vtkProperty BackProperty = new vtkProperty();
    BackProperty.SetColor(BackColor);
		    
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(parametricFunctionSource.GetOutputPort());
		    
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetDiffuseColor(DiffuseColor);
    Actor.GetProperty().SetSpecular(0.5);
    Actor.GetProperty().SetSpecularPower(20);
    Actor.SetBackfaceProperty(BackProperty);
		    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
	        
    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(BgColor);
    ren.ResetCamera();
	        

    renWin.SetSize(300, 300);
    renWin.Render();
	    	
	    	
    iren.Initialize();
    iren.Start();

  }
}
