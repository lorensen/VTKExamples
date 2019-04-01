import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkCone;
import vtk.vtkSampleFunction;
import vtk.vtkThreshold;
import vtk.vtkPointSource;
import vtk.vtkProbeFilter;
import vtk.vtkThresholdPoints;
import vtk.vtkGlyph3D;
import vtk.vtkDataSetMapper;
import vtk.vtkSphereSource;


public class RandomProbe
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
    int resolution = 50;
    
    //parse command line arguments
    if (args.length > 1) 
    {
      String res = args[0];
      resolution = Integer.parseInt(res);
    }
    
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];
    colors.GetColor("DeepSkyBlue", Bgcolor);
    
    // Create a sampled cone
    vtkCone implicitCone = new vtkCone();
    implicitCone.SetAngle(30.0);

    double radius = 1.0;
    vtkSampleFunction sampledCone = new vtkSampleFunction();
    sampledCone.SetSampleDimensions(resolution, resolution, resolution);
    double xMin = -radius * 2.0;
    double xMax =  radius * 2.0;
    sampledCone.SetModelBounds(xMin, xMax, xMin, xMax, xMin, xMax);
    sampledCone.SetImplicitFunction(implicitCone);
    
    vtkThreshold thresholdCone = new vtkThreshold();
    thresholdCone.SetInputConnection(sampledCone.GetOutputPort());
    thresholdCone.ThresholdByLower(0);
    
    vtkPointSource randomPoints = new vtkPointSource();
    randomPoints.SetCenter (0.0, 0.0, 0.0);
    randomPoints.SetNumberOfPoints(10000);
    randomPoints.SetDistributionToUniform();
    randomPoints.SetRadius(xMax);
    
    // Probe the cone dataset with random points
    vtkProbeFilter randomProbe = new vtkProbeFilter();
    randomProbe.SetInputConnection(0, randomPoints.GetOutputPort());
    randomProbe.SetInputConnection(1, thresholdCone.GetOutputPort());
    randomProbe.Update();
    randomProbe.GetOutput().GetPointData().SetActiveScalars("vtkValidPointMask");
    
    vtkThresholdPoints selectPoints = new vtkThresholdPoints();
    selectPoints.SetInputConnection(randomProbe.GetOutputPort());
    selectPoints.ThresholdByUpper(1.0);
    
    vtkSphereSource sphere =new vtkSphereSource();
    sphere.SetRadius(.05);
    
    vtkGlyph3D glyph = new vtkGlyph3D();
    glyph.SetSourceConnection(sphere.GetOutputPort());
    glyph.SetInputConnection(selectPoints.GetOutputPort());
    
    // Create a mapper and actor
    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputConnection(glyph.GetOutputPort());
    mapper.ScalarVisibilityOff();
    
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
