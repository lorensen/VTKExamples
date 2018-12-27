import vtk.vtkNativeLibrary;
import vtk.vtkGraphLayoutView;
import vtk.vtkMutableUndirectedGraph;
import vtk.vtkSimple2DLayoutStrategy;

public class VisualizeGraph 
{

  //-----------------------------------------------------------------
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

    vtkMutableUndirectedGraph G = new vtkMutableUndirectedGraph();
    int v1 = G.AddVertex();
    int v2 = G.AddVertex();

    G.AddGraphEdge(v1, v2);
    G.AddGraphEdge(v1, v2);

    vtkGraphLayoutView GraphLayoutView = new vtkGraphLayoutView();
    GraphLayoutView.AddRepresentationFromInput(G);
    GraphLayoutView.SetLayoutStrategy("Simple 2D");
    GraphLayoutView.ResetCamera();
    GraphLayoutView.Render();


    vtkSimple2DLayoutStrategy Simple2DLayoutStrategy = new vtkSimple2DLayoutStrategy();
    Simple2DLayoutStrategy.SetRandomSeed(0);
    GraphLayoutView.GetLayoutStrategy();
    GraphLayoutView.GetInteractor().Start();

  }

}
