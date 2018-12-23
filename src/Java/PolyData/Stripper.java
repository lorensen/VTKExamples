import vtk.vtkSphereSource;
import vtk.vtkStripper;
import vtk.vtkNativeLibrary;

class Stripper{  
	
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
		
    System.out.println("Number of cells before stripping:" + SphereSource.GetOutput().GetNumberOfCells() );
	
			  
    vtkStripper Stripper = new vtkStripper();
    Stripper.SetInputConnection(SphereSource.GetOutputPort());
    Stripper.Update();

			  
    System.out.println("Number of cells after stripping:" + Stripper.GetOutput().GetNumberOfCells() );
			  
		  		  
  }  
}   
