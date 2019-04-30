import vtk.vtkNativeLibrary;
import vtk.vtkDiscretizableColorTransferFunction;

public class DiscretizableColorTransferFunction 
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
   vtkDiscretizableColorTransferFunction discretizableColorTransferFunction = new vtkDiscretizableColorTransferFunction();
   discretizableColorTransferFunction.DiscretizeOn();
   discretizableColorTransferFunction.SetNumberOfValues(2);
   
   discretizableColorTransferFunction.AddRGBPoint(0.0, 1, 0, 0);
   discretizableColorTransferFunction.AddRGBPoint(10.0, 0, 1, 0);
   discretizableColorTransferFunction.Build();
   
   double color[] = new double[3];
   discretizableColorTransferFunction.GetColor(1.0, color);
   
   System.out.println(color[0] +" " + color[1] + " " + color[2]);
   
   discretizableColorTransferFunction.GetColor(5.0, color);
   System.out.println(color[0] +" " + color[1] + " " + color[2]);   
  }
}
