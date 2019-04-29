import vtk.vtkNativeLibrary;
import vtk.vtkFunctionParser;

public class FunctionParser 
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
   vtkFunctionParser functionParser = new vtkFunctionParser();
   functionParser.SetFunction("a+b");
   functionParser.SetScalarVariableValue( "a", 2);
   functionParser.SetScalarVariableValue( "b", 3);
   
   double result = functionParser.GetScalarResult();
   
   System.out.println("Result:" +" " +result);
  }
}
