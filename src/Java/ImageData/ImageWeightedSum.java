import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;
import vtk.vtkImageCast;
import vtk.vtkImageMandelbrotSource;
import vtk.vtkImageSinusoidSource;
import vtk.vtkImageWeightedSum;
import vtk.vtkImageActor;

public class ImageWeightedSum 
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
 
    double bkgL[] = new double[4] ;
    double bkgC[] = new double[4] ;
    double bkgR[] = new double [4] ;
         
    Color.GetColor("Tan",bkgL);
    Color.GetColor("DarkCyan",bkgC);
    Color.GetColor("LightSlateGray",bkgR);
    
    //create an image
    vtkImageMandelbrotSource source1 = new vtkImageMandelbrotSource();
    source1.SetWholeExtent(0, 255, 0, 255, 0, 0);
    source1.Update();

    vtkImageCast source1Double = new vtkImageCast();
    source1Double.SetInputConnection(0, source1.GetOutputPort());
    source1Double.SetOutputScalarTypeToDouble();

    vtkImageSinusoidSource source2 = new vtkImageSinusoidSource();
    source2.SetWholeExtent(0, 255, 0, 255, 0, 0);
    source2.Update();
    
    vtkImageWeightedSum sumFilter = new vtkImageWeightedSum();
    sumFilter.SetWeight(0, .8);
    sumFilter.SetWeight(1, .2);
    sumFilter.AddInputConnection(source1Double.GetOutputPort());
    sumFilter.AddInputConnection(source2.GetOutputPort());

    sumFilter.Update();

    vtkImageCast source1CastFilter = new vtkImageCast();
    source1CastFilter.SetInputConnection(source1.GetOutputPort());
    source1CastFilter.SetOutputScalarTypeToUnsignedChar();
    source1CastFilter.Update();

    vtkImageCast source2CastFilter = new vtkImageCast();
    source2CastFilter.SetInputConnection(source2.GetOutputPort());
    source2CastFilter.SetOutputScalarTypeToUnsignedChar();
    source2CastFilter.Update();

    vtkImageCast summedCastFilter = new vtkImageCast();
    summedCastFilter.SetInputConnection(sumFilter.GetOutputPort());
    summedCastFilter.SetOutputScalarTypeToUnsignedChar();
    summedCastFilter.Update();

    //Create actors
    vtkImageActor source1Actor = new vtkImageActor();
    source1Actor.GetMapper().SetInputConnection(source1CastFilter.GetOutputPort());

    vtkImageActor source2Actor = new vtkImageActor();
    source2Actor.GetMapper().SetInputConnection(source2CastFilter.GetOutputPort());

    vtkImageActor summedActor = new vtkImageActor();
    summedActor.GetMapper().SetInputConnection(summedCastFilter.GetOutputPort());
    
    // There will be one render window
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.SetSize(600, 300);

    // And one interactor
    vtkRenderWindowInteractor interactor = new vtkRenderWindowInteractor();
    interactor.SetRenderWindow(renderWindow);

    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double leftViewport[] = new double[] {0.0, 0.0, 0.33, 1.0};
    double centerViewport[] = new double[]{0.33, 0.0, .66, 1.0};
    double rightViewport[] = new double[] {0.66, 0.0, 1.0, 1.0};

    // Setup renderers
    vtkRenderer leftRenderer = new vtkRenderer();
    renderWindow.AddRenderer(leftRenderer);
    leftRenderer.SetViewport(leftViewport);
    leftRenderer.SetBackground(bkgL);

    vtkRenderer centerRenderer = new vtkRenderer();
    renderWindow.AddRenderer(centerRenderer);
    centerRenderer.SetViewport(centerViewport);
    centerRenderer.SetBackground(bkgC);

    vtkRenderer rightRenderer = new vtkRenderer();
    renderWindow.AddRenderer(rightRenderer);
    rightRenderer.SetViewport(rightViewport);
    rightRenderer.SetBackground(bkgR);

    leftRenderer.AddActor(source1Actor);
    centerRenderer.AddActor(source2Actor);
    rightRenderer.AddActor(summedActor);

    leftRenderer.ResetCamera();
    centerRenderer.ResetCamera();
    rightRenderer.ResetCamera();

    renderWindow.Render();
    interactor.Start();
  }
}
