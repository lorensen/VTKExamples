import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkSphereSource;
import vtk.vtkArrowSource;
import vtk.vtkBrownianPoints;
import vtk.vtkGlyph3D;
import vtk.vtkMath;

public class BrownianPoints 
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
    vtkNamedColors Color = new vtkNamedColors(); 

    //For Actor Color
    double glyphActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
         
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Banana",glyphActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("SlateGray",BgColor);
    
    //Create a sphere
    vtkSphereSource sphereSource = new vtkSphereSource();

    //Generate random vectors
    vtkMath math = new vtkMath(	);
    math.RandomSeed(5070); // for testing
    vtkBrownianPoints brownianPoints = new vtkBrownianPoints();
    brownianPoints.SetInputConnection(sphereSource.GetOutputPort());

    vtkArrowSource arrowSource = new vtkArrowSource();

    vtkGlyph3D glyph3D = new vtkGlyph3D();
    glyph3D.SetSourceConnection(arrowSource.GetOutputPort());
    glyph3D.SetInputConnection(brownianPoints.GetOutputPort());
    glyph3D.SetScaleFactor(.3);
    
    //Create a mapper and actor for sphere
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(sphereSource.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.GetProperty().EdgeVisibilityOn();
    actor.GetProperty().SetInterpolationToFlat();
    actor.SetMapper(mapper);

    //Create a mapper and actor for glyphs
    vtkPolyDataMapper glyphMapper = new vtkPolyDataMapper();
    glyphMapper.SetInputConnection(glyph3D.GetOutputPort());

    vtkActor glyphActor = new vtkActor();
    glyphActor.GetProperty().SetColor(glyphActorColor);
    glyphActor.SetMapper(glyphMapper);
                
    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(actor);
    ren.AddActor(glyphActor);
    
    ren.ResetCamera();
    ren.GetActiveCamera().Azimuth(30	);
    ren.GetActiveCamera().Elevation(30);
    ren.GetActiveCamera().Dolly(1.4);
    ren.ResetCameraClippingRange();
    ren.SetBackground(BgColor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
