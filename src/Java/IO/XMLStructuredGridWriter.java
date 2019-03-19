import vtk.vtkNativeLibrary;
import vtk.vtkStructuredGrid;
import vtk.vtkPoints;
import vtk.vtkXMLStructuredGridWriter;


public class XMLStructuredGridWriter
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
      System.err.println("Usage: java -classpath ... Filename(.vts) e.g output.vts");
      return;
    }
    String Filename = args[0];
    
    // Create a grid
    vtkStructuredGrid structuredGrid = new vtkStructuredGrid();
    
    vtkPoints points = new vtkPoints();
    points.InsertNextPoint(0, 0, 0);
    points.InsertNextPoint(1, 0, 0);
    points.InsertNextPoint(0, 1, 0);
    points.InsertNextPoint(1, 1, 0);
    points.InsertNextPoint(0, 2, 0);
    points.InsertNextPoint(1, 2, 1);
    
    // Specify the dimensions of the grid
    structuredGrid.SetDimensions(2,3,1);
    structuredGrid.SetPoints(points);
    
    // Write file
    vtkXMLStructuredGridWriter writer = new vtkXMLStructuredGridWriter();
    writer.SetFileName(Filename);
    writer.SetInputData(structuredGrid);
    writer.Write();

  }
}
