import vtk.vtkNativeLibrary;
import vtk.vtkPassThrough;
import vtk.vtkSphereSource;

public class PassThrough 
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
  
    // Create a sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.Update();
    
    System.out.println("Points before:" + " " + sphereSource.GetOutput().GetNumberOfPoints());
    
    vtkPassThrough passThrough = new vtkPassThrough();
    passThrough.SetInputConnection(sphereSource.GetOutputPort());
    passThrough.Update();
    passThrough.GetOutput();

    System.out.println("Points after:" + " " + sphereSource.GetOutput().GetNumberOfPoints());
   
  }
}
