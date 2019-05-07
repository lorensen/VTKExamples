import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageEllipsoidSource;
import vtk.vtkImagePermute;
import vtk.vtkImageActor;
import vtk.vtkInteractorStyleImage;


public class ImageOrientation 
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

    //For originalViewport Color
    double originalViewportColor[] = new double[4];
    //For permutedViewport Color
    double permutedViewportColor[] = new double[4];

    colors.GetColor("SlateGray", originalViewportColor);
    colors.GetColor("LightSteelBlue",permutedViewportColor);
    
    // Create an image
    vtkImageEllipsoidSource source = new vtkImageEllipsoidSource();
    source.SetWholeExtent(0, 20, 0, 20, 0, 0);
    source.SetCenter(10,10,0);
    source.SetRadius(2,5,0);
    source.Update();
    
    vtkImagePermute permuteFilter = new vtkImagePermute();
    permuteFilter.SetInputConnection(source.GetOutputPort());
    permuteFilter.SetFilteredAxes(1,0,2);
    permuteFilter.Update();
    
    // Create actors
    vtkImageActor originalActor = new vtkImageActor();
    originalActor.GetMapper().SetInputConnection(source.GetOutputPort());
    
    vtkImageActor permutedActor = new vtkImageActor();
    permutedActor.GetMapper().SetInputConnection(permuteFilter.GetOutputPort());
    
    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double originalViewport[] = new double[] {0.0, 0.0, 0.5, 1.0};
    double permutedViewport[] = new double[] {0.5, 0.0, 1.0, 1.0};
    
    // Setup renderers
    vtkRenderer originalRenderer = new vtkRenderer();
    originalRenderer.SetViewport(originalViewport);
    originalRenderer.AddActor(originalActor);
    originalRenderer.ResetCamera();
    originalRenderer.SetBackground(originalViewportColor);
    
    vtkRenderer permutedRenderer = new vtkRenderer();
    permutedRenderer.SetViewport(permutedViewport);
    permutedRenderer.AddActor(permutedActor);
    permutedRenderer.ResetCamera();
    permutedRenderer.SetBackground(permutedViewportColor);
    
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.SetSize(600, 300);
    renderWindow.AddRenderer(originalRenderer);
    renderWindow.AddRenderer(permutedRenderer);
    
    vtkRenderWindowInteractor renderWindowInteractor = new vtkRenderWindowInteractor();
    
    vtkInteractorStyleImage style =new vtkInteractorStyleImage();
    
    renderWindowInteractor.SetInteractorStyle(style);

    renderWindowInteractor.SetRenderWindow(renderWindow);
    renderWindow.Render();
    renderWindowInteractor.Initialize();

    renderWindowInteractor.Start();
  }
}
