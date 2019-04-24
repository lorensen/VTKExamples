import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageGridSource;
import vtk.vtkLookupTable;
import vtk.vtkImageMapToColors;
import vtk.vtkBMPReader;
import vtk.vtkImageBlend;
import vtk.vtkPoints;
import vtk.vtkThinPlateSplineTransform;
import vtk.vtkImageReslice;
import vtk.vtkImageMapper;
import vtk.vtkActor2D;
import vtk.vtkInteractorStyleTerrain;

public class ThinPlateSplineTransform 
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

    colors.GetColor("Black", Bgcolor);
    
    // First, create an image to warp
    vtkImageGridSource imageGrid = new vtkImageGridSource();
    imageGrid.SetGridSpacing(16, 16, 0);
    imageGrid.SetGridOrigin(0, 0, 0);
    imageGrid.SetDataExtent(0, 255, 0, 255, 0, 0);
    imageGrid.SetDataScalarTypeToUnsignedChar();

    vtkLookupTable table = new vtkLookupTable();
    table.SetTableRange(0, 1);
    table.SetAlphaRange(0.0, 1.0);
    table.SetHueRange(0.15, 0.15);
    table.SetSaturationRange(1, 1);
    table.SetValueRange(0, 1 );
    table.Build();
    
    vtkImageMapToColors alpha = new vtkImageMapToColors();
    alpha.SetInputConnection(imageGrid.GetOutputPort());
    alpha.SetLookupTable( table );
    
    vtkBMPReader reader = new vtkBMPReader();
    reader.SetFileName(inputFilename);
    reader.Update();
    
    vtkImageBlend blend = new vtkImageBlend();
    blend.AddInputConnection(0, reader.GetOutputPort());
    blend.AddInputConnection(0, alpha.GetOutputPort());
    
    // Next, create a ThinPlateSpline transform
    vtkPoints p1 = new vtkPoints();
    p1.SetNumberOfPoints( 8 );
    p1.SetPoint(0, 0, 0, 0);
    p1.SetPoint(1, 0, 255, 0);
    p1.SetPoint(2, 255, 0, 0);
    p1.SetPoint(3, 255, 255, 0);
    p1.SetPoint(4, 96, 96, 0);
    p1.SetPoint(5, 96, 159, 0);
    p1.SetPoint(6, 159, 159, 0);
    p1.SetPoint(7, 159, 96, 0);

    vtkPoints p2 = new vtkPoints();
    p2.SetNumberOfPoints( 8 );
    p2.SetPoint(0, 0, 0, 0);
    p2.SetPoint(1, 0, 255, 0);
    p2.SetPoint(2, 255, 0, 0);
    p2.SetPoint(3, 255, 255, 0);
    p2.SetPoint(4, 96, 159, 0);
    p2.SetPoint(5, 159, 159, 0);
    p2.SetPoint(6, 159, 96, 0);
    p2.SetPoint(7, 96, 96, 0);
    
    vtkThinPlateSplineTransform transform = new vtkThinPlateSplineTransform();
    transform.SetSourceLandmarks(p2);
    transform.SetTargetLandmarks(p1);
    transform.SetBasisToR2LogR();
    // You must invert the transform before passing it to vtkImageReslice
    transform.Inverse();

    vtkImageReslice reslice = new vtkImageReslice();
    reslice.SetInputConnection(blend.GetOutputPort());
    reslice.SetResliceTransform(transform);
    reslice.SetInterpolationModeToLinear();
    
    vtkImageMapper map = new vtkImageMapper();
    map.SetInputConnection(reslice.GetOutputPort());
    map.SetColorWindow( 255.0);
    map.SetColorLevel(127.5);
    map.SetZSlice(0);
    
    vtkActor2D  actor = new vtkActor2D();
    actor.SetMapper(map);
    actor.SetPosition(0.0, 0.0);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    vtkInteractorStyleTerrain style = new vtkInteractorStyleTerrain();
    iren.SetInteractorStyle(style);
    
    // Visualize
    ren.AddActor(actor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(640, 480);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
