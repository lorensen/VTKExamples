import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkSplineWidget2;
import vtk.vtkNamedColors;
import vtk.vtkRenderWindow;
import vtk.vtkRenderer;


public class SplineWidget  
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
		  
    vtkNamedColors Color = new vtkNamedColors(); 

    //For Renderer Background Color
    double BgColor[] = new double[4];
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("DarkSalmon",BgColor);
		
    // An interactor
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		  
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetInteractor(iren);
    iren.SetRenderWindow(renWin);
    ren.ResetCamera();
    ren.SetBackground(BgColor);
	       
    vtkSplineWidget2 splineWidget = new vtkSplineWidget2();
    splineWidget.SetInteractor(iren);
	 	  
		  
    iren.Initialize();
    splineWidget.On();
    iren.Start();
		   
  }
	    
}
	
