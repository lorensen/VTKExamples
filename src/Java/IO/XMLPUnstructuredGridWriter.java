import vtk.vtkNativeLibrary;
import vtk.vtkSphereSource;
import vtk.vtkDelaunay3D;
import vtk.vtkXMLPUnstructuredGridWriter;

public class XMLPUnstructuredGridWriter
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
      System.err.println("Usage: java -classpath ... Filename(.pvtu) e.g Test.pvtu");
      return;
    }
    String Filename = args[0];
    
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.Update();
    
    vtkDelaunay3D delaunay = new vtkDelaunay3D();
    delaunay.SetInputConnection(sphereSource.GetOutputPort());
    delaunay.Update();
    
    vtkXMLPUnstructuredGridWriter writer = new vtkXMLPUnstructuredGridWriter();
    writer.SetInputConnection(delaunay.GetOutputPort());
    writer.SetFileName(Filename);
    writer.SetNumberOfPieces(4);
    writer.SetStartPiece(0);
    writer.SetEndPiece(3);
    writer.Update();

  }
}
