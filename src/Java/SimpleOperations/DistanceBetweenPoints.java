import vtk.vtkNativeLibrary;
import vtk.vtkMath;


public class DistanceBetweenPoints 
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
	
public static void main(String s[]) 
{					  
  // Create two points.
  double p0[] = new double[] {0.0, 0.0, 0.0};
  double p1[] = new double[] {1.0, 1.0, 1.0};
		
  // Find the squared distance between the points.
  vtkMath squaredDistance = new vtkMath();
  double squaredDist = squaredDistance.Distance2BetweenPoints(p0, p1);
		
  // Take the square root to get the Euclidean distance between the points.
  double distance = Math.sqrt(squaredDist);
		
  // Output the results.
  System.out.println("Squared Distance:" + " " + squaredDist);
  System.out.println("Distance:" + " " + distance);

 }
}
