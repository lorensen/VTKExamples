import vtk.vtkNativeLibrary;
import vtk.vtkPiecewiseFunction;

public class PiecewiseFunction 
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
   vtkPiecewiseFunction piecewiseFunction = new vtkPiecewiseFunction();
   piecewiseFunction.AddPoint(0.0, 0.0);
   piecewiseFunction.AddPoint(1.0, 2.0);
   
   double test = piecewiseFunction.GetValue(0.25);
   
   System.out.println( "Test: "  + " " + test); //(should be 0.5)
  }
}
