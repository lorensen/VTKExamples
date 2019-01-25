import vtk.vtkNativeLibrary;
import vtk.vtkImageCanvasSource2D;
import vtk.vtkOggTheoraWriter;
import vtk.vtkNamedColors;

    
public class OggTheora 
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
        System.err.println("Usage: java -classpath ... OggTheora Filename(.avi) e.g OggTheora.avi");
        return;
    }
    
    String fileName = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();

    double bkgcolor[] = new double[] {0, 0,0,1};
    double boxcolor[] = new double[] {255,0,0,1};

    colors.SetColor("bkgColor", bkgcolor);
    colors.SetColor("boxColor", boxcolor);

    vtkImageCanvasSource2D source = new vtkImageCanvasSource2D();
    source.SetScalarTypeToUnsignedChar();
    source.SetNumberOfScalarComponents(3);
    source.SetExtent(0, 100, 0, 100, 0, 0);

    vtkOggTheoraWriter writer = new vtkOggTheoraWriter();

    writer.SetInputConnection(source.GetOutputPort());
    writer.SetFileName(fileName);
    writer.Start();

    for(int i = 0; i < 100; i++)
    {
      source.SetDrawColor(bkgcolor); //black
      source.FillBox(0, 100, 0, 100); //clear image
        
      source.SetDrawColor(boxcolor); //red
      source.FillBox(i, 20, 10, 20);
        
      source.Update();
      writer.Write();
    }
    writer.End();
  }
}
