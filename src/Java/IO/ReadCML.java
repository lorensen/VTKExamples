import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkCMLMoleculeReader;
import vtk.vtkMoleculeMapper;

public class ReadCML 
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
      System.err.println("Usage: java -classpath ... Filename(.cml) e.g porphyrin.cml");
      return;
    }
    String inputFilename = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Silver", Bgcolor);
    
    vtkCMLMoleculeReader cmlSource = new vtkCMLMoleculeReader();
    
    cmlSource.SetFileName(inputFilename);

    vtkMoleculeMapper molmapper = new vtkMoleculeMapper();
    molmapper.SetInputConnection(cmlSource.GetOutputPort());

    molmapper.UseBallAndStickSettings();
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(molmapper);
    actor.GetProperty().SetDiffuse(.7);
    actor.GetProperty().SetSpecular(.5);
    actor.GetProperty().SetSpecularPower(20.0);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(actor);
    ren.SetBackground(Bgcolor);
      
    renWin.SetSize(300, 300);
    renWin.SetMultiSamples(0);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();
  }
}
