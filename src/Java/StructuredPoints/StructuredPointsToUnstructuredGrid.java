import vtk.vtkNativeLibrary;
import vtk.vtkStructuredPoints;
import vtk.vtkPoints;
import vtk.vtkUnstructuredGrid;
import vtk.vtkXMLUnstructuredGridWriter;

public class StructuredPointsToUnstructuredGrid 
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
      System.err.println("Usage: java -classpath ... Filename(.vtu) e.g output.vtu");
      return;
    }
    String outputFilename = args[0];
    
    // Create a structuredpoints
    vtkStructuredPoints structuredPoints = new vtkStructuredPoints();

    // Specify the size of the image data
    structuredPoints.SetDimensions(2,3,1);
    int VTK_DOUBLE = 11;
    structuredPoints.AllocateScalars(VTK_DOUBLE,1);

    int dims[] = new int[3];
    dims=structuredPoints.GetDimensions();
    
    System.out.println("Dims: " + "\n" + " x: " + " " + dims[0] + " " +  " y: " + dims[1] + " z: " + " " + dims[2] );
    System.out.println("Number of points: " + " " + structuredPoints.GetNumberOfPoints());
    System.out.println("Number of cells: " + " " + structuredPoints.GetNumberOfCells());
    
    // Copy the points from the StructuredPoints to the UnstructuredGrid
    vtkPoints points = new vtkPoints();

    //retrieve the entries from the grid and print them to the screen
    double p[] = new double[3];
    for(int i = 0; i < structuredPoints.GetNumberOfPoints(); i++)
    {
      structuredPoints.GetPoint(i, p);
      points.InsertNextPoint(p);
    }

    vtkUnstructuredGrid ug = new vtkUnstructuredGrid();
    ug.SetPoints(points);
    
    vtkXMLUnstructuredGridWriter writer = new vtkXMLUnstructuredGridWriter();
    writer.SetFileName(outputFilename);
    writer.SetInputData(ug);
    writer.Write();

  }
}
