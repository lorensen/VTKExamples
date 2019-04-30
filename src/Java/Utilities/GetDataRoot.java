import vtk.vtkNativeLibrary;
import vtk.vtkTesting;

public class GetDataRoot 
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
   vtkTesting testHelper = new vtkTesting();
   String dataRoot = testHelper.GetDataRoot();
   
   System.out.print("DataRoot:" + " " + dataRoot);
  }
}
