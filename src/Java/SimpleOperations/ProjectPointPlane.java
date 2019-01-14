import vtk.vtkNativeLibrary;
import vtk.vtkPlane;


public class ProjectPointPlane
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
    vtkPlane Plane = new vtkPlane();
    Plane.SetOrigin(0, 0, 0);
    Plane.SetNormal(0, 0, 1.0);

    double p[] = new double[] {23.1, 54.6, 9.2};
    double origin[] = new double[] {0.0, 0.0, 0.0};
    double normal[] = new double[] {0.0, 0.0, 1.0};
    double projected[] = new double[3];

    Plane.ProjectPoint(p, origin,normal,projected);
    System.out.println("Projected:" + " " +projected[0] + " " + projected[1] + " " + projected[2] );
  }		  
}
