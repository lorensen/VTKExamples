import vtk.vtkNativeLibrary;
import vtk.vtkLookupTable;


public class ColorLookupTable
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
          System.out.println(lib.GetLibraryName() + "not loaded");
        }
      }
    }
    vtkNativeLibrary.DisableOutputWindow(null);
  }
  // ------------------------------------------------------------------

  public static void main(String args[]) 
  {
    vtkLookupTable lookupTable = new vtkLookupTable();
    lookupTable.SetTableRange(0.0, 10.0);
    // If you don't want to use the whole color range, you can use
    // SetValueRange, SetHueRange, and SetSaturationRange
    lookupTable.Build();

    double color[] = new double[3];
    lookupTable.GetColor(1.0, color);
    
    System.out.println(color[0]  + " " + color[1] + " " + color[2]);
    
    lookupTable.GetColor(5.0, color);
    
    System.out.println(color[0]  + " " + color[1] + " " + color[2]);

  }
}
