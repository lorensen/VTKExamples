import vtk.vtkNativeLibrary;
import vtk.vtkRandomGraphSource;
import vtk.vtkGraphLayoutView;

public class RandomGraphSource 
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
  
    vtkRandomGraphSource randomGraphSource =  new vtkRandomGraphSource();
    randomGraphSource.SetNumberOfVertices(5);
    randomGraphSource.SetNumberOfEdges(4);
    randomGraphSource.SetSeed(1); // This ensures repeatable results for testing. Turn this off for real use.
    randomGraphSource.Update();
    
    vtkGraphLayoutView graphLayoutView = new vtkGraphLayoutView();
    graphLayoutView.AddRepresentationFromInput(randomGraphSource.GetOutput());
    graphLayoutView.ResetCamera();
    graphLayoutView.Render();
    graphLayoutView.GetInteractor().Start();
  
  }
}
