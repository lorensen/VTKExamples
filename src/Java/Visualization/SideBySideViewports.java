import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkCubeSource;

public class SideBySideViewports 
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

    //leftRenderer Background Color
    double leftRenderercolor[] = new double[4];
    //rightRenderer Background Color
    double rightRenderercolor[] = new double[4];

    colors.GetColor("Tan", leftRenderercolor);
    colors.GetColor("LightSlateGray", rightRenderercolor);
    
    // Setup sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.Update();
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(sphereSource.GetOutputPort());
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);

    // Setup cube
    vtkCubeSource cubeSource = new vtkCubeSource();
    cubeSource.Update();
    vtkPolyDataMapper cubeMapper = new vtkPolyDataMapper();
    cubeMapper.SetInputConnection(cubeSource.GetOutputPort());
    vtkActor cubeActor = new vtkActor();
    cubeActor.SetMapper(cubeMapper);
    cubeActor.GetProperty().SetDiffuseColor(.3, .6, .4);
	  
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double leftViewport[] = new double[] {0.0, 0.0, 0.5, 1.0};
    double rightViewport[] = new double[] {0.5, 0.0, 1.0, 1.0};
    
    // Setup both renderers
    vtkRenderer leftRenderer = new vtkRenderer();
    renWin.AddRenderer(leftRenderer);
    leftRenderer.SetViewport(leftViewport);
    leftRenderer.SetBackground(leftRenderercolor);  
    
    vtkRenderer rightRenderer = new vtkRenderer();
    renWin.AddRenderer(rightRenderer);
    rightRenderer.SetViewport(rightViewport);
    rightRenderer.SetBackground(rightRenderercolor);  
    
    // Add the sphere to the left and the cube to the right
    leftRenderer.AddActor(sphereActor);
    rightRenderer.AddActor(cubeActor);
    
    leftRenderer.ResetCamera();

    rightRenderer.ResetCamera();
    rightRenderer.GetActiveCamera().Azimuth(30);
    rightRenderer.GetActiveCamera().Elevation(30);
    
    renWin.SetSize(600, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
