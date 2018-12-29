import vtk.vtkImageCanvasSource2D;
import vtk.vtkJPEGWriter;
import vtk.vtkNamedColors;
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
	  vtkNamedColors colors = new vtkNamedColors();
	  
	  double bkgColor[] = new double[] {255, 0,0,1};
	  double boxColor[] = new double[] {255,255,0,1};
	  
	  colors.SetColor("bkgColor", bkgColor);
	  colors.SetColor("boxColor", boxColor);
	  
	  
	// Provide default values.
	String file_Name = "Output.jpg";
	String File_Argument ="";
	for(int i = 0; i < args.length; ++i)
	{
	      switch (i) 
	      {
	        case 0:
	        		file_Name = args[i];
	        		break;
	        case 1:
	        		File_Argument = args[i];
	        		break;
	      }
	}


    vtkImageCanvasSource2D ImageSource = new vtkImageCanvasSource2D();
    ImageSource.SetExtent(0, 99, 0, 99, 0, 0);
    
    //vtkJPEGWriter only accepts unsigned char input
    ImageSource.SetScalarTypeToUnsignedChar();
    
    //3 color channels: Red, Green and Blue
    ImageSource.SetNumberOfScalarComponents(3);

    //Fill the whole image with a blue background
    ImageSource.SetDrawColor(bkgColor);
    ImageSource.FillBox(0, 99, 0, 99);

    //Paint a 30x30 white square into the image
    ImageSource.SetDrawColor(boxColor);
    ImageSource.FillBox(40, 70, 20, 50);

    vtkJPEGWriter Writer = new vtkJPEGWriter();
    Writer.SetFileName(file_Name);
    Writer.SetInputConnection(ImageSource.GetOutputPort());
    Writer.Write();

  }
}
