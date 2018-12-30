import vtk.vtkNativeLibrary;
import vtk.vtkSphereSource;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;


public class FullScreen 
{
  //-----------------------------------------------------------------
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
  //-----------------------------------------------------------------
		
 public static void main(String s[]) 
 {
   // Create a sphere
   vtkSphereSource SphereSource = new vtkSphereSource();
   SphereSource.Update();
	  	
   vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
   Mapper.SetInputConnection(SphereSource.GetOutputPort());
		
  vtkActor Actor = new vtkActor();
  Actor.SetMapper(Mapper);
		
  // Create the renderer, render window and interactor.
  vtkRenderer ren = new vtkRenderer();
  vtkRenderWindow renWin = new vtkRenderWindow();
  renWin.AddRenderer(ren);
  vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
  iren.SetRenderWindow(renWin);
	    
  // Visualise Sphere in full screen window
  ren.AddActor(Actor);
  renWin.Render();
  renWin.SetFullScreen(1);
  ren.ResetCamera();
  ren.ResetCameraClippingRange();

  iren.Initialize();
  iren.Start();
 }
}
