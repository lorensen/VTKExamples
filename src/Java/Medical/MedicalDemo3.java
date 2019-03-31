import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkMetaImageReader;
import vtk.vtkMarchingCubes;
import vtk.vtkOutlineFilter;
import vtk.vtkCamera;
import vtk.vtkStripper;
import vtk.vtkLookupTable;
import vtk.vtkImageMapToColors;
import vtk.vtkImageActor;

public class MedicalDemo3
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
    
    //For bone Color
    double boneColor[] = new double[4];
    //For skin  Color
    double skinColor[] = new double[4];
    //For outline Color
    double outlineColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Ivory", boneColor);
    colors.GetColor("Coral", skinColor);
    colors.GetColor("Black", outlineColor);
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
    reader.Update();
    
    // An isosurface, or contour value of 500 is known to correspond to the
    // skin of the patient.
    // The triangle stripper is used to create triangle strips from the
    // isosurface; these render much faster on many systems.
    vtkMarchingCubes skinExtractor = new vtkMarchingCubes();
    skinExtractor.SetInputConnection(reader.GetOutputPort());
    skinExtractor.SetValue(0, 500);
    skinExtractor.Update();
    
    vtkStripper skinStripper = new  vtkStripper();
    skinStripper.SetInputConnection(skinExtractor.GetOutputPort());
    skinStripper.Update();
    
    vtkPolyDataMapper skinMapper = new vtkPolyDataMapper();
    skinMapper.SetInputConnection(skinStripper.GetOutputPort());
    skinMapper.ScalarVisibilityOff();
    
    vtkActor skin = new vtkActor();
    skin.SetMapper(skinMapper);
    skin.GetProperty().SetDiffuseColor(skinColor);
    skin.GetProperty().SetSpecular(.3);
    skin.GetProperty().SetSpecularPower(20);
    
    // An isosurface, or contour value of 1150 is known to correspond to the
    // bone of the patient.
    // The triangle stripper is used to create triangle strips from the
    // isosurface; these render much faster on may systems.
    vtkMarchingCubes boneExtractor = new vtkMarchingCubes();
    boneExtractor.SetInputConnection(reader.GetOutputPort());
    boneExtractor.SetValue(0, 1150);

    vtkStripper boneStripper = new vtkStripper();
    boneStripper.SetInputConnection(boneExtractor.GetOutputPort());

    vtkPolyDataMapper boneMapper = new vtkPolyDataMapper();
    boneMapper.SetInputConnection(boneStripper.GetOutputPort());
    boneMapper.ScalarVisibilityOff();

    vtkActor bone = new vtkActor();
    bone.SetMapper(boneMapper);
    bone.GetProperty().SetDiffuseColor(boneColor);
       
    // An outline provides context around the data.
    vtkOutlineFilter outlineData = new vtkOutlineFilter();
    outlineData.SetInputConnection(reader.GetOutputPort());
    
    vtkPolyDataMapper mapOutline = new vtkPolyDataMapper();
    mapOutline.SetInputConnection(outlineData.GetOutputPort());
    
    vtkActor outline = new vtkActor();
    outline.SetMapper(mapOutline);
    outline.GetProperty().SetColor(outlineColor);
    
    // Now we are creating three orthogonal planes passing through the volume. 
    // Each plane uses a different texture map and therefore has different coloration.
    // Start by creating a black/white lookup table.
    
    vtkLookupTable bwLut = new vtkLookupTable();
    bwLut.SetTableRange (0, 2000);
    bwLut.SetSaturationRange (0, 0);
    bwLut.SetHueRange (0, 0);
    bwLut.SetValueRange (0, 1);
    bwLut.Build(); //effective built
    
    // Now create a lookup table that consists of the full hue circle (from HSV).
    vtkLookupTable hueLut = new vtkLookupTable();
    hueLut.SetTableRange (0, 2000);
    hueLut.SetHueRange (0, 1);
    hueLut.SetSaturationRange (1, 1);
    hueLut.SetValueRange (1, 1);
    hueLut.Build(); //effective built

    // Finally, create a lookup table with a single hue but having a range
    // in the saturation of the hue.
    vtkLookupTable satLut = new vtkLookupTable();
    satLut.SetTableRange (0, 2000);
    satLut.SetHueRange (.6, .6);
    satLut.SetSaturationRange (0, 1);
    satLut.SetValueRange (1, 1);
    satLut.Build(); //effective built
    
    // Create the first of the three planes. The filter vtkImageMapToColors
    // maps the data through the corresponding lookup table created above.  The
    // vtkImageActor is a type of vtkProp and conveniently displays an image on
    // a single quadrilateral plane. It does this using texture mapping and as
    // a result is quite fast. (Note: the input image has to be unsigned char
    // values, which the vtkImageMapToColors produces.) Note also that by
    // specifying the DisplayExtent, the pipeline requests data of this extent
    // and the vtkImageMapToColors only processes a slice of data.
    
    vtkImageMapToColors sagittalColors = new vtkImageMapToColors();
    sagittalColors.SetInputConnection(reader.GetOutputPort());
    sagittalColors.SetLookupTable(bwLut);
    sagittalColors.Update();
    
    vtkImageActor sagittal = new vtkImageActor();
    sagittal.GetMapper().SetInputConnection(sagittalColors.GetOutputPort());
    sagittal.SetDisplayExtent(128, 128, 0,255, 0,92);
    sagittal.ForceOpaqueOn();
    
    // Create the second (axial) plane of the three planes. We use the
    // same approach as before except that the extent differs.
    vtkImageMapToColors axialColors = new vtkImageMapToColors();
    axialColors.SetInputConnection(reader.GetOutputPort());
    axialColors.SetLookupTable(hueLut);
    axialColors.Update();
    
    vtkImageActor axial = new vtkImageActor();
    axial.GetMapper().SetInputConnection(axialColors.GetOutputPort());
    axial.SetDisplayExtent(0,255, 0,255, 46,46);
    axial.ForceOpaqueOn();
    
    // Create the third (coronal) plane of the three planes. We use
    // the same approach as before except that the extent differs.
    vtkImageMapToColors coronalColors = new vtkImageMapToColors();
    coronalColors.SetInputConnection(reader.GetOutputPort());
    coronalColors.SetLookupTable(satLut);
    coronalColors.Update();

    vtkImageActor coronal = new vtkImageActor();
    coronal.GetMapper().SetInputConnection(coronalColors.GetOutputPort());
    coronal.SetDisplayExtent(0,255, 128,128, 0,92);
    coronal.ForceOpaqueOn();
    
    // It is convenient to create an initial view of the data. 
    // The FocalPoint and Position form a vector direction. 
    // Later on (ResetCamera() method) this vector is used to position the camera to look at the data in this direction.
    
    vtkCamera aCamera = new vtkCamera();
    aCamera.SetViewUp (0, 0, -1);
    aCamera.SetPosition (0, -1, 0);
    aCamera.SetFocalPoint (0, 0, 0);
    aCamera.ComputeViewPlaneNormal();
    aCamera.Azimuth(30.0);
    aCamera.Elevation(30.0);
    
    // Actors are added to the renderer. An initial camera view is created.
    // The Dolly() method moves the camera towards the FocalPoint, thereby enlarging the image.
    
    ren.AddActor(outline);
    ren.AddActor(sagittal);
    ren.AddActor(axial);
    ren.AddActor(coronal);
    ren.AddActor(skin);
    ren.AddActor(bone);
    ren.SetActiveCamera(aCamera);
    ren.ResetCamera ();
    aCamera.Dolly(1.0);
    
    // Turn off bone for this example.
    bone.VisibilityOff();

    // Set skin to semi-transparent.
    skin.GetProperty().SetOpacity(0.5);

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
