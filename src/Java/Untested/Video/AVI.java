import vtk.vtkImageCanvasSource2D;
import vtk.vtkNamedColors;
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
	vtkNamedColors colors = new vtkNamedColors();
	  
	double bkgColor[] = new double[] {0, 0,0,1};
	double boxColor[] = new double[] {255,0,0,1};
	  
	colors.SetColor("bkgColor", bkgColor);
	colors.SetColor("boxColor", boxColor);
	
	
	// Provide default values.
	String fileName = "Output.avi";
	for(int i = 0; i < args.length; ++i)
	{
		switch (i) 
		{
			case 0:
				fileName = args[i];
		        	break;

		}
	}
    vtkImageCanvasSource2D Source = new vtkImageCanvasSource2D();
    Source.SetScalarTypeToUnsignedChar();
    Source.SetNumberOfScalarComponents(3);
    Source.SetExtent(0, 100, 0, 100, 0, 0);

    vtkAVIWriter Writer = new vtkAVIWriter();
    Writer.SetInputConnection(Source.GetOutputPort());
    Writer.SetFileName(fileName);
    Writer.Start();

    for(int i = 0; i < 100; i++)
    {
      
      Source.SetDrawColor(bkgColor);
      Source.FillBox(0, 100, 0, 100);
      Source.SetDrawColor(boxColor);
      Source.FillBox(i, 20, 10, 20);
      Source.Update();
      Writer.Write();
      
    }
    Writer.End();
  }

}
