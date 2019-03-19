import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;
import vtk.vtkActorCollection;
import vtk.vtkVRMLImporter;

public class VRMLImporter
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
      System.err.println("Usage: java -classpath ... Filename(.wrl) e.g sextant.wrl");
      return;
    }
    String inputFilename = args[0];

    vtkNamedColors Color = new vtkNamedColors(); 

    //Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Burlywood",BgColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // VRML Import
    vtkVRMLImporter importer = new vtkVRMLImporter();
    importer.SetFileName (inputFilename);
    importer.SetRenderWindow(renWin);
    importer.Update();
    
    vtkActorCollection actors = new vtkActorCollection();
    actors = ren.GetActors();
    System.out.println("There are" + " " + actors.GetNumberOfItems() + " actors");
	
    ren.SetBackground(BgColor);

    renWin.SetSize(300,300);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();

  }
}
