import vtk.vtkImageCanvasSource2D;
import vtk.vtkNativeLibrary;
import vtk.vtkAVIWriter;

public class AVI 
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
  // ----------------------------------------------------------------
  
  public static void main(String args[]) 
  {

    vtkImageCanvasSource2D Source = new vtkImageCanvasSource2D();
    Source.SetScalarTypeToUnsignedChar();
    Source.SetNumberOfScalarComponents(3);
    Source.SetExtent(0, 100, 0, 100, 0, 0);

    vtkAVIWriter Writer = new vtkAVIWriter();
    Writer.SetInputConnection(Source.GetOutputPort());
    Writer.SetFileName("test.avi");
    Writer.Start();

    for(int i = 0; i < 100; i++)
    {
      
      Source.SetDrawColor(0, 0, 0, 1);
      Source.FillBox(0, 100, 0, 100);
      Source.SetDrawColor(255, 0, 0, 1);
      Source.FillBox(i, 20, 10, 20);
      Source.Update();
      Writer.Write();
      
    }
    Writer.End();
  }
}
