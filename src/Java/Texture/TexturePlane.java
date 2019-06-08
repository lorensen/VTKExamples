import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageReader2Factory;
import vtk.vtkImageReader2;
import vtk.vtkTexture;
import vtk.vtkPlaneSource;

public class TexturePlane 
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
      System.err.println("Usage: java -classpath ... Filename(.bmp) e.g masonry.bmp");
      return;
    }
    String inputFilename = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];
    
    colors.GetColor("SlateGray", Bgcolor);
    
    vtkImageReader2Factory readerFactory = new vtkImageReader2Factory();
    vtkImageReader2 textureFile = new vtkImageReader2();
    textureFile = readerFactory.CreateImageReader2(inputFilename);
    textureFile.SetFileName(inputFilename);
    textureFile.Update();
    
    vtkTexture atext = new vtkTexture();
    atext.SetInputConnection(textureFile.GetOutputPort());
    atext.InterpolateOn();
    
    // Create a plane source and actor. The vtkPlanesSource generates texture coordinates.
    
    vtkPlaneSource plane = new vtkPlaneSource();
    
    vtkPolyDataMapper  planeMapper = new vtkPolyDataMapper();
    planeMapper.SetInputConnection(plane.GetOutputPort());
    
    vtkActor planeActor = new vtkActor();
    planeActor.SetMapper(planeMapper);
    planeActor.SetTexture(atext);
	
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // VisualiZe
    ren.AddActor(planeActor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(640, 480);
    renWin.Render();
    
    ren.ResetCamera();
    ren.GetActiveCamera().Elevation(-30);
    ren.GetActiveCamera().Roll(-20);
    ren.ResetCameraClippingRange();
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
