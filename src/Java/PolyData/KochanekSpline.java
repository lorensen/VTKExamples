import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPointSource;
import vtk.vtkPoints;
import vtk.vtkKochanekSpline;
import vtk.vtkParametricSpline;
import vtk.vtkParametricFunctionSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPolyData;
import vtk.vtkSphereSource;
import vtk.vtkGlyph3DMapper;

public class KochanekSpline  
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
		  
		    //For Actor Color
		    double ActorColor[] = new double[4];
		    //For Point Actor Color
		    double PointActorColor[] = new double[4];
		    //Renderer Background Color
		    double BgColor[] = new double[4];
		  
			   
		    //Change Color Name to Use your own Color for Change Actor Color
		    Color.GetColor("DarkSlateGrey",ActorColor);
		    //Change Color Name to Use your own Color for Change Outline Actor Color
		    Color.GetColor("Red",PointActorColor);
		    //Change Color Name to Use your own Color for Renderer Background
		    Color.GetColor("White",BgColor);

		    int numberOfPoints = 10;
		    vtkPointSource pointSource = new vtkPointSource();
		    pointSource.SetNumberOfPoints(numberOfPoints);
		    pointSource.Update();
		    
		    vtkPoints Points = pointSource.GetOutput().GetPoints();
		    
	    
		    vtkKochanekSpline xSpline = new vtkKochanekSpline();
		    vtkKochanekSpline ySpline = new vtkKochanekSpline();
		    vtkKochanekSpline zSpline = new vtkKochanekSpline();
		    
		    vtkParametricSpline spline = new vtkParametricSpline();
		    spline.SetXSpline(xSpline);
		    spline.SetYSpline(ySpline);
		    spline.SetZSpline(zSpline);
		    spline.SetPoints(Points);
		   	    	  
		    vtkParametricFunctionSource functionSource = new vtkParametricFunctionSource();
		    functionSource.SetParametricFunction(spline);
		    functionSource.SetUResolution(50*numberOfPoints);
		    functionSource.SetVResolution(50*numberOfPoints);
		    functionSource.SetWResolution(50*numberOfPoints);
		    functionSource.Update();
		    
		    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
		    Mapper.SetInputConnection(functionSource.GetOutputPort());


		    vtkActor Actor = new vtkActor();
		    Actor.SetMapper(Mapper);
		    Actor.GetProperty().SetColor(ActorColor);
		    Actor.GetProperty().SetLineWidth(3.0);
		    
		    //Glyph the points
		    vtkSphereSource Sphere = new vtkSphereSource();
		    Sphere.SetRadius(0.02);
		    Sphere.SetPhiResolution(21);
		    Sphere.SetThetaResolution(21);


		    vtkPolyData polyData = new vtkPolyData();
		    polyData.SetPoints(Points);
		    
		    vtkGlyph3DMapper PointMapper = new vtkGlyph3DMapper();
		    PointMapper.SetInputData(polyData);
		    PointMapper.SetSourceConnection(Sphere.GetOutputPort());
		    
		    vtkActor PointActor = new vtkActor();
		    PointActor.SetMapper(PointMapper);
		    PointActor.GetProperty().SetColor(PointActorColor);
		    
		    // Create the renderer, render window and interactor.
		    vtkRenderer ren = new vtkRenderer();
		    vtkRenderWindow renWin = new vtkRenderWindow();
		    renWin.AddRenderer(ren);
		    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		    iren.SetRenderWindow(renWin);
		    
		    // Visualise the arrow
		    ren.AddActor(Actor);
		    ren.AddActor(PointActor);
		    ren.SetBackground(BgColor);
		    ren.ResetCamera();
	      
		    renWin.SetSize(300,300);
		    renWin.Render();

		    iren.Initialize();
		    iren.Start();
		  
	  }
}
