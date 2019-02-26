import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkPolyDataMapper;
import vtk.vtkCubeSource;
import vtk.vtkSphereSource;

public class Opacity 
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
   
    //Cube
    vtkCubeSource cubeSource = new vtkCubeSource();
    vtkPolyDataMapper cubeMapper = new vtkPolyDataMapper();
    cubeMapper.SetInputConnection(cubeSource.GetOutputPort());

    vtkActor cubeActor = new vtkActor();
    cubeActor.GetProperty().SetOpacity(0.5);
    cubeActor.SetMapper(cubeMapper);
    
    //Sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(sphereSource.GetOutputPort());

    vtkActor sphereActor =  new vtkActor();
    sphereActor.GetProperty().SetColor(0.5,1,0.5);
    sphereActor.GetProperty().SetOpacity(0.5);
    sphereActor.SetMapper(sphereMapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(cubeActor);
    ren.AddActor(sphereActor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
