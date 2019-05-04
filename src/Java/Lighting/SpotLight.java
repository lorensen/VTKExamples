import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPlaneSource;
import vtk.vtkLight;

public class SpotLight
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
    
    //For greenLight 
    double greenLightColor[] = new double[4];
    //For PinkLight 
    double pinkLightColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
    //Renderer Background1 Color
    double BgColor2[] = new double[4];
    
    //Change Color Name to Use your own Color 
    Color.GetColor("Lawn_green",greenLightColor);
    Color.GetColor("DeepPink",pinkLightColor);
    Color.GetColor("RoyalBlue",BgColor);
    Color.GetColor("SkyBlue",BgColor2);
	
    vtkPlaneSource PlaneSource = new vtkPlaneSource();
    PlaneSource.SetOrigin(-5.0, 0.0, 5.0);
    PlaneSource.SetPoint1(5.0, 0.0, 5.0);
    PlaneSource.SetPoint2(-5.0, 0.0, -5.0);
    PlaneSource.SetResolution(100, 100);
    
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(PlaneSource.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    
    vtkLight greenLight = new vtkLight();
    greenLight.PositionalOn();
    greenLight.SetPosition(-4.0, 4.0, -1.0);
    greenLight.SetColor(greenLightColor);
    greenLight.SetIntensity(0.5);

    vtkLight pinkLight = new vtkLight();
    pinkLight.PositionalOn();
    pinkLight.SetPosition(4.0, 5.0,1.0);
    pinkLight.SetColor(pinkLightColor);
    pinkLight.SetIntensity(0.6);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetSize(640, 480);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(Actor);
    
    // set camera view
    ren.ResetCamera();
    ren.GetActiveCamera().Azimuth(40.0);
    ren.GetActiveCamera().Elevation(30.0);
    
    // add lights to the renderer
    ren.AddLight(pinkLight);
    ren.AddLight(greenLight);
	
    ren.SetBackground(BgColor);
    ren.SetBackground2(BgColor2);
    ren.GradientBackgroundOn();
    
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
