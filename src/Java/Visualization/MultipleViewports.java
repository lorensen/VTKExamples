import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;

public class MultipleViewports 
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

    //For Actor Color
    double actorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Tomato", actorColor);
    colors.GetColor("DarkSeaGreen", Bgcolor);
    
    //  Define viewport ranges
    double xmins[] = new double[] {0,.5,0,.5};
    double xmaxs[] = new double[] {0.5,1,0.5,1};
    double ymins[] = new double[] {0,0,.5,.5};
    double ymaxs[] = new double[] {0.5,0.5,1,1};

    vtkRenderWindow renWin = new vtkRenderWindow();
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    for(int i = 0; i < 4; i++)
    {
     vtkRenderer ren = new vtkRenderer();
     renWin.AddRenderer(ren);
     ren.SetViewport(xmins[i],ymins[i],xmaxs[i],ymaxs[i]);
     
     // Create a sphere
     vtkSphereSource sphereSource = new vtkSphereSource();
     sphereSource.SetCenter(0.0, 0.0, 0.0);
     phereSource.SetRadius(5);
     sphereSource.Update();
     
     // Create a mapper and actor
     vtkPolyDataMapper mapper = new vtkPolyDataMapper();
     mapper.SetInputConnection(sphereSource.GetOutputPort());
     vtkActor actor = new vtkActor();
     actor.SetMapper(mapper);
     ren.AddActor(actor);
     ren.ResetCamera();
     
     renWin.Render();
     renWin.SetWindowName("Multiple ViewPorts");
    }    

    iren.Initialize();
    iren.Start();
  }
}
