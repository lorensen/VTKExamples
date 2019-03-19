import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;
import vtk.vtkActorCollection;
import vtk.vtk3DSImporter;
import vtk.vtkCamera;

public class ThreeDSImporter
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
      System.err.println("Usage: java -classpath ... Filename(.3ds) e.g iflamingo.3ds");
      return;
    }
    String inputFilename = args[0];

    vtkNamedColors Color = new vtkNamedColors(); 

    //Renderer Background Color
    double BgColor[] = new double[4];
    double BgColor2[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Gold",BgColor);
    Color.GetColor("Wheat",BgColor2);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    vtk3DSImporter importer = new vtk3DSImporter();
    importer.SetFileName(inputFilename);
    importer.ComputeNormalsOn();
    
    renWin.AddRenderer(ren);
    ren.SetBackground2 (BgColor);
    ren.SetBackground (BgColor2);
    ren.GradientBackgroundOn();
    
    importer.SetRenderWindow(renWin);
    importer.Update();
    
    vtkActorCollection actors = new vtkActorCollection();
    actors = ren.GetActors();
    System.out.println("There are" + " " + actors.GetNumberOfItems() + " " + "actors");


    renWin.SetSize(300,300);
    renWin.Render();
    
    vtkCamera camera = new vtkCamera();
    camera.SetPosition (0, -1, 0);
    camera.SetFocalPoint (0, 0, 0);
    camera.SetViewUp (0, 0, 1);
    camera.Azimuth(150);
    camera.Elevation(30);
    
    ren.SetActiveCamera(camera);
    ren.ResetCamera();
    ren.ResetCameraClippingRange();
    
    iren.Initialize();
    iren.Start();

  }
}
