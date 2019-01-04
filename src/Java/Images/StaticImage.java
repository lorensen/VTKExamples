import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkImageReader2;
import vtk.vtkImageViewer2;
import vtk.vtkImageReader2Factory;

public class StaticImage 
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
    // Read the image (Pass the Image File Name as Argument)
    vtkImageReader2Factory ReaderFactory = new vtkImageReader2Factory();
    vtkImageReader2 Reader = ReaderFactory.CreateImageReader2(args[0]);
    Reader.SetFileName(args[0]);
    Reader.Update();
		
    // Visualize
    vtkImageViewer2 ImageViewer = new vtkImageViewer2();
    ImageViewer.SetInputConnection(Reader.GetOutputPort());
    ImageViewer.GetRenderWindow().SetSize(500, 500);
    ImageViewer.GetRenderer().ResetCamera();

    // Set up an interactor that does not respond to mouse events
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    ImageViewer.GetRenderWindow().SetInteractor(iren);
    iren.SetInteractorStyle(null);
    ImageViewer.Render();

    // Start the event loop
    iren.Initialize();
    iren.Start();

    Reader.Delete();
  }
}
