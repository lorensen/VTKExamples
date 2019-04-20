import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkConeSource;
import vtk.vtkInteractorStyleTrackballActor;

public class TrackballActor 
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

    colors.GetColor("SteelBlue", Bgcolor);
    
    // Create a sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(1.0, 0.0, 0.0 );
    sphereSource.Update();

    vtkPolyDataMapper sphereMapper  = new vtkPolyDataMapper();
    sphereMapper .SetInputData (sphereSource.GetOutput());
    
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);
    
    // Create a Cone
    vtkConeSource ConeSource = new vtkConeSource();
        
    vtkPolyDataMapper coneMapper = new vtkPolyDataMapper();
    coneMapper.SetInputConnection(ConeSource.GetOutputPort());

    vtkActor coneActor  = new vtkActor();
    coneActor.SetMapper(coneMapper);
   
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(sphereActor);
    ren.AddActor(coneActor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetWindowName("Trackball Actor");
    renWin.SetSize(300, 300);
    renWin.Render();
    
    vtkInteractorStyleTrackballActor style = new vtkInteractorStyleTrackballActor();
    iren.SetInteractorStyle(style);
    
    iren.Initialize();
    iren.Start();
   }
}
