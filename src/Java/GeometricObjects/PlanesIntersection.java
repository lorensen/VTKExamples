import vtk.vtkSphereSource;
import vtk.vtkPoints;
import vtk.vtkPlanesIntersection;
import vtk.vtkNativeLibrary;

class PlanesIntersection{  
	
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
	
	
    public static void main(String args[]){  
    	
    	vtkSphereSource SphereSource = new vtkSphereSource();
		  SphereSource.Update();
		  
		  double bounds[] = new double[6];
		  		  
		  SphereSource.GetOutput().GetBounds(bounds);
		  vtkPoints Box = new vtkPoints();
		  Box.SetNumberOfPoints(8);
		  
		  double xMin, xMax, yMin, yMax, zMin, zMax;
		  xMin = bounds[0]; xMax = bounds[1];
		  yMin = bounds[2]; yMax = bounds[3];
		  zMin = bounds[4]; zMax = bounds[5];

		  
		  Box.SetPoint(0, xMax, yMin, zMax);
		  Box.SetPoint(1, xMax, yMin, zMin);
		  Box.SetPoint(2, xMax, yMax, zMin);
		  Box.SetPoint(3, xMax, yMax, zMax);
		  Box.SetPoint(4, xMin, yMin, zMax);
		  Box.SetPoint(5, xMin, yMin, zMin);
		  Box.SetPoint(6, xMin, yMax, zMin);
		  Box.SetPoint(7, xMin, yMax, zMax);
		  
		  
		  vtkPlanesIntersection PlanesIntersection = new vtkPlanesIntersection();
		  PlanesIntersection.SetBounds(bounds);
		  
		  int intersects = PlanesIntersection.IntersectsRegion(Box);
		  System.out.print("Intersects:" + intersects );
		  
    }  
}   
