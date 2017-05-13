import vtk.*;

public class WritePolyData
{

  static
  {
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
    System.loadLibrary("vtkImagingJava");
    System.loadLibrary("vtkGraphicsJava");
    System.loadLibrary("vtkRenderingJava");
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
