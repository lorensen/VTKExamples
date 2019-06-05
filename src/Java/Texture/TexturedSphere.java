import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkTexturedSphereSource;
import vtk.vtkImageReader2Factory;
import vtk.vtkTexture;
import vtk.vtkImageReader2;
import vtk.vtkTransformTextureCoords;

public class TexturedSphere 
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
    if (args.length < 2) 
    {
      System.err.println("Usage: java -classpath ... Filename(.png) translate e.g earthTexture.png 0 ");
      return;
    }
    double translate[] = new double[3];
    String inputFilename = args[0];
    
    if (args.length > 2)
    {
    	translate[0] = Double.parseDouble(args[1]);
    }
    else 
    {
    	translate[0] = 0.0;
    }
    translate[1] = 0.0;
    translate[2] = 0.0;
    
    System.out.print(translate[0] + " " + translate[1] + " " + translate[2] + "\n");
    
    vtkNamedColors colors = new vtkNamedColors();

    double Bgcolor[] = new double[4];

    colors.GetColor("SteelBlue", Bgcolor);
    
    // Create a sphere with texture coordinates
    vtkTexturedSphereSource source = new vtkTexturedSphereSource();
    source.SetPhiResolution(40);
    source.SetThetaResolution(40);

    // Read texture file
    vtkImageReader2Factory readerFactory = new vtkImageReader2Factory();
    vtkImageReader2 imageReader = new vtkImageReader2();
    imageReader = readerFactory.CreateImageReader2(inputFilename);
    imageReader.SetFileName(inputFilename);
    
    // Create texture
    vtkTexture texture = new vtkTexture();
    texture.SetInputConnection(imageReader.GetOutputPort());

    vtkTransformTextureCoords transformTexture = new vtkTransformTextureCoords();
    transformTexture.SetInputConnection(source.GetOutputPort());
    transformTexture.SetPosition(translate);

    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(transformTexture.GetOutputPort());
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.SetTexture(texture);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.AddActor(actor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();
  }
}
