import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPointSource;
import vtk.vtkDistanceToCamera;
import vtk.vtkArrowSource;
import vtk.vtkGlyph3D;
import vtk.vtkInteractorStyleTrackballCamera;
import vtk.vtkSphereSource;

public class DistanceToCamera 
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

    //For fixedActor Color
    double fixedActorColor[] = new double[4];
    //For sphereActor Color
    double sphereActorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Aqua", fixedActorColor);
    colors.GetColor("Yellow",sphereActorColor);
    colors.GetColor("White", Bgcolor);
    
    // Draw some arrows that maintain a fixed size during zooming.
    // Create a set of points.
    vtkPointSource fixedPointSource = new vtkPointSource();
    fixedPointSource.SetNumberOfPoints(2);
    
    // Calculate the distance to the camera of each point.
    vtkDistanceToCamera distanceToCamera = new vtkDistanceToCamera();
    distanceToCamera.SetInputConnection(fixedPointSource.GetOutputPort());
    distanceToCamera.SetScreenSize(100.0);
    
    // Glyph each point with an arrow.
    vtkArrowSource arrow = new vtkArrowSource();
    vtkGlyph3D fixedGlyph = new vtkGlyph3D();
    fixedGlyph.SetInputConnection(distanceToCamera.GetOutputPort());
    fixedGlyph.SetSourceConnection(arrow.GetOutputPort());
    
    // Scale each point.
    fixedGlyph.SetScaleModeToScaleByScalar();
    fixedGlyph.SetInputArrayToProcess(0, 0, 0, 0, "DistanceToCamera");
    
    // Create a mapper.
    vtkPolyDataMapper fixedMapper = new vtkPolyDataMapper();
    fixedMapper.SetInputConnection(fixedGlyph.GetOutputPort());
    fixedMapper.SetScalarVisibility(0);
    
    // Create an actor.
    vtkActor fixedActor = new vtkActor();
    fixedActor.SetMapper(fixedMapper);
    fixedActor.GetProperty().SetColor(fixedActorColor);
    
    // Draw some spheres that get bigger when zooming in.
    // Create a set of points.
    vtkPointSource pointSource = new vtkPointSource();
    pointSource.SetNumberOfPoints(4);
    
    // Glyph each point with a sphere.
    vtkSphereSource sphere = new vtkSphereSource();
    vtkGlyph3D glyph = new vtkGlyph3D();
    glyph.SetInputConnection(pointSource.GetOutputPort());
    glyph.SetSourceConnection(sphere.GetOutputPort());
    glyph.SetScaleFactor(0.1);
    
    // Create a mapper.
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(glyph.GetOutputPort());
    mapper.SetScalarVisibility(0);
    
    // Create an actor.
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetColor(sphereActorColor);
	    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    ren.SetBackground(Bgcolor);
    
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    
    // Give DistanceToCamera a pointer to the renderer.
    distanceToCamera.SetRenderer(ren);
    
    // Visualize
    ren.AddActor(fixedActor);
    ren.AddActor(actor);
	
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
        
    vtkInteractorStyleTrackballCamera style = new vtkInteractorStyleTrackballCamera();
    iren.SetInteractorStyle(style);
    iren.SetRenderWindow(renWin);

    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
