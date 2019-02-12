import vtk.vtkNativeLibrary;
import vtk.vtkPLYWriter;
import vtk.vtkXMLPolyDataReader;

public class ConvertFile
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
    if (args.length != 2) 
    {
      System.err.println("Usage: java -classpath ... InputVTP Filename(.vtp) OutputFilename(.ply) e.g input.vtp output.ply");
      return;
    } 
    
    String inputFileName = args[0];
    String outputFileName = args[1];

    vtkXMLPolyDataReader reader = new vtkXMLPolyDataReader();
    reader.SetFileName(inputFileName);
    reader.Update();

    vtkPLYWriter writer = new vtkPLYWriter();
    writer.SetFileName(outputFileName);
    writer.SetInputConnection(reader.GetOutputPort());
    writer.Update();
  }
}
