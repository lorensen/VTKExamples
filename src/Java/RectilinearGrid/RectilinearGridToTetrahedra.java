import vtk.vtkDoubleArray;
import vtk.vtkNativeLibrary;
import vtk.vtkRectilinearGrid;
import vtk.vtkRectilinearGridToTetrahedra;
import vtk.vtkXMLUnstructuredGridWriter;

public class RectilinearGridToTetrahedra 
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
    String Filename = args[0];
	
    // Create a grid
    vtkRectilinearGrid grid = new vtkRectilinearGrid();
    
    grid.SetDimensions(5,4,3);

    vtkDoubleArray xArray = new vtkDoubleArray();
    xArray.InsertNextValue(0.0);
    xArray.InsertNextValue(1.0);
    xArray.InsertNextValue(2.0);
    xArray.InsertNextValue(3.0);
    xArray.InsertNextValue(4.0);
    
    vtkDoubleArray yArray = new vtkDoubleArray();
    yArray.InsertNextValue(0.0);
    yArray.InsertNextValue(1.0);
    yArray.InsertNextValue(2.0);
    yArray.InsertNextValue(3.0);
    
    vtkDoubleArray zArray = new vtkDoubleArray();
    zArray.InsertNextValue(0.0);
    zArray.InsertNextValue(1.0);
    zArray.InsertNextValue(2.0);
    
    grid.SetXCoordinates(xArray);
    grid.SetYCoordinates(yArray);
    grid.SetZCoordinates(zArray);
    
    vtkRectilinearGridToTetrahedra rectilinearGridToTetrahedra = new vtkRectilinearGridToTetrahedra();
    rectilinearGridToTetrahedra.SetInputData(grid);
    rectilinearGridToTetrahedra.Update();

    vtkXMLUnstructuredGridWriter writer = new vtkXMLUnstructuredGridWriter();
    writer.SetFileName(Filename);
    writer.SetInputConnection(rectilinearGridToTetrahedra.GetOutputPort());
    writer.Write();
    
    System.out.println("There are " + " " + rectilinearGridToTetrahedra.GetOutput().GetNumberOfCells() + " " + " cells."); 

  }
}
