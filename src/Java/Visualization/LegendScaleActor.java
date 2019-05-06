import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkLegendScaleActor;

public class LegendScaleActor 
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

    colors.GetColor("DarkSlateBlue", Bgcolor);
    
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.Update();
    
    vtkPolyDataMapper sphereMapper  = new vtkPolyDataMapper();
    sphereMapper .SetInputData (sphereSource.GetOutput());
    
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);
	
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    vtkLegendScaleActor legendScaleActor = new vtkLegendScaleActor();
    
    // Visualize
    ren.AddActor(sphereActor);
    ren.AddActor(legendScaleActor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(640, 480);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
