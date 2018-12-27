import vtk.vtkImageCanvasSource2D;
import vtk.vtkJPEGWriter;
import vtk.vtkNativeLibrary;

public class JPEGWriter 
{

  //-----------------------------------------------------------------
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

    vtkImageCanvasSource2D ImageSource = new vtkImageCanvasSource2D();
    ImageSource.SetExtent(0, 99, 0, 99, 0, 0);
    
    //vtkJPEGWriter only accepts unsigned char input
    ImageSource.SetScalarTypeToUnsignedChar();
    
    //3 color channels: Red, Green and Blue
    ImageSource.SetNumberOfScalarComponents(3);

    //Fill the whole image with a blue background
    ImageSource.SetDrawColor(0, 127, 255);
    ImageSource.FillBox(0, 99, 0, 99);

    //Paint a 30x30 white square into the image
    ImageSource.SetDrawColor(255, 255, 255);
    ImageSource.FillBox(40, 70, 20, 50);

    vtkJPEGWriter Writer = new vtkJPEGWriter();
    Writer.SetFileName("Output.jpg");
    Writer.SetInputConnection(ImageSource.GetOutputPort());
    Writer.Write();

  }
}
