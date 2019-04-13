import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkStructuredPointsReader;
import vtk.vtkPiecewiseFunction;
import vtk.vtkColorTransferFunction;
import vtk.vtkVolumeProperty;
import vtk.vtkFixedPointVolumeRayCastMapper;
import vtk.vtkVolume;

   
public class SimpleRayCast 
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
      System.err.println("Usage: java -classpath ... Filename(.vtk) e.g ironProt.vtk");
      return;
    }
    String inputFilename = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Tomato", actorColor);
    colors.GetColor("Wheat", Bgcolor);
    
    // Create the reader for the data
    vtkStructuredPointsReader reader = new vtkStructuredPointsReader();
    reader.SetFileName(inputFilename);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Create transfer mapping scalar value to opacity
    vtkPiecewiseFunction opacityTransferFunction = new vtkPiecewiseFunction();
    opacityTransferFunction.AddPoint(20, 0.0);
    opacityTransferFunction.AddPoint(255, 0.2);
    
    // Create transfer mapping scalar value to color
    vtkColorTransferFunction colorTransferFunction = new vtkColorTransferFunction();
    colorTransferFunction.AddRGBPoint(0.0, 0.0, 0.0, 0.0);
    colorTransferFunction.AddRGBPoint(64.0, 1.0, 0.0, 0.0);
    colorTransferFunction.AddRGBPoint(128.0, 0.0, 0.0, 1.0);
    colorTransferFunction.AddRGBPoint(192.0, 0.0, 1.0, 0.0);
    colorTransferFunction.AddRGBPoint(255.0, 0.0, 0.2, 0.0);
    
    // The property describes how the data will look
    vtkVolumeProperty volumeProperty = new vtkVolumeProperty();
    volumeProperty.SetColor(colorTransferFunction);
    volumeProperty.SetScalarOpacity(opacityTransferFunction);
    volumeProperty.ShadeOn();
    volumeProperty.SetInterpolationTypeToLinear();
    
    // The mapper / ray cast function know how to render the data
    vtkFixedPointVolumeRayCastMapper volumeMapper = new vtkFixedPointVolumeRayCastMapper();
    volumeMapper.SetInputConnection(reader.GetOutputPort());
    
    // The volume holds the mapper and the property and can be used to position/orient the volume
    vtkVolume volume = new vtkVolume();
    volume.SetMapper(volumeMapper);
    volume.SetProperty(volumeProperty);
    
    ren.AddVolume(volume);
    ren.SetBackground(Bgcolor);
    ren.GetActiveCamera().Azimuth(45);
    ren.GetActiveCamera().Elevation(30);
    ren.ResetCameraClippingRange();
    ren.ResetCamera();
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
