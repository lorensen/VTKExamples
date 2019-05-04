import vtk.vtkActor;
import vtk.vtkInteractorStyleTrackballActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;

public class MoveActor
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

    colors.GetColor("White", Bgcolor);
    
    //Sphere1
    vtkSphereSource sphereSource1 = new vtkSphereSource();
    sphereSource1.SetCenter(0.0, 0.0, 0.0 );
    sphereSource1.SetRadius(4.0);
    sphereSource1.Update();
    
    vtkPolyDataMapper sphereMapper1  = new vtkPolyDataMapper();
    sphereMapper1 .SetInputData (sphereSource1.GetOutput());
    
    vtkActor sphereActor1 = new vtkActor();
    sphereActor1.SetMapper(sphereMapper1);
    
    //Sphere2
    vtkSphereSource sphereSource2 = new vtkSphereSource();
    sphereSource2.SetCenter(10.0, 0.0, 0.0 );
    sphereSource2.SetRadius(3.0);
    sphereSource2.Update();
    
    vtkPolyDataMapper sphereMapper2  = new vtkPolyDataMapper();
    sphereMapper2 .SetInputData (sphereSource2.GetOutput());
    
    vtkActor sphereActor2 = new vtkActor();
    sphereActor2.SetMapper(sphereMapper2);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(sphereActor1);
    ren.AddActor(sphereActor2);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(640, 480);
    renWin.Render();
    
    vtkInteractorStyleTrackballActor style = new vtkInteractorStyleTrackballActor();
    iren.SetInteractorStyle(style);
    
    iren.Initialize();
    iren.Start();
  }
}
