import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkTriangle;
import vtk.vtkCellArray;
import vtk.vtkPolyData;

public class AddCell
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
    //  Create a triangle
    vtkPoints points = new vtkPoints();
    points.InsertNextPoint ( 1.0, 0.0, 0.0 );
    points.InsertNextPoint ( 0.0, 0.0, 0.0 );
    points.InsertNextPoint ( 0.0, 1.0, 0.0 );

    vtkTriangle triangle = new vtkTriangle();
    triangle.GetPointIds().SetId ( 0, 0 );
    triangle.GetPointIds().SetId ( 1, 1 );
    triangle.GetPointIds().SetId ( 2, 2 );
    
    vtkCellArray triangles = new vtkCellArray();
    triangles.InsertNextCell ( triangle );

    // Create a polydata object
    vtkPolyData polyData = new vtkPolyData();

    // Add the geometry and topology to the polydata
    polyData.SetPoints ( points );
    polyData.SetPolys ( triangles );
        
    System.out.println("There are " + " " + polyData.GetNumberOfCells() + " " + "cells.");
    polyData.GetPolys().InsertNextCell(triangle);
    System.out.println("There are " + " " + polyData.GetNumberOfCells() + " " + "cells.");

  }
}
