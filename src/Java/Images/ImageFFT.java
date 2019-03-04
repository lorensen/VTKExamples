import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;
import vtk.vtkImageEllipsoidSource;
import vtk.vtkImageFFT;
import vtk.vtkImageCast;
import vtk.vtkImageActor;
import vtk.vtkInteractorStyleImage;

public class ImageFFT
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

    double OriginalRendererBgColor[] = new double[] {.4, .5, .6, 1};
    Color.SetColor("OriginalRendererBgColor",OriginalRendererBgColor);
    
    double fftRendererBgColor[] = new double[] {.4, .5, .7, 1};
    Color.SetColor("fftRendererBgColor",fftRendererBgColor);
    
    //Create an image
    vtkImageEllipsoidSource source = new vtkImageEllipsoidSource();
    source.SetWholeExtent(0, 20, 0, 20, 0, 0);
    source.SetCenter(10,10,0);
    source.SetRadius(3,4,0);
    source.Update();

    vtkImageFFT fftFilter = new vtkImageFFT();
    fftFilter.SetInputConnection(source.GetOutputPort());
    fftFilter.Update();
    
    vtkImageCast fftCastFilter = new vtkImageCast();
    fftCastFilter.SetInputConnection(fftFilter.GetOutputPort());
    fftCastFilter.SetOutputScalarTypeToUnsignedChar();
    fftCastFilter.Update();

    //Create actors
    vtkImageActor originalActor = new vtkImageActor();
    originalActor.GetMapper().SetInputConnection(source.GetOutputPort());

    vtkImageActor fftActor = new vtkImageActor();
    fftActor.GetMapper().SetInputConnection(fftCastFilter.GetOutputPort());

    //Define viewport ranges
    //(xmin, ymin, xmax, ymax)
    double originalViewport[]= new double[] {0.0, 0.0, 0.5, 1.0};
    double fftViewport[] = new double[] {0.5, 0.0, 1.0, 1.0};
    
    //Setup renderers
    vtkRenderer originalRenderer = new vtkRenderer();
    originalRenderer.SetViewport(originalViewport);
    originalRenderer.AddActor(originalActor);
    originalRenderer.ResetCamera();
    originalRenderer.SetBackground(OriginalRendererBgColor);

    vtkRenderer fftRenderer = new vtkRenderer();
    fftRenderer.SetViewport(fftViewport);
    fftRenderer.AddActor(fftActor);
    fftRenderer.ResetCamera();
    fftRenderer.SetBackground(fftRendererBgColor);

    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.SetSize(600, 300);
    renderWindow.AddRenderer(originalRenderer);
    renderWindow.AddRenderer(fftRenderer);

    vtkRenderWindowInteractor renderWindowInteractor = new vtkRenderWindowInteractor();
    vtkInteractorStyleImage style = new vtkInteractorStyleImage();

    renderWindowInteractor.SetInteractorStyle(style);

    renderWindowInteractor.SetRenderWindow(renderWindow);
    renderWindow.Render();
    renderWindowInteractor.Initialize();

    renderWindowInteractor.Start();

  }
}
