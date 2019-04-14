import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSuperquadricSource;
import vtk.vtkCubeAxesActor;

public class CubeAxesActor 
{
  private static final int VTK_GRID_LINES_FURTHEST = 2;
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

    //For Actor Color
    double actorColor[] = new double[4];
    //For axis1 Color
    double axis1Color[] = new double[4];
    //For axis2 Color
    double axis2Color[] = new double[4];
    //For axis3 Color
    double axis3Color[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Tomato", actorColor);
    colors.GetColor("Salmon", axis1Color);
    colors.GetColor("PaleGreen", axis2Color);
    colors.GetColor("DodgerBlue", axis3Color);
    colors.GetColor("Indigo", Bgcolor);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
        
    //  Create a superquadric
    vtkSuperquadricSource superquadricSource = new vtkSuperquadricSource();
    superquadricSource.SetPhiRoundness(3.1);
    superquadricSource.SetThetaRoundness(1.0);
    superquadricSource.Update(); // needed to GetBounds later
    
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(superquadricSource.GetOutputPort());
    
    vtkActor superquadricActor = new vtkActor();
    superquadricActor.SetMapper(mapper);
    superquadricActor.GetProperty().SetDiffuseColor(actorColor);
    superquadricActor.GetProperty().SetDiffuse(.7);
    superquadricActor.GetProperty().SetSpecular(.7);
    superquadricActor.GetProperty().SetSpecularPower(50.0);
    
    vtkCubeAxesActor cubeAxesActor = new vtkCubeAxesActor();
    cubeAxesActor.SetUseTextActor3D(1);
    cubeAxesActor.SetBounds(superquadricSource.GetOutput().GetBounds());
    cubeAxesActor.SetCamera(ren.GetActiveCamera());
    cubeAxesActor.GetTitleTextProperty(0).SetColor(axis1Color);
    cubeAxesActor.GetTitleTextProperty(0).SetFontSize(48);
    cubeAxesActor.GetLabelTextProperty(0).SetColor(axis1Color);
    
    cubeAxesActor.GetTitleTextProperty(1).SetColor(axis2Color);
    cubeAxesActor.GetLabelTextProperty(1).SetColor(axis2Color);
    cubeAxesActor.GetTitleTextProperty(2).SetColor(axis3Color);
    cubeAxesActor.GetLabelTextProperty(2).SetColor(axis3Color);
    
    cubeAxesActor.DrawXGridlinesOn();
    cubeAxesActor.DrawYGridlinesOn();
    cubeAxesActor.DrawZGridlinesOn();
    cubeAxesActor.SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
    
    cubeAxesActor.XAxisMinorTickVisibilityOff();
    cubeAxesActor.YAxisMinorTickVisibilityOff();
    cubeAxesActor.ZAxisMinorTickVisibilityOff();
    
    cubeAxesActor.SetFlyModeToStaticEdges();
    ren.AddActor(cubeAxesActor);
    ren.AddActor(superquadricActor);
    ren.GetActiveCamera().Azimuth(30);
    ren.GetActiveCamera().Elevation(30);

    ren.ResetCamera();
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(1200, 900);
    renWin.Render();
   
    iren.Initialize();
    iren.Start();
  }
}
