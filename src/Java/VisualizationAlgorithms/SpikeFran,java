import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkGlyph3D;
import vtk.vtkPolyDataReader;
import vtk.vtkPolyDataNormals;
import vtk.vtkTransformPolyDataFilter;
import vtk.vtkMaskPoints;
import vtk.vtkConeSource;
import vtk.vtkTransform;

public class SpikeFran
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
      System.err.println("Usage: java -classpath ... Filename(.vtk) e.g fran_cut.vtk");
      return;
    }
    String inputFilename = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();

    //For franActor Color
    double franActorColor[] = new double[4];
    //For spikeActor Color
    double spikeActorColor[] = new double[4];
    
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Flesh", franActorColor);
    colors.GetColor("Emerald_Green", spikeActorColor);
    colors.GetColor("SlateGray", Bgcolor);
    
    vtkPolyDataReader fran = new vtkPolyDataReader();
    fran.SetFileName(inputFilename);
    
    vtkPolyDataNormals normals = new vtkPolyDataNormals();
    normals.SetInputConnection(fran.GetOutputPort());
    normals.FlipNormalsOn();
    
    vtkPolyDataMapper franMapper = new vtkPolyDataMapper();
    franMapper.SetInputConnection(normals.GetOutputPort());
    
    vtkActor franActor = new vtkActor();
    franActor.SetMapper(franMapper);
    franActor.GetProperty().SetColor(franActorColor);
    
    // We subsample the dataset because we want to glyph just a subset of
    // the points. Otherwise the display is cluttered and cannot be easily
    // read. The RandomModeOn and SetOnRatio combine to random select one out
    // of every 10 points in the dataset.
    
    vtkMaskPoints ptMask = new vtkMaskPoints();
    ptMask.SetInputConnection(normals.GetOutputPort());
    ptMask.SetOnRatio(10);
    ptMask.RandomModeOn();
    
    // In this case we are using a cone as a glyph. We transform the cone so
    // its base is at 0,0,0. This is the point where glyph rotation occurs.
    
    vtkConeSource cone = new vtkConeSource();
    cone.SetResolution(6);
    
    vtkTransform transform = new vtkTransform();
    transform.Translate(0.5, 0.0, 0.0);
    
    vtkTransformPolyDataFilter transformF = new vtkTransformPolyDataFilter();
    transformF.SetInputConnection(cone.GetOutputPort());
    transformF.SetTransform(transform);
    
    // vtkGlyph3D takes two inputs: the input point set (SetInputConnection)
    // which can be any vtkDataSet; and the glyph (SetSourceConnection) which
    // must be a vtkPolyData.  We are interested in orienting the glyphs by the
    // surface normals that we previously generated.
    
    vtkGlyph3D glyph = new vtkGlyph3D();
    glyph.SetInputConnection(ptMask.GetOutputPort());
    glyph.SetSourceConnection(transformF.GetOutputPort());
    glyph.SetVectorModeToUseNormal();
    glyph.SetScaleModeToScaleByVector();
    glyph.SetScaleFactor(0.004);
    
    vtkPolyDataMapper spikeMapper = new vtkPolyDataMapper();
    spikeMapper.SetInputConnection(glyph.GetOutputPort());
    
    vtkActor spikeActor = new vtkActor();
    spikeActor.SetMapper(spikeMapper);
    spikeActor.GetProperty().SetColor(spikeActorColor);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetSize(640, 480);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.AddActor(franActor);
    ren.AddActor(spikeActor);
    renWin.Render();
	
    ren.SetBackground(Bgcolor);
    ren.GetActiveCamera().Zoom(1.4);
    ren.GetActiveCamera().Azimuth(110);

    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
