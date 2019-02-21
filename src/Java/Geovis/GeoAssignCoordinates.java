import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkMutableDirectedGraph;
import vtk.vtkDoubleArray;
import vtk.vtkGeoAssignCoordinates;
import vtk.vtkGraphMapper;

public class GeoAssignCoordinates 
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
    vtkMutableDirectedGraph g = new vtkMutableDirectedGraph();
    vtkDoubleArray latitude = new vtkDoubleArray();
    latitude.SetName("latitude");

    vtkDoubleArray longitude = new vtkDoubleArray();
    longitude.SetName("longitude");
    
    for(int lat = -90; lat <= 90; lat += 10)
    {
      for(int lon = -180; lon <= 180; lon += 20)
      {
        g.AddVertex();
        latitude.InsertNextValue(lat);
        longitude.InsertNextValue(lon);
      }
    }
    
    g.GetVertexData().AddArray(latitude);
    g.GetVertexData().AddArray(longitude);

    vtkGeoAssignCoordinates assign = new vtkGeoAssignCoordinates();
    assign.SetInputData(g);
    assign.SetLatitudeArrayName("latitude");
    assign.SetLongitudeArrayName("longitude");
    assign.SetGlobeRadius(1.0);
    assign.Update();

    vtkGraphMapper mapper = new vtkGraphMapper();
    mapper.SetInputConnection(assign.GetOutputPort());
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(actor);
    ren.ResetCamera();
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
