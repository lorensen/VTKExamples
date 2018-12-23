import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkMath;
import vtk.vtkUnsignedCharArray;
import vtk.vtkPlaneSource;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;


public class ColorCellsWithRGB  
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
	  
  public static void main(String s[]) 
  {
    vtkNamedColors Color = new vtkNamedColors(); 
    //Renderer Background Color
    double BgColor[] = new double[4];
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("DarkGray",BgColor);

    // Provide some geometry
    int resolutionX = 5;
    int resolutionY = 3;
			   
    vtkPlaneSource aPlane = new vtkPlaneSource();
    aPlane.SetXResolution(resolutionX);
    aPlane.SetYResolution(resolutionY);
    aPlane.Update();
			   
    // Create cell data  
    vtkMath RS = new vtkMath();
    RS.RandomSeed(8775070);
			  
    vtkUnsignedCharArray CellData = new vtkUnsignedCharArray();
    CellData.SetNumberOfComponents(3);
    CellData.SetNumberOfTuples(aPlane.GetOutput().GetNumberOfCells());
		    
    for(int i=0;i<aPlane.GetOutput().GetNumberOfCells();i++)
    {
      double rgb[] = new double[3];
      rgb[0] = RS.Random(64, 255);
      rgb[1] = RS.Random(64, 255);
      rgb[2] = RS.Random(64, 255);
      CellData.InsertTuple3(i, rgb[0], rgb[1],rgb[2]);
				  
    }
		    
    aPlane.GetOutput().GetCellData().SetScalars(CellData);
			  

    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(aPlane.GetOutputPort());
			  
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
			  
			  
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
				    
    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(BgColor);
    ren.ResetCamera();
			      
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
} 
