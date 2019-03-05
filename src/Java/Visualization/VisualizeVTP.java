import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkXMLPolyDataReader;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;

public class VisualizeVTP 
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
    Color.GetColor("LightSlateGray",BgColor);
    
    //parse command line arguments
    if (args.length != 1) 
    {
      System.err.println("Usage: java -classpath ... Filename(.vtp) e.g Bunny.vtp");
      return;
    }
    
    //Read the polydata for the icon
    vtkXMLPolyDataReader reader =  new vtkXMLPolyDataReader();
    reader.SetFileName(args[0]);
       
    //Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(reader.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(actor);
    ren.SetBackground(BgColor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Start();

  }
}
