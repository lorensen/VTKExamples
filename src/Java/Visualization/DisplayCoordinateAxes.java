import vtk.vtkActor;
import vtk.vtkAxesActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkOrientationMarkerWidget;
import vtk.vtkSphereSource;

public class DisplayCoordinateAxes
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
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("SlateGray", Bgcolor);
    
    //Sphere1
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0 );
    sphereSource.SetRadius(1.0);
    sphereSource.Update();
    
    vtkPolyDataMapper sphereMapper  = new vtkPolyDataMapper();
    sphereMapper.SetInputData (sphereSource.GetOutput());
    
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetWindowName("Display Coordinate Axes");
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.AddActor(sphereActor);
    ren.SetBackground(Bgcolor);
    
    vtkAxesActor axes = new vtkAxesActor();
    
    vtkOrientationMarkerWidget widget = new vtkOrientationMarkerWidget();
    double rgba[] = new double[] {0.0, 0.0, 0.0, 0.0};
    colors.GetColor("Carrot",rgba);
    widget.SetOutlineColor(rgba[0], rgba[1], rgba[2]);
    widget.SetOrientationMarker(axes);
    widget.SetInteractor(iren);
    widget.SetViewport( 0.0, 0.0, 0.4, 0.4 );
    widget.SetEnabled(1);
    widget.InteractiveOn();
    
    ren.GetActiveCamera().Azimuth(50);
    ren.GetActiveCamera().Elevation(-30);
    ren.ResetCamera();
    
    renWin.SetSize(640, 480);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
