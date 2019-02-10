import vtk.vtkNativeLibrary;
import vtk.vtkMath;

    
public class NormalizeVector
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
    double a[] = new double[] {100.0, 2.0, 1.0};
    System.out.println(a[0] + " " + a[1] + " " + a[2]);
    vtkMath M = new vtkMath();
    M.Normalize(a);
    System.out.println(a[0] + " " + a[1] + " " + a[2]);
  }
}
