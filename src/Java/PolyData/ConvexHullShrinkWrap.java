import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkSphereSource;
import vtk.vtkPointSource;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkGlyph3D;
import vtk.vtkDataSetMapper;
import vtk.vtkNativeLibrary;
import vtk.vtkSmoothPolyDataFilter;

public class ConvexHullShrinkWrap  
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
	  
		    //For Glyph3DActor Color
		    double GlyphActorColor[] = new double[4];
		    //For Actor Color
		    double ActorColor[] = new double[4];
		    //Renderer Background Color
		    double EdgeColor[] = new double[4];
		    //Renderer Background Color
		    double BgColor[] = new double[4];
		  
			   
		    //Change Color Name to Use your own Color for Change Actor Color
		    Color.GetColor("Banana",GlyphActorColor);
		    //Change Color Name to Use your own Color for Change Actor Color
		    Color.GetColor("Tomato",ActorColor);
		    //Change Color Name to Use your own Color for Change Actor Color
		    Color.GetColor("IvoryBlack",EdgeColor);
		    //Change Color Name to Use your own Color for Renderer Background
		    Color.GetColor("DarkSlateGray",BgColor);
	    	  
		    //Create a Sphere
		    vtkSphereSource Sphere = new vtkSphereSource();
		    Sphere.SetRadius(10.0);
		    Sphere.SetPhiResolution(50);
		    Sphere.SetThetaResolution(50);
		   
		    	  
		    vtkPointSource PointSource = new vtkPointSource();
		    PointSource.SetNumberOfPoints(60);
		    PointSource.SetRadius(2);

		    
		    vtkSmoothPolyDataFilter SmoothFilter = new vtkSmoothPolyDataFilter();
		    SmoothFilter.SetInputConnection(0, Sphere.GetOutputPort());
		    SmoothFilter.SetInputConnection(1, PointSource.GetOutputPort());
		    
		    vtkSphereSource GlyphSource = new vtkSphereSource();
		    GlyphSource.SetRadius(0.04);

		    vtkGlyph3D Glyph3D = new vtkGlyph3D();
		    Glyph3D.SetInputConnection(PointSource.GetOutputPort());
		    Glyph3D.SetSourceConnection(GlyphSource.GetOutputPort());
		    Glyph3D.ScalingOff();
		    
		    vtkDataSetMapper Glyph3DMapper = new vtkDataSetMapper();
		    Glyph3DMapper.SetInputConnection(Glyph3D.GetOutputPort());
		    Glyph3DMapper.ScalarVisibilityOff();
		    
  
		    vtkActor Glyph3DActor = new vtkActor();
		    Glyph3DActor.SetMapper(Glyph3DMapper);
		    Glyph3DActor.GetProperty().SetColor(GlyphActorColor);

		    vtkDataSetMapper Mapper = new vtkDataSetMapper();
		    Mapper.SetInputConnection(SmoothFilter.GetOutputPort());
		    Mapper.ScalarVisibilityOff();
		    
		    // Create an actor for the surface  
		    vtkActor Actor = new vtkActor();
		    Actor.SetMapper(Mapper);
		    Actor.GetProperty().SetDiffuseColor(ActorColor);
		    Actor.GetProperty().SetEdgeColor(EdgeColor);
		    Actor.GetProperty().SetOpacity(1.0);
		    Actor.GetProperty().EdgeVisibilityOff();

	    
		    // Create the renderer, render window and interactor.
		    vtkRenderer ren = new vtkRenderer();
		    vtkRenderWindow renWin = new vtkRenderWindow();
		    renWin.AddRenderer(ren);
		    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		    iren.SetRenderWindow(renWin);
				    
		    // Visualise the arrow
		    ren.AddActor(Actor);
		    ren.AddActor(Glyph3DActor);
		    ren.SetBackground(BgColor);
		    ren.ResetCamera();
			      
		    renWin.SetSize(300,300);
		    renWin.Render();
		
		    iren.Initialize();
		    iren.Start();
			
		    
	  }
}
