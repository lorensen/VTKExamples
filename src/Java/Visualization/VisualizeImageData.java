import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkImageData;
import vtk.vtkDataSetMapper;

public class VisualizeImageData 
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

    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
 
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Gold",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("SpringGreen",BgColor);
    
    //  Create an image data
    vtkImageData imageData = new vtkImageData();

    // Specify the size of the image data
    imageData.SetDimensions(3,3,2);
    imageData.SetSpacing(1.0, 1.0, 1.0);
    imageData.SetOrigin(0.0, 0.0, 0.0);
    
    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputData(imageData);
   
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(actor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
