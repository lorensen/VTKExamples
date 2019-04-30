import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderer;
import vtk.vtkConeSource;

public class ReportRenderWindowCapabilities 
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
   //Create a cone
   vtkConeSource coneSource = new vtkConeSource();
   coneSource.Update();
   
   //Create a mapper and actor
   vtkPolyDataMapper mapper = new vtkPolyDataMapper();
   mapper.SetInputConnection(coneSource.GetOutputPort());
   
   vtkActor actor = new vtkActor();
   actor.SetMapper(mapper);
   
   // Create the renderer, render window
   vtkRenderer ren = new vtkRenderer();
   vtkRenderWindow renWin = new vtkRenderWindow();
   renWin.AddRenderer(ren);
   
   ren.AddActor(actor);
   
   renWin.Render();
   
   System.out.println(renWin.ReportCapabilities());
  }
}
