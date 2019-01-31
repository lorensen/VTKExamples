import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkGraphLayoutView;
import vtk.vtkMutableUndirectedGraph;


public class GraphPoints 
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
   
     vtkMutableUndirectedGraph graph = new vtkMutableUndirectedGraph();

     // Create 3 vertices
     int v1 = graph.AddVertex();
     int v2 = graph.AddVertex();
     int v3 = graph.AddVertex();
     
     graph.AddGraphEdge(v1, v2);
     graph.AddGraphEdge(v1, v3);

     vtkPoints points = new vtkPoints();
     points.InsertNextPoint(0.0, 0.0, 0.0);
     points.InsertNextPoint(1.0, 0.0, 0.0);
     points.InsertNextPoint(0.0, 1.0, 0.0);

     graph.SetPoints(points);

     System.out.println("Number of output points: " + " " + graph.GetPoints().GetNumberOfPoints());

     vtkGraphLayoutView graphLayoutView = new vtkGraphLayoutView();
     graphLayoutView.AddRepresentationFromInput(graph);
     graphLayoutView.SetLayoutStrategy("Pass Through");
     graphLayoutView.ResetCamera();
     graphLayoutView.Render();
     graphLayoutView.GetInteractor().Start();

  }
}
