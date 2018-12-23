import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkAngleRepresentation2D;
import vtk.vtkAngleWidget;
import vtk.vtkNamedColors;
import vtk.vtkRenderWindow;
import vtk.vtkRenderer;


public class AngleWidget2D  {
  //private static final long serialVersionUID = 1L;
	  
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
		
    // An interactor
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		  
    double pos1[] = new double[] {50.0, 200.0, 0.0};
    double pos2[] = new double[] {200.0, 20.0, 0.0};
    double center[] =new double[] {100.0, 100.0, 0.0};
	  
    vtkAngleRepresentation2D Rep = new vtkAngleRepresentation2D();
    Rep.ArcVisibilityOff();
		  
		
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetInteractor(iren);
    iren.SetRenderWindow(renWin);
    ren.ResetCamera();
    ren.SetBackground(BgColor);
	       
    // Angle Widget  
    vtkAngleWidget angleWidget = new vtkAngleWidget();
    angleWidget.SetInteractor(iren);
    angleWidget .CreateDefaultRepresentation();
    angleWidget.SetRepresentation(Rep);

    angleWidget.On();
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
	  	  
    Rep.SetPoint1DisplayPosition(pos1);
    Rep.SetPoint2DisplayPosition(pos2);
    Rep.SetCenterDisplayPosition(center);
    Rep.Ray1VisibilityOn();
    Rep.Ray2VisibilityOn();
    Rep.ArcVisibilityOn();
	  	  
    iren.Start();

  }
} 
