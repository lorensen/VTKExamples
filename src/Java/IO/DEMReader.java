import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkDEMReader;
import vtk.vtkLookupTable;
import vtk.vtkImageMapToColors;
import vtk.vtkImageActor;
import vtk.vtkInteractorStyleImage;

public class DEMReader 
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
      System.err.println("Usage: java -classpath ... Filename(.dem) e.g SainteHelens.dem");
      return;
    }
    String inputFilename = args[0];
    
    //Read the file
    vtkDEMReader reader = new vtkDEMReader();
    reader.SetFileName(inputFilename);
    reader.Update();
    
    vtkLookupTable lut = new vtkLookupTable();
    lut.SetHueRange(0.6, 0);
    lut.SetSaturationRange(1.0, 0);
    lut.SetValueRange(0.5, 1.0);
    lut.SetTableRange(reader.GetOutput().GetScalarRange());
    
    //Visualize
    vtkImageMapToColors mapColors = new vtkImageMapToColors();
    mapColors.SetLookupTable(lut);
    mapColors.SetInputConnection(reader.GetOutputPort());
    
    //Create an actor
    vtkImageActor actor = new vtkImageActor();
    actor.GetMapper().SetInputConnection(mapColors.GetOutputPort());
    
    //Setup renderer
    vtkRenderer renderer = new vtkRenderer();
    renderer.AddActor(actor);
    renderer.ResetCamera();
    
    //Setup render window
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);
    
    //Setup render window interactor
    vtkRenderWindowInteractor renderWindowInteractor = new vtkRenderWindowInteractor();
    vtkInteractorStyleImage style = new vtkInteractorStyleImage();
    
    renderWindowInteractor.SetInteractorStyle(style);
    
    //Render and start interaction
    renderWindowInteractor.SetRenderWindow(renderWindow);
    renderWindow.Render();

    renderWindowInteractor.Initialize();
    renderWindowInteractor.Start();

  }
}
