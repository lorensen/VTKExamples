import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkSphereSource;
import vtk.vtkElevationFilter;

public class ColoredSphere 
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

     //Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("SlateGray",BgColor);
    
    //  Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    vtkSphereSource sphere = new vtkSphereSource();
    sphere.SetPhiResolution(12); 
    sphere.SetThetaResolution(12);

    vtkElevationFilter colorIt = new vtkElevationFilter();
    colorIt.SetInputConnection(sphere.GetOutputPort());
    colorIt.SetLowPoint(0,0,-1);
    colorIt.SetHighPoint(0,0,1);
   
    //Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(colorIt.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
           
    ren.AddActor(actor);
    ren.SetBackground(BgColor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
