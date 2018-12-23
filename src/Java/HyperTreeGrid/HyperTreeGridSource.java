import vtk.vtkNativeLibrary;
import vtk.vtkActor;
import vtk.vtkHyperTreeGridSource;
import vtk.vtkShrinkFilter;
import vtk.vtkDataSetMapper;
import vtk.vtkNamedColors;

import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;

public class HyperTreeGridSource  {
	  
  //private static final long serialVersionUID = 1L;
	  

  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
  static {
    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
        if (!lib.IsLoaded()) {
          System.out.println(lib.GetLibraryName() + " not loaded");
        }
      }
    }
    vtkNativeLibrary.DisableOutputWindow(null);
  }
  // -----------------------------------------------------------------

  public static void main(String s[]) {
		  
    vtkNamedColors Color = new vtkNamedColors(); 
    //For Actor Color
    double ActorColor[] = new double[4];
    //For Renderer Background Color
    double BgColor[] = new double[4];
		   
		   
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Burlywood",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Teal",BgColor);
		
		   
    // Create hyper tree grid source
    vtkHyperTreeGridSource Source = new vtkHyperTreeGridSource();
    Source.SetMaximumLevel(6);
    Source.SetGridSize(3, 3, 2);
    Source.SetGridScale(1.5, 1.0, 0.7);
    Source.SetDimension(3);
    Source.SetBranchFactor(4);
    Source.SetDescriptor("RRR .R. .RR ..R ..R .R.|R.......................... ........................... ........................... .............R............. ....RR.RR........R......... .....RRRR.....R.RR......... ........................... ........................... ...........................|........................... ........................... ........................... ...RR.RR.......RR.......... ........................... RR......................... ........................... ........................... ........................... ........................... ........................... ........................... ........................... ............RRR............|........................... ........................... .......RR.................. ........................... ........................... ........................... ........................... ........................... ........................... ........................... ...........................|........................... ..........................." );
    Source.Update();

    vtkShrinkFilter Shrink = new vtkShrinkFilter();
    Shrink.SetInputConnection(Source.GetOutputPort());
    Shrink.SetShrinkFactor(0.8);
		   
    vtkDataSetMapper Mapper = new vtkDataSetMapper();
    Mapper.SetInputConnection(Shrink.GetOutputPort());
    Mapper.ScalarVisibilityOff();
		   
		   
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetDiffuseColor(ActorColor);
		   
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
    ren.ResetCameraClippingRange();
    ren.GetActiveCamera().Azimuth(150);
    ren.GetActiveCamera().Elevation(130);
    ren.ResetCameraClippingRange();

    renWin.SetSize(300, 300);
    renWin.Render();
	  
    iren.Initialize();
    iren.Start();

    
  }
} 
