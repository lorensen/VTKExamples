import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkConeSource;

public class PickableOff
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

    //For coneActor0 Color
    double coneActor0Color[] = new double[4];
    //For coneActor1 Color
    double coneActor1Color[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Gold", coneActor0Color);
    colors.GetColor("Lime", coneActor1Color);
    colors.GetColor("DarkGray", Bgcolor);
    
    vtkConeSource ConeSource0 = new vtkConeSource();
    ConeSource0.Update();
    
    vtkConeSource ConeSource1 = new vtkConeSource();
    ConeSource1.SetCenter(5, 0, 0);
    ConeSource1.Update();
    
    vtkPolyDataMapper coneMapper0 = new vtkPolyDataMapper();
    coneMapper0.SetInputConnection(ConeSource0.GetOutputPort());
    
    vtkPolyDataMapper coneMapper1 = new vtkPolyDataMapper();
    coneMapper1.SetInputConnection(ConeSource1.GetOutputPort());
	
    vtkActor coneActor0 = new vtkActor();
    coneActor0.SetMapper(coneMapper0);
    coneActor0.GetProperty().SetColor(coneActor0Color);
	
    vtkActor coneActor1 = new vtkActor();
    coneActor1.SetMapper(coneMapper1);
    coneActor1.GetProperty().SetColor(coneActor1Color);
    coneActor1.PickableOff();
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(coneActor0);
    ren.AddActor(coneActor1);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
