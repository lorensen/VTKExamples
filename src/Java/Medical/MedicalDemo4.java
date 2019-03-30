import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkMetaImageReader;
import vtk.vtkCamera;
import vtk.vtkColorTransferFunction;
import vtk.vtkPiecewiseFunction;
import vtk.vtkFixedPointVolumeRayCastMapper;
import vtk.vtkVolumeProperty;
import vtk.vtkVolume;

public class MedicalDemo4 
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
      System.err.println("Usage: java -classpath ... Filename(.mhd) e.g FullHead.mhd");
      return;
    }
    String inputFilename = args[0];
    
    vtkNamedColors colors = new vtkNamedColors();
    
    double Bgcolor[] = new double[4];

    colors.GetColor("SteelBlue", Bgcolor);
	
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // The following reader is used to read a series of 2D slices (images)
    // that compose the volume. The slice dimensions are set, and the
    // pixel spacing. The data Endianness must also be specified. The reader
    // uses the FilePrefix in combination with the slice number to construct
    // filenames using the format FilePrefix.%d. (In this case the FilePrefix
    // is the root name of the file: quarter.)
    
    vtkMetaImageReader reader = new vtkMetaImageReader();
    reader.SetFileName(inputFilename);
    
    // The volume will be displayed by ray-cast alpha compositing.
    // A ray-cast mapper is needed to do the ray-casting.
    vtkFixedPointVolumeRayCastMapper volumeMapper = new vtkFixedPointVolumeRayCastMapper();
    volumeMapper.SetInputConnection(reader.GetOutputPort());

    // The color transfer function maps voxel intensities to colors.
    // It is modality-specific, and often anatomy-specific as well.
    // The goal is to one color for flesh (between 500 and 1000)
    // and another color for bone (1150 and over).
    vtkColorTransferFunction volumeColor = new vtkColorTransferFunction();
    volumeColor.AddRGBPoint(0,    0.0, 0.0, 0.0);
    volumeColor.AddRGBPoint(500,  1.0, 0.5, 0.3);
    volumeColor.AddRGBPoint(1000, 1.0, 0.5, 0.3);
    volumeColor.AddRGBPoint(1150, 1.0, 1.0, 0.9);

    // The opacity transfer function is used to control the opacity
    // of different tissue types.
    vtkPiecewiseFunction volumeScalarOpacity = new vtkPiecewiseFunction();
    volumeScalarOpacity.AddPoint(0,    0.00);
    volumeScalarOpacity.AddPoint(500,  0.15);
    volumeScalarOpacity.AddPoint(1000, 0.15);
    volumeScalarOpacity.AddPoint(1150, 0.85);
    
    // The gradient opacity function is used to decrease the opacity
    // in the "flat" regions of the volume while maintaining the opacity
    // at the boundaries between tissue types.  The gradient is measured
    // as the amount by which the intensity changes over unit distance.
    // For most medical data, the unit distance is 1mm.
    vtkPiecewiseFunction volumeGradientOpacity = new vtkPiecewiseFunction();
    volumeGradientOpacity.AddPoint(0,   0.0);
    volumeGradientOpacity.AddPoint(90,  0.5);
    volumeGradientOpacity.AddPoint(100, 1.0);
    
    // The VolumeProperty attaches the color and opacity functions to the
    // volume, and sets other volume properties.  The interpolation should
    // be set to linear to do a high-quality rendering.  The ShadeOn option
    // turns on directional lighting, which will usually enhance the
    // appearance of the volume and make it look more "3D".  However,
    // the quality of the shading depends on how accurately the gradient
    // of the volume can be calculated, and for noisy data the gradient
    // estimation will be very poor.  The impact of the shading can be
    // decreased by increasing the Ambient coefficient while decreasing
    // the Diffuse and Specular coefficient.  To increase the impact
    // of shading, decrease the Ambient and increase the Diffuse and Specular.
    vtkVolumeProperty volumeProperty = new vtkVolumeProperty();
    volumeProperty.SetColor(volumeColor);
    volumeProperty.SetScalarOpacity(volumeScalarOpacity);
    volumeProperty.SetGradientOpacity(volumeGradientOpacity);
    volumeProperty.SetInterpolationTypeToLinear();
    volumeProperty.ShadeOn();
    volumeProperty.SetAmbient(0.4);
    volumeProperty.SetDiffuse(0.6);
    volumeProperty.SetSpecular(0.2);
    
    // The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position
    // and orientation of the volume in world coordinates.
    vtkVolume volume = new vtkVolume();
    volume.SetMapper(volumeMapper);
    volume.SetProperty(volumeProperty);
    double c[] = new double[3];
    c=volume.GetCenter();
    
    ren.AddViewProp(volume);
    
    // Set up an initial view of the volume.  The focal point will be the
    // center of the volume, and the camera position will be 400mm to the
    // patient's left (which is our right).
    
    vtkCamera camera = new vtkCamera();
    camera.SetViewUp (0, 0, -1);
    camera.SetPosition (c[0], c[1] - 400, c[2]);
    camera.SetFocalPoint (c[0], c[1], c[2]);
    camera.Azimuth(30.0);
    camera.Elevation(30.0);
    camera.Dolly(0.75);
    
    // Actors are added to the renderer. An initial camera view is created.
    // The Dolly() method moves the camera towards the FocalPoint, thereby enlarging the image.
    
    ren.SetActiveCamera(camera);
    
    // Set a background color for the renderer and set the size of the
    // render window (expressed in pixels).
    ren.SetBackground(Bgcolor);

    // Note that when camera movement occurs (as it does in the Dolly()
    // method), the clipping planes often need adjusting. Clipping planes
    // consist of two planes: near and far along the view direction. The
    // near plane clips out objects in front of the plane; the far plane
    // clips out objects behind the plane. This way only what is drawn
    // between the planes is actually rendered.
    ren.ResetCameraClippingRange ();

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
