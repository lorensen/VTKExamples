import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkLegendBoxActor;
import vtk.vtkCubeSource;
import vtk.vtkPolyData;


public class Legend 
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

    //For boxLegendColor
    double boxLegendColor[] = new double[4];
    //For ballLegendColor
    double ballLegendColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];
    //Renderer legend Background Color
    double legendBgcolor[] = new double[4];

    colors.GetColor("Tomato", boxLegendColor);
    colors.GetColor("banana", ballLegendColor);
    colors.GetColor("cyan", Bgcolor);
    colors.GetColor("warm_grey", legendBgcolor);
    
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0);
    sphereSource.SetRadius(5000.0);
    sphereSource.Update();
    
    vtkPolyData polydata = sphereSource.GetOutput();
    
    // Create a mapper
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputData(polydata);
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    vtkLegendBoxActor legend = new vtkLegendBoxActor();
    legend.SetNumberOfEntries(2);
    
    vtkCubeSource legendBox = new vtkCubeSource();
    legendBox.Update();
    legend.SetEntry(0, legendBox.GetOutput(), "Box", boxLegendColor);
    legend.SetEntry(1, sphereSource.GetOutput(), "Ball", ballLegendColor);
    
    // place legend in lower right
    legend.GetPositionCoordinate().SetCoordinateSystemToView();
    legend.GetPositionCoordinate().SetValue(.5, -1.0);
    
    legend.GetPosition2Coordinate().SetCoordinateSystemToView();
    legend.GetPosition2Coordinate().SetValue(1.0, -0.5);
    
    legend.UseBackgroundOn();
    legend.SetBackgroundColor(legendBgcolor);
	   
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(actor);
    ren.AddActor(legend);
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
