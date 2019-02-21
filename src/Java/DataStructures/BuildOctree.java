import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkOctreePointLocator;
public class BuildOctree 
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
    //  Setup point coordinates
    double x[] = new double[] {1.0, 0.0, 0.0};
    double y[] = new double[] {0.0, 1.0, 0.0};
    double z[] = new double[] {0.0, 0.0, 1.0};

    vtkPoints points = new vtkPoints();

    for(int i = 0; i < 3; ++i)
    {
      points.InsertNextPoint ( x[i], y[i], z[i] );
    }
    
    System.out.println("There are " + " " + points.GetNumberOfPoints() + " " + "points.");

    vtkPolyData polydata = new vtkPolyData();
    polydata.SetPoints(points);

    //Create the tree
    vtkOctreePointLocator octree = new vtkOctreePointLocator();
    octree.SetDataSet(polydata);
    octree.BuildLocator();
    System.out.println("Number of points in tree: " + " " + octree.GetDataSet().GetNumberOfPoints());
    
    double p[] = new double[3];
    octree.GetDataSet().GetPoint(0,p);
    System.out.println("p: " + " " + p[0] + " " + p[1] + " " +p[2]);
  }
}
