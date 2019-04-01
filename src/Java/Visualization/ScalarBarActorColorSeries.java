import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkFloatArray;
import vtk.vtkPolyData;
import vtk.vtkScalarBarActor;
import vtk.vtkLookupTable;
import vtk.vtkColorSeries;

   
public class ScalarBarActorColorSeries 
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

    //For Background  Color
    double Bgcolor[] = new double[4];
    //Renderer Background2 Color
    double Bgcolor2[] = new double[4];

    colors.GetColor("Crimson", Bgcolor);
    colors.GetColor("NavajoWhite", Bgcolor2);
    
    // Create a sphere for some geometry
    vtkSphereSource sphere = new vtkSphereSource();
    sphere.SetCenter(0,0,0);
    sphere.SetRadius(1);
    sphere.SetPhiResolution(30);
    sphere.SetThetaResolution(60);
    sphere.Update();

    // Create scalar data to associate with the vertices of the sphere
    int numPts = sphere.GetOutput().GetPoints().GetNumberOfPoints();
    vtkFloatArray scalars = new vtkFloatArray();
    scalars.SetNumberOfValues( numPts );
    for( int i = 0; i < numPts; ++i )
    {
      scalars.SetValue(i,(float)(i)/numPts);
    }
	        
    vtkPolyData poly = new vtkPolyData();
    poly.DeepCopy(sphere.GetOutput());
    poly.GetPointData().SetScalars(scalars);
    
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputData(poly);
    mapper.ScalarVisibilityOn();
    mapper.SetScalarModeToUsePointData();
    mapper.SetColorModeToMapScalars();
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetInterpolationToFlat();
    
    vtkScalarBarActor scalarBar = new vtkScalarBarActor();
    scalarBar.SetLookupTable(mapper.GetLookupTable());
    scalarBar.SetTitle("Beachball");
    scalarBar.SetNumberOfLabels(4);
    
    // Create a lookup table to share between the mapper and the scalarbar
    vtkLookupTable seriesLut = new vtkLookupTable();
    
    vtkColorSeries series = new vtkColorSeries();
    int seriesEnum = 16;
    series.SetColorScheme(seriesEnum);
    series.BuildLookupTable(seriesLut, 0);
    
    mapper.SetLookupTable(seriesLut);
    scalarBar.SetLookupTable(seriesLut);
   
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.GradientBackgroundOn();
    ren.AddActor(actor);
    ren.AddActor2D(scalarBar);
    ren.SetBackground(Bgcolor);
    ren.SetBackground2(Bgcolor2);
    
    renWin.SetSize(300, 300);
    renWin.Render();
	
    iren.Initialize();
    iren.Start();
  }
}
