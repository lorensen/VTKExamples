import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkPNMReader;
import vtk.vtkImageViewer2;


public class ReadPNM 
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
      System.err.println("Usage: java -classpath ... Filename(.pnm) e.g Gourds.pnm");
      return;
    }
    String inputFilename = args[0];

    vtkPNMReader reader = new vtkPNMReader();
    reader.SetFileName(inputFilename);
    reader.Update();

    // Visualize
    vtkImageViewer2 imageViewer = new vtkImageViewer2();
    imageViewer.SetInputConnection(reader.GetOutputPort());
    vtkRenderWindowInteractor renderWindowInteractor =new vtkRenderWindowInteractor();
    imageViewer.SetupInteractor(renderWindowInteractor);
    imageViewer.Render();
    imageViewer.GetRenderer().ResetCamera();
    imageViewer.Render();

    renderWindowInteractor.Start();
    
   }
}
