import vtk.vtkNativeLibrary;
import vtk.vtkSphereSource;
import vtk.vtkSimplePointsWriter;

public class SimplePointsWriter 
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
    //parse command line arguments
    if (args.length != 1) 
    {
      System.err.println("Usage: java -classpath ... Filename(.xyz) e.g SimplePointWriter.xyz");
      return;
    }
    String inputFilename = args[0];
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.Update();
    
    vtkSimplePointsWriter writer = new vtkSimplePointsWriter();
    writer.SetFileName(inputFilename);
    writer.SetInputConnection(sphereSource.GetOutputPort());
    writer.Write();
    
  }
}
