import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkDataSetMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkShrinkFilter;
import vtk.vtkElevationFilter;


public class LoopShrink 
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
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("White", Bgcolor);
    
    vtkSphereSource sphere = new vtkSphereSource();
    sphere.SetThetaResolution(12); sphere.SetPhiResolution(12);
    
    vtkShrinkFilter shrink = new vtkShrinkFilter();
    shrink.SetInputConnection(sphere.GetOutputPort());
    shrink.SetShrinkFactor(0.9);
    
    vtkElevationFilter colorIt = new vtkElevationFilter();
    colorIt.SetInputConnection(shrink.GetOutputPort());
    colorIt.SetLowPoint(0,0,-.5);
    colorIt.SetHighPoint(0,0,.5);
    
    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputConnection(colorIt.GetOutputPort());
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(actor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
