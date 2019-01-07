import vtk.vtkActor;
import vtk.vtkAppendPolyData;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataConnectivityFilter;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderer;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkSphereSource;


public class ColorDisconnectedRegions {
  private static final long serialVersionUID = 1L;


  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
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
  // -----------------------------------------------------------------


  public static void main(String s[]) {
    // Create some spheres
    vtkSphereSource sphere1 = new vtkSphereSource();
    sphere1.Update();

    vtkSphereSource sphere2 = new vtkSphereSource();
    sphere2.SetCenter(5.0, 0.0, 0.0);
    sphere2.Update();

    vtkSphereSource sphere3 = new vtkSphereSource();
    sphere3.SetCenter(10.0, 0.0, 0.0);
    sphere3.Update();

    vtkAppendPolyData appendFilter = new vtkAppendPolyData();
    appendFilter.AddInputConnection(sphere1.GetOutputPort());
    appendFilter.AddInputConnection(sphere2.GetOutputPort());
    appendFilter.AddInputConnection(sphere3.GetOutputPort());
    appendFilter.Update();

    vtkPolyDataConnectivityFilter connectivityFilter = new vtkPolyDataConnectivityFilter();
    connectivityFilter.SetInputConnection(appendFilter.GetOutputPort());
    connectivityFilter.SetExtractionModeToAllRegions();
    connectivityFilter.ColorRegionsOn();
    connectivityFilter.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(connectivityFilter.GetOutputPort());
    mapper.SetScalarRange(connectivityFilter.GetOutput().GetPointData().GetArray("RegionId").GetRange());
    mapper.Update();

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(actor);
    ren.ResetCamera();
    ren.GetActiveCamera().Zoom(0.9);

    renWin.SetSize(600, 600);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
