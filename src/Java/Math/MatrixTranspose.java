import vtk.vtkNativeLibrary;
import vtk.vtkMatrix3x3;

public class MatrixTranspose 
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
    // For a 3x3 matrices
    vtkMatrix3x3 Matrix = new vtkMatrix3x3();
    
    Matrix.SetElement(2, 1, 2.0); // Set element (0,0) to 1.0
    
    System.out.println(Matrix);
    
    Matrix.Transpose();
    
    System.out.println(Matrix); 
  }
}
