import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkStructuredPointsReader;
import vtk.vtkHedgeHog;
import vtk.vtkLookupTable;
import vtk.vtkOutlineFilter;


public class ComplexV 
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
    //parse command line arguments
    if (args.length != 1) 
    {
      System.err.println("Usage: java -classpath ... Filename(.vtk) e.g carotid.vtk");
      return;
    }
    String inputFilename = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();

    //For outline Actor Color
    double outlineactorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Black", outlineactorColor);
    colors.GetColor("Gray", Bgcolor);
    
    vtkStructuredPointsReader reader = new vtkStructuredPointsReader();
    reader.SetFileName(inputFilename);
    
    vtkHedgeHog hhog = new vtkHedgeHog();
    hhog.SetInputConnection(reader.GetOutputPort());
    hhog.SetScaleFactor(0.3);
    
    vtkLookupTable lut = new vtkLookupTable();
    // lut.SetHueRange(.667, 0.0);
    lut.Build();
        
    vtkPolyDataMapper hhogMapper = new vtkPolyDataMapper();
    hhogMapper.SetInputConnection(hhog.GetOutputPort());
    hhogMapper.SetScalarRange(50, 550);
    hhogMapper.SetLookupTable(lut);
    
    vtkActor hhogActor = new vtkActor();
    hhogActor.SetMapper(hhogMapper);
    
    vtkOutlineFilter outline = new vtkOutlineFilter();
    outline.SetInputConnection(reader.GetOutputPort());
    
    vtkPolyDataMapper outlineMapper = new vtkPolyDataMapper();
    outlineMapper.SetInputConnection(outline.GetOutputPort());
    
    vtkActor outlineActor = new vtkActor();
    outlineActor.SetMapper(outlineMapper);
    outlineActor.GetProperty().SetColor(outlineactorColor);
    	 
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(outlineActor);
    ren.AddActor(hhogActor);
	
    ren.SetBackground(Bgcolor);
    
    ren.GetActiveCamera().SetFocalPoint(0,0,0);
    ren.GetActiveCamera().SetPosition(1,0,0);
    ren.GetActiveCamera().SetViewUp(0,0,1);
    ren.ResetCamera();

    ren.GetActiveCamera().Azimuth(60);
    ren.GetActiveCamera().Elevation(30);
    ren.GetActiveCamera().Dolly(1.1);
    ren.ResetCameraClippingRange();
    
    renWin.SetSize(300, 300);
    renWin.Render();
        
    iren.Initialize();
    iren.Start();
  }
}
