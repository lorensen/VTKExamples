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


public class MedicalDemo1 
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

    //For skin  Color
    double skinColor[] = new double[4];
    //For outline Color
    double outlineColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Coral", skinColor);
    colors.GetColor("Black", outlineColor);
    colors.GetColor("SteelBlue", Bgcolor);
	
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    vtkMetaImageReader reader = new vtkMetaImageReader();
    reader.SetFileName(inputFilename);
    
    // An isosurface, or contour value of 500 is known to correspond to the skin of the patient.
    vtkMarchingCubes skinExtractor = new vtkMarchingCubes();
    skinExtractor.SetInputConnection(reader.GetOutputPort());
    skinExtractor.SetValue(0, 500);
    
    vtkPolyDataMapper skinMapper = new vtkPolyDataMapper();
    skinMapper.SetInputConnection(skinExtractor.GetOutputPort());
    skinMapper.ScalarVisibilityOff();
    
    vtkActor skin = new vtkActor();
    skin.SetMapper(skinMapper);
    skin.GetProperty().SetDiffuseColor(skinColor);
    
    // An outline provides context around the data.
    vtkOutlineFilter outlineData = new vtkOutlineFilter();
    outlineData.SetInputConnection(reader.GetOutputPort());
    
    vtkPolyDataMapper mapOutline = new vtkPolyDataMapper();
    mapOutline.SetInputConnection(outlineData.GetOutputPort());
    
    vtkActor outline = new vtkActor();
    outline.SetMapper(mapOutline);
    outline.GetProperty().SetColor(outlineColor);
    
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
    ren.AddActor(skin);
    ren.SetActiveCamera(aCamera);
    ren.ResetCamera ();
    aCamera.Dolly(1.0);
    
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
