import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkStructuredGrid;
import vtk.vtkPoints;
import vtk.vtkDataSetMapper;

public class BlankPoint {
	
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
		
	    vtkNamedColors colors = new vtkNamedColors();

	    //Renderer Background Color
	    double Bgcolor[] = new double[4];

	    colors.GetColor("Seagreen", Bgcolor);
	    
	    // Create a grid
	    vtkStructuredGrid structuredGrid = new vtkStructuredGrid();

	    vtkPoints points = new vtkPoints();
	    
	    int gridSize = 8;
	    int counter = 0;
	    // Create a 5x5 grid of points
	    for( int j = 0; j < gridSize; j++)
	    {
	      for( int i = 0; i < gridSize; i++)
	      {
	        if(i == 3 && j == 3) // Make one point higher than the rest
	        {
	          points.InsertNextPoint(i, j, 2);
	          System.out.println("The different point is number " + " " + counter );
	        }
	        else
	        {
	          points.InsertNextPoint(i, j, 0); // Make most of the points the same height
	        }
	        counter++;
	      }
	    }
	    
	    // Specify the dimensions of the grid
	    structuredGrid.SetDimensions(gridSize,gridSize,1);

	    structuredGrid.SetPoints(points);

	    structuredGrid.BlankPoint(27);
	    structuredGrid.Modified();

	    // Create a mapper and actor
	    vtkDataSetMapper gridMapper = new vtkDataSetMapper();
	    gridMapper.SetInputData(structuredGrid);

	    vtkActor gridActor = new vtkActor();
	    gridActor.SetMapper(gridMapper);
	    gridActor.GetProperty().EdgeVisibilityOn();
	    gridActor.GetProperty().SetEdgeColor(0,0,1);

		
	    // Create the renderer, render window and interactor.
	    vtkRenderer ren = new vtkRenderer();
	    vtkRenderWindow renWin = new vtkRenderWindow();
	    renWin.AddRenderer(ren);
	    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
	    iren.SetRenderWindow(renWin);
	    
	    // Visualise
	    ren.AddActor(gridActor);
		
	    ren.SetBackground(Bgcolor);
	    
	    renWin.SetSize(300, 300);
	    renWin.Render();

	    iren.Initialize();
	    iren.Start();
	  }

}
