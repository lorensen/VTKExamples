import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkProteinRibbonFilter;
import vtk.vtkPDBReader;
import vtk.vtkInteractorStyleSwitch;
import vtk.vtkPolyDataMapper;

public class ProteinRibbons
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
  

  public static void main(String args[]) 
  {
	  
    //parse command line arguments
    if (args.length != 1) 
    {
      System.err.println("Usage: java -classpath ... Filename(.pdb) e.g 2j6g.pdb");
      return;
    }
    String Filename = args[0];
  
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Silver", Bgcolor);
    
    // read protein from pdb
    vtkPDBReader reader = new vtkPDBReader();
    reader.SetFileName(Filename);

    // setup ribbon filter
    vtkProteinRibbonFilter ribbonFilter = new vtkProteinRibbonFilter();
    ribbonFilter.SetInputConnection(reader.GetOutputPort());

    // setup poly data mapper
    vtkPolyDataMapper polyDataMapper = new vtkPolyDataMapper();
    polyDataMapper.SetInputConnection(ribbonFilter.GetOutputPort());

    // setup actor
    vtkActor actor = new vtkActor();
    actor.SetMapper(polyDataMapper);
    actor.GetProperty().SetDiffuse(.7);
    actor.GetProperty().SetSpecular(.5);
    actor.GetProperty().SetSpecularPower(80.0);

    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    vtkInteractorStyleSwitch style = new vtkInteractorStyleSwitch();
    style.SetCurrentStyleToTrackballCamera();
    
    // Visualise
    ren.AddActor(actor);
    ren.ResetCameraClippingRange();
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.SetMultiSamples(0);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
