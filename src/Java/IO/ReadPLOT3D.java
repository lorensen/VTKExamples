import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkMultiBlockPLOT3DReader;
import vtk.vtkStructuredGridGeometryFilter;


public class ReadPLOT3D
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
    if (args.length != 2) 
    {
      System.err.println("Usage: java -classpath ... XYZFilename(.bin) QFileName(.bin) e.g combxyz.bin combq.bin");
      return;
    }
    String xyzFilename = args[0];
    String qFilename = args[1];
    
    vtkNamedColors Color = new vtkNamedColors(); 

    //Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Seagreen",BgColor);
    
    vtkMultiBlockPLOT3DReader reader = new vtkMultiBlockPLOT3DReader();
    reader.SetXYZFileName(xyzFilename);
    reader.SetQFileName(qFilename);
    reader.SetScalarFunctionNumber(100);
    reader.SetVectorFunctionNumber(202);
    reader.Update();

    vtkStructuredGridGeometryFilter geometryFilter = new vtkStructuredGridGeometryFilter();
    geometryFilter.SetInputData(reader.GetOutput().GetBlock(0));
    geometryFilter.Update();

    // Visualize
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(geometryFilter.GetOutputPort());
    mapper.ScalarVisibilityOff();
	
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    ren.AddActor(actor);
    ren.SetBackground(BgColor);

    renWin.SetSize(300,300);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();

  }
}
