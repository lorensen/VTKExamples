import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkDataSetMapper;
import vtk.vtkPoints;
import vtk.vtkPyramid;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkUnstructuredGrid;
import vtk.vtkCellArray;
import vtk.vtkNamedColors;


public class Pyramid  
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
	  

  public static void main(String s[]) 
  {
    vtkNamedColors Color = new vtkNamedColors(); 
    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];


    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Sienna",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Ivory",BgColor);

    vtkPoints Points = new vtkPoints();

    double p0[] = new double[] {1.0,1.0,1.0};
    double p1[] = new double[] {-1.0,1.0,1.0};
    double p2[] = new double[] {-1.0,-1.0,1.0};
    double p3[] = new double[] {1.0,-1.0, 1.0};
    double p4[] = new double[] {0.0,0.0, 0.0};

    Points.InsertNextPoint(p0);
    Points.InsertNextPoint(p1);
    Points.InsertNextPoint(p2);
    Points.InsertNextPoint(p3);
    Points.InsertNextPoint(p4);


    vtkPyramid Pyramid = new vtkPyramid();
    Pyramid.GetPointIds().SetId(0, 0);
    Pyramid.GetPointIds().SetId(1, 1);
    Pyramid.GetPointIds().SetId(2, 2);
    Pyramid.GetPointIds().SetId(3, 3);
    Pyramid.GetPointIds().SetId(4, 4);

    vtkCellArray Cells = new vtkCellArray();
    Cells.InsertNextCell(Pyramid);

    vtkUnstructuredGrid UG = new vtkUnstructuredGrid();
    UG.SetPoints(Points);
    UG.InsertNextCell(Pyramid.GetCellType(), Pyramid.GetPointIds());

    vtkDataSetMapper Mapper = new vtkDataSetMapper();
    Mapper.SetInputData(UG);


    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().EdgeVisibilityOn();
    Actor.GetProperty().SetColor(ActorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(BgColor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
} 
