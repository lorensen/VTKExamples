import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkMath;
import vtk.vtkCellArray;
import vtk.vtkRibbonFilter;
import vtk.vtkNamedColors;

public class RibbonFilter 
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
   	   	//For Line Actor Color
   	   	double LineActorColor[] = new double[4];
   	  	 //Renderer Background Color
   	   	double BgColor[] = new double[4];
   	   
   	   
   	   	//Change Color Name to Use your own Color for Change Actor Color
   	   	Color.GetColor("Sienna",LineActorColor);
   	   	//Change Color Name to Use your own Color for Renderer Background
   	   	Color.GetColor("SteelBlue",BgColor);
   	   
   	   	// No. of vertices
   	   	int nV = 256;      
   	   	double vX, vY, vZ;
   	   	// Spiral radius
   	   	double rS = 2;  
   	   	// No. of spiral cycles
   	   	int nCyc = 3;    
   	   	// Height
   	   	double h = 10;              

   	   	int i;

   	  	// Create points and cells for a spiral
   	   	vtkPoints Points = new vtkPoints();
   	   	vtkMath findPI = new vtkMath(); 
   	   	for(i = 0; i < nV; i++)
   	   	{
		     // Spiral coordinates
		     vX = rS * Math.cos(2 * findPI.Pi()* nCyc * i / (nV - 1));
		     vY = rS * Math.sin(2 * findPI.Pi() * nCyc * i / (nV - 1));
		     vZ = h * i / nV;
		     Points.InsertPoint(i, vX, vY, vZ);
   	   	}
   			  
   	  	vtkCellArray Lines = new vtkCellArray();
   	  	Lines.InsertNextCell(nV);
   	  	for (i = 0; i < nV; i++)
   	  	{
   		  Lines.InsertCellPoint(i);
   	  	}
   	  
   	  
   	  	vtkPolyData PolyData = new vtkPolyData();
   	  	PolyData.SetPoints(Points);
   	  	PolyData.SetLines(Lines);
   	  
   	  	// Create a mapper and actor
   	  	vtkPolyDataMapper LineMapper = new vtkPolyDataMapper();
   	  	LineMapper.SetInputData(PolyData);
   	  
   	  
   	  	vtkActor LineActor = new vtkActor();
   	  	LineActor.SetMapper(LineMapper);
   	  	LineActor.GetProperty().SetColor(LineActorColor);
   	  	LineActor.GetProperty().SetLineWidth(3);
   	  
   	  	// Create a ribbon around the line
   	  	vtkRibbonFilter RibbonFilter = new vtkRibbonFilter();
   	  	RibbonFilter.SetInputData(PolyData);
   	  	RibbonFilter.SetWidth(0.4);
   	  
   	  	// Create a mapper and actor for Ribbon
   	  	vtkPolyDataMapper RibbonMapper = new vtkPolyDataMapper();
   	  	RibbonMapper.SetInputConnection(RibbonFilter.GetOutputPort());
   			  
   	  
   	  	vtkActor RibbonActor = new vtkActor();
   	  	RibbonActor.SetMapper(RibbonMapper);
   	  
	  	// Create the renderer, render window and interactor.
      		vtkRenderer ren = new vtkRenderer();
     		vtkRenderWindow renWin = new vtkRenderWindow();
     		renWin.AddRenderer(ren);
      		vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
      		iren.SetRenderWindow(renWin);
      
      
      		// Visualise the arrow
      		ren.AddActor(LineActor);
      		ren.AddActor(RibbonActor);
      		ren.SetBackground(BgColor);
      		ren.GetActiveCamera().Azimuth(40);
      		ren.GetActiveCamera().Elevation(30);
      		ren.ResetCamera();
      		ren.ResetCameraClippingRange();
      
     		renWin.SetSize(300,300);
      		renWin.Render();

      		iren.Initialize();
      		iren.Start();

	  }
} 
