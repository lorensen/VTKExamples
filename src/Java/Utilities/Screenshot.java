import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkPNGWriter;
import vtk.vtkWindowToImageFilter;

public class Screenshot 
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
      System.err.println("Usage: java -classpath ... Filename(.png) e.g screenshot.png");
      return;
    }
    String fileName = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("White", Bgcolor);
   
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0 );
    sphereSource.SetRadius(4.0);
    sphereSource.Update();
    
    vtkPolyDataMapper sphereMapper  = new vtkPolyDataMapper();
    sphereMapper.SetInputData (sphereSource.GetOutput());
    
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);
	
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetAlphaBitPlanes(1);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(sphereActor);
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();
    
    vtkWindowToImageFilter windowToImageFilter = new vtkWindowToImageFilter();
    windowToImageFilter.SetInput(renWin);
    windowToImageFilter.SetScale(2);
    windowToImageFilter.SetInputBufferTypeToRGB();

    windowToImageFilter.ReadFrontBufferOff();
    windowToImageFilter.Update();

    vtkPNGWriter writer = new vtkPNGWriter();
    writer.SetFileName(fileName);
    writer.SetInputConnection(windowToImageFilter.GetOutputPort());
    writer.Write();
    
    renWin.Render();
    ren.ResetCamera();
    renWin.Render();
    iren.Start();
  }
}
