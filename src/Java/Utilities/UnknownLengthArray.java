import vtk.vtkNativeLibrary;
import vtk.vtkFloatArray;

public class UnknownLengthArray 
{
  //-----------------------------------------------------------------
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
  //-----------------------------------------------------------------
			
  public static void main(String s[]) 
  {	
    vtkFloatArray Distances = new vtkFloatArray();
    Distances.SetName("Distances");
    Distances.SetNumberOfComponents(1);
    //set values
    for(int i = 0; i < 5; i++)
    {
      double f = i + 0.1;
      //this will allocate memory as necessary
      Distances.InsertNextValue(f);
    }
    //get values
    for(int i = 0; i <Distances.GetNumberOfTuples(); i++)
    {
      double f = Distances.GetValue(i);
      System.out.println(f);
    }		
  }
}
