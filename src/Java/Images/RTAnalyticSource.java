import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageActor;
import vtk.vtkRTAnalyticSource;
import vtk.vtkInteractorStyleImage;

public class RTAnalyticSource 
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
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("DarkRed", Bgcolor);

    vtkRTAnalyticSource AnalyticSource = new vtkRTAnalyticSource();
    AnalyticSource.SetWholeExtent(-10, 10, -10, 10, 0, 0);

    vtkImageActor ImageActor = new vtkImageActor();
    ImageActor.GetMapper().SetInputConnection(AnalyticSource.GetOutputPort());

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    vtkInteractorStyleImage Style = new vtkInteractorStyleImage();
    iren.SetInteractorStyle(Style);

    // Visualize Actor
    ren.AddActor(ImageActor);
    ren.SetBackground(Bgcolor);
    ren.ResetCamera();

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
