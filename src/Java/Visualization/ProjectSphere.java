import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkProjectSphereFilter;
import vtk.vtkElevationFilter;
import vtk.vtkParametricSuperEllipsoid;
import vtk.vtkParametricFunctionSource;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;

public class ProjectSphere
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
    double leftRenderercolor[] = new double[4];
    double rightRenderercolor[] = new double[4];

    colors.GetColor("Tan", leftRenderercolor);
    colors.GetColor("LightSlateGray", rightRenderercolor);
    
    vtkParametricSuperEllipsoid surface = new vtkParametricSuperEllipsoid();
    surface.SetN1(2.0);
    surface.SetN2(0.5);
    
    vtkParametricFunctionSource source = new vtkParametricFunctionSource();
    source.SetParametricFunction(surface);
    
    vtkElevationFilter elevationFilter = new vtkElevationFilter();
    elevationFilter.SetInputConnection(source.GetOutputPort());
    elevationFilter.SetLowPoint(0.0, 0.0, -4.0);
    elevationFilter.SetHighPoint(0.0, 0.0, 4.0);
    elevationFilter.Update();
    
    // Deep copy the point data since in some versions of VTK, the ProjectSphereFilter modifies the input point data 
    vtkPolyData pd1 = new vtkPolyData();
    pd1.DeepCopy(elevationFilter.GetOutput());

    vtkProjectSphereFilter sphereProject1 = new vtkProjectSphereFilter();
    sphereProject1.SetInputConnection(elevationFilter.GetOutputPort());
    sphereProject1.Update();

    vtkPolyDataMapper mapper1 = new vtkPolyDataMapper();
    mapper1.SetInputConnection(sphereProject1.GetOutputPort());
    mapper1.SetScalarRange(sphereProject1.GetOutput().GetPointData().GetScalars().GetRange());
    
    vtkActor actor1 = new vtkActor();
    actor1.SetMapper(mapper1);

    vtkPolyDataMapper mapper2 = new vtkPolyDataMapper();
    mapper2.SetInputData(pd1);
    mapper2.SetScalarRange(pd1.GetPointData().GetScalars().GetRange());  
    
    vtkActor actor2 = new vtkActor();
    actor2.SetMapper(mapper2);
    	 
    // A render window
    vtkRenderWindow renderWindow = new vtkRenderWindow();

    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double leftViewport[] = new double[] {0.0, 0.0, 0.5, 1.0};
    double rightViewport[] = new double[] {0.5, 0.0, 1.0, 1.0};

    // Setup both renderers
    vtkRenderer leftRenderer = new vtkRenderer();
    renderWindow.AddRenderer(leftRenderer);
    leftRenderer.SetViewport(leftViewport);
    leftRenderer.SetBackground(.6, .5, .4);

    vtkRenderer rightRenderer = new vtkRenderer();
    renderWindow.AddRenderer(rightRenderer);
    rightRenderer.SetViewport(rightViewport);
    rightRenderer.SetBackground(.4, .5, .6);

    leftRenderer.AddActor(actor2);
    rightRenderer.AddActor(actor1);

    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renderWindow);
	
    leftRenderer.GetActiveCamera().Azimuth(30);
    leftRenderer.GetActiveCamera().Elevation(-30);
    leftRenderer.ResetCamera();
    
    renderWindow.SetSize(640, 480);
    renderWindow.Render();

    iren.Initialize();
    iren.Start();
  }
}
