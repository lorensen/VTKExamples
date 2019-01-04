import vtk.vtkNativeLibrary;
import vtk.vtkPerspectiveTransform;
import vtk.vtkTransform;
import vtk.vtkMatrix4x4;

public class PerspectiveTransform 
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
    vtkMatrix4x4 M = new vtkMatrix4x4();
    M.SetElement(0, 0, 1);
    M.SetElement(0, 1, 2);
    M.SetElement(0, 2, 3);
    M.SetElement(0, 3, 4);
    M.SetElement(1, 0, 2);
    M.SetElement(1, 1, 2);
    M.SetElement(1, 2, 3);
    M.SetElement(1, 3, 4);
    M.SetElement(2, 0, 3);
    M.SetElement(2, 1, 2);
    M.SetElement(2, 2, 1);
    M.SetElement(2, 3, 4);
    M.SetElement(3, 0, 4);
    M.SetElement(3, 1, 2);
    M.SetElement(3, 2, 3);
    M.SetElement(3, 3, 4);

    vtkPerspectiveTransform PT = new vtkPerspectiveTransform();
    PT.SetMatrix(M);

    vtkTransform Transform = new vtkTransform();
    Transform.SetMatrix(M);

    double p[] = new double[] {1.0,2.0,3.0};

    double normalProjection[] = new double[3];
    Transform.TransformPoint(p, normalProjection);
    System.out.println(normalProjection[0] + " " + normalProjection[1] + " " + normalProjection[2]);

    double perspectiveProjection[] = new double[3];
    PT.TransformPoint(p, perspectiveProjection);
    System.out.println(perspectiveProjection[0] + " " + perspectiveProjection[1] + " " + perspectiveProjection[2]);
  }		  
}
