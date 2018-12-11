import vtk.*;

public class WritePolyData
{

  // Loading Native Libraries.
  // Now it works in eclipse without any issues.
  static {
	    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
	      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
	        if (!lib.IsLoaded()) {
	          System.out.println(lib.GetLibraryName() + " not loaded");
	        }
	      }
	    }
	    vtkNativeLibrary.DisableOutputWindow(null);
	  }

  public static void main(String[] args)
  {
    //Create 10 points.
    vtkPoints points = new vtkPoints();
   
    for ( int i = 0; i < 10; ++i )
      {
      points.InsertNextPoint ( i, i, i );
      }
   
    //Create a polydata object and add the points to it.
    vtkPolyData polydata = new vtkPolyData();
    polydata.SetPoints(points);
   
    //Write the file
    vtkXMLPolyDataWriter writer = new vtkXMLPolyDataWriter();
    writer.SetFileName("test.vtp");
    writer.SetInput(polydata);
   
    //Optional - set the mode. The default is binary.
    //writer.SetDataModeToBinary();
    //writer.SetDataModeToAscii();
   
    writer.Write();
  }
}
