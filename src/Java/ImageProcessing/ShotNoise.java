import vtk.vtkNativeLibrary;
import vtk.vtkImageCanvasSource2D;
import vtk.vtkPNGWriter;

public class ShotNoise 
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
    //Provide default values.
    String fileName = "TestShotNoise.png";
    for(int i = 0; i < args.length; ++i)
    {
      switch (i) 
      {
        case 0:
                fileName = args[i];
                break;
      }
    }

    vtkImageCanvasSource2D ImageCanvas = new vtkImageCanvasSource2D();

    ImageCanvas.SetScalarTypeToUnsignedChar();

    ImageCanvas.SetExtent(1, 256, 1, 256, 0, 0);
    ImageCanvas.SetDrawColor(0);
    ImageCanvas.FillBox(1, 256, 1, 256);
    ImageCanvas.SetDrawColor(255);
    ImageCanvas.FillBox(30, 255, 30, 225);
    ImageCanvas.SetDrawColor(0);
    ImageCanvas.FillBox(60, 195, 60, 195);
    ImageCanvas.SetDrawColor(255);
    ImageCanvas.FillTube(100, 100, 154, 154, 40);
    ImageCanvas.SetDrawColor(0);
    ImageCanvas.DrawSegment(45, 45, 45, 210);
    ImageCanvas.DrawSegment(45, 210, 210, 210);
    ImageCanvas.DrawSegment(210, 210, 210, 45);
    ImageCanvas.DrawSegment(210, 45, 45, 45);
    ImageCanvas.DrawSegment(100, 150, 150, 100);
    ImageCanvas.DrawSegment(110, 160, 160, 110);
    ImageCanvas.DrawSegment(90, 140, 140, 90);
    ImageCanvas.DrawSegment(120, 170, 170, 120);
    ImageCanvas.DrawSegment(80, 130, 130, 80);
    ImageCanvas.Update();

    vtkPNGWriter Writer = new vtkPNGWriter();
    Writer.SetInputConnection(ImageCanvas.GetOutputPort());
    Writer.SetFileName(fileName);
    Writer.Write();
  }
}
