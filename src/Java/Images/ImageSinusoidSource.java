import vtk.vtkNativeLibrary;
import vtk.vtkImageSinusoidSource;
import vtk.vtkImageViewer2;
import vtk.vtkRenderWindowInteractor;

public class ImageSinusoidSource 
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
  
  vtkImageSinusoidSource sinusoidSource = new vtkImageSinusoidSource();
  sinusoidSource.Update();

  //Visualize
  vtkImageViewer2 imageViewer = new vtkImageViewer2();
  imageViewer.SetInputConnection(sinusoidSource.GetOutputPort());
  imageViewer.GetRenderWindow().SetSize( 500, 500 );
  imageViewer.GetRenderer().ResetCamera();

  vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
  imageViewer.GetRenderWindow().SetInteractor(iren);
  iren.SetInteractorStyle(null);
  imageViewer.Render();

  iren.Initialize();
  iren.Start();

 }
}
