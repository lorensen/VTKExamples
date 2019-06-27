import vtk.vtkNativeLibrary;
import vtk.vtkCenterOfMass;
import vtk.vtkPolyData;
import vtk.vtkPoints;

public class CenterOfMass 
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
    vtkPoints points = new vtkPoints();
    points.InsertNextPoint(0,0,0);
    points.InsertNextPoint(1,0,0);
    points.InsertNextPoint(0,1,0);
    points.InsertNextPoint(1,1,0);
    
    vtkPolyData polydata = new vtkPolyData();
    polydata.SetPoints(points);
    
    // Compute the center of mass
    vtkCenterOfMass centerOfMassFilter = new vtkCenterOfMass();
    centerOfMassFilter.SetInputData(polydata);
    centerOfMassFilter.SetUseScalarsAsWeights(false);
    centerOfMassFilter.Update();
    
    double center[] = new double[3];
    center = centerOfMassFilter.GetCenter();
    System.out.print("Center of mass is " + " " + center[0] + " " + center[1] + " " + center[2]);
  }
}
