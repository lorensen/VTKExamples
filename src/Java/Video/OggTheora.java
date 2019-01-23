import vtk.vtkNativeLibrary;
import vtk.vtkImageCanvasSource2D;
import vtk.vtkOggTheoraWriter;

    
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

    String fileName = "test.avi";
    for(int i = 0; i < args.length; ++i)
    {
      switch (i) 
      {
        case 0:
        fileName = args[i];
        break;
      }
    }

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
      source.SetDrawColor(0,0,0,1); //black
      source.FillBox(0, 100, 0, 100); //clear image
      source.SetDrawColor(255,0,0,1); //red
      source.FillBox(i, 20, 10, 20);
      source.Update();
      writer.Write();
    }
    writer.End();
  }
}
