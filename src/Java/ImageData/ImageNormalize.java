import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageSinusoidSource;
import vtk.vtkNamedColors;
import vtk.vtkImageNormalize;
import vtk.vtkImageCast;
import vtk.vtkImageActor;


public class ImageNormalize 
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
    
    double left_bkg[] = new double[]{0.6, 0.5, 0.4, 1.0};
    double right_bkg[] = new double[]{0.4, 0.5, 0.6, 1.0};
    
    colors.SetColor("bkgColor", left_bkg);
    colors.SetColor("boxColor", right_bkg);
    
    //  Create an image
    vtkImageSinusoidSource source = new vtkImageSinusoidSource();
    source.Update();

    vtkImageNormalize normalizeFilter = new vtkImageNormalize();

    normalizeFilter.SetInputConnection(source.GetOutputPort());
    normalizeFilter.Update();
    
    vtkImageCast inputCastFilter = new vtkImageCast();
    inputCastFilter.SetInputConnection(source.GetOutputPort());
    inputCastFilter.SetOutputScalarTypeToUnsignedChar();
    inputCastFilter.Update();

    vtkImageCast normalizeCastFilter = new vtkImageCast();
    normalizeCastFilter.SetInputConnection(normalizeFilter.GetOutputPort());
    normalizeCastFilter.SetOutputScalarTypeToUnsignedChar();
    normalizeCastFilter.Update();
    
    //  Create actors
    vtkImageActor inputActor = new vtkImageActor();
    inputActor.GetMapper().SetInputConnection(inputCastFilter.GetOutputPort());

    vtkImageActor normalizedActor = new vtkImageActor();
    normalizedActor.GetMapper().SetInputConnection(normalizeCastFilter.GetOutputPort());
    
    //  Create the render window and interactor.
    
    vtkRenderWindow renWin = new vtkRenderWindow();
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    //  Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double leftViewport[] = new double[] {0.0, 0.0, 0.5, 1.0};
    double rightViewport[] = new double[] {0.5, 0.0, 1.0, 1.0};
    
    
    //  Setup both renderers
    vtkRenderer leftRenderer = new vtkRenderer();
    renWin.AddRenderer(leftRenderer);
    leftRenderer.SetViewport(leftViewport);
    leftRenderer.SetBackground(left_bkg);

    vtkRenderer rightRenderer = new vtkRenderer();
    renWin.AddRenderer(rightRenderer);
    rightRenderer.SetViewport(rightViewport);
    rightRenderer.SetBackground(right_bkg);
    
    leftRenderer.AddActor(inputActor);
    rightRenderer.AddActor(normalizedActor);

    leftRenderer.ResetCamera();
    rightRenderer.ResetCamera();
    
    renWin.SetSize(600,300);
    renWin.Render();
   
    iren.Initialize();
    iren.Start();
  }
}
