import vtk.vtkSphereSource;
import vtk.vtkActor;
import vtk.vtkLight;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;

public class AmbientSpheres 
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

  public static void main(String s[]) 
  {
    
    vtkNamedColors colors = new vtkNamedColors();

    //For Sphere1 Color
    double Sphere1Color[] = new double[4];
       
    //For Sphere2 Color
    double Sphere2Color[] = new double[4];
    
    //For Sphere3 Color
    double Sphere3Color[] = new double[4];
    
    //For Sphere4 Color
    double Sphere4Color[] = new double[4];
    
    //For Sphere5 Color
    double Sphere5Color[] = new double[4];
    
    //For Sphere6 Color
    double Sphere6Color[] = new double[4];
    
    //For Sphere7 Color
    double Sphere7Color[] = new double[4];
    
    //For Sphere8 Color
    double Sphere8Color[] = new double[4];
        
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Navy", Sphere1Color);
    colors.GetColor("Navy", Sphere2Color);
    colors.GetColor("Navy", Sphere3Color);
    colors.GetColor("Navy", Sphere4Color);
    colors.GetColor("Navy", Sphere5Color);
    colors.GetColor("Navy", Sphere6Color);
    colors.GetColor("Navy", Sphere7Color);
    colors.GetColor("Navy", Sphere8Color);
    
    colors.GetColor("LightSalmon", Bgcolor);

    //  The following lines create a sphere represented by polygons.
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.SetThetaResolution(100);
    Sphere.SetPhiResolution(50);
        
    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes
    // are defined.
   
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(Sphere.GetOutputPort());
        
    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // In this example we create eight different spheres (two rows of four
    // spheres) and set the specular lighting coefficients. A little ambient
    // is turned on so the sphere is not completely black on the back side.
    
    vtkActor Sphere1 = new vtkActor();
    Sphere1.SetMapper(sphereMapper);
    Sphere1.GetProperty().SetColor(Sphere1Color);
    Sphere1.GetProperty().SetAmbient(0.125);
    Sphere1.GetProperty().SetDiffuse(0.0);
    Sphere1.GetProperty().SetSpecular(0.0);
    
    vtkActor Sphere2 = new vtkActor();
    Sphere2.SetMapper(sphereMapper);
    Sphere2.GetProperty().SetColor(Sphere2Color);
    Sphere2.GetProperty().SetAmbient(0.25);
    Sphere2.GetProperty().SetDiffuse(0.0);
    Sphere2.GetProperty().SetSpecular(0.0);
    Sphere2.SetPosition(1.25, 0, 0);
    
    vtkActor Sphere3 = new vtkActor();
    Sphere3.SetMapper(sphereMapper);
    Sphere3.GetProperty().SetColor(Sphere2Color);
    Sphere3.GetProperty().SetAmbient(0.375);
    Sphere3.GetProperty().SetDiffuse(0.0);
    Sphere3.GetProperty().SetSpecular(0.0);
    Sphere3.SetPosition(2.5, 0, 0);
    
    vtkActor Sphere4 = new vtkActor();
    Sphere4.SetMapper(sphereMapper);
    Sphere4.GetProperty().SetColor(Sphere2Color);
    Sphere4.GetProperty().SetAmbient(0.5);
    Sphere4.GetProperty().SetDiffuse(0.0);
    Sphere4.GetProperty().SetSpecular(0.0);
    Sphere4.SetPosition(3.75, 0, 0);
    
    vtkActor Sphere5 = new vtkActor();
    Sphere5.SetMapper(sphereMapper);
    Sphere5.GetProperty().SetColor(Sphere2Color);
    Sphere5.GetProperty().SetAmbient(0.625);
    Sphere5.GetProperty().SetDiffuse(0.0);
    Sphere5.GetProperty().SetSpecular(0.0);
    Sphere5.SetPosition(0.0, 1.25, 0);
    
    vtkActor Sphere6 = new vtkActor();
    Sphere6.SetMapper(sphereMapper);
    Sphere6.GetProperty().SetColor(Sphere2Color);
    Sphere6.GetProperty().SetAmbient(0.75);
    Sphere6.GetProperty().SetDiffuse(0.0);
    Sphere6.GetProperty().SetSpecular(0.0);
    Sphere6.SetPosition(1.25, 1.25, 0);
    
    vtkActor Sphere7 = new vtkActor();
    Sphere7.SetMapper(sphereMapper);
    Sphere7.GetProperty().SetColor(Sphere2Color);
    Sphere7.GetProperty().SetAmbient(0.875);
    Sphere7.GetProperty().SetDiffuse(0.0);
    Sphere7.GetProperty().SetSpecular(0.0);
    Sphere7.SetPosition(2.5, 1.25, 0);
    
    vtkActor Sphere8 = new vtkActor();
    Sphere8.SetMapper(sphereMapper);
    Sphere8.GetProperty().SetColor(Sphere2Color);
    Sphere8.GetProperty().SetAmbient(1.0);
    Sphere8.GetProperty().SetDiffuse(0.0);
    Sphere8.GetProperty().SetSpecular(0.0);
    Sphere8.SetPosition(3.75, 1.25, 0);
    
    //  Create the graphics structure. The renderer renders into the
    // render window. The render window interactor captures mouse events
    // and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    
     vtkRenderer ren = new vtkRenderer();
     vtkRenderWindow renWin = new vtkRenderWindow();
     renWin.AddRenderer(ren);
     vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
     iren.SetRenderWindow(renWin);

     //  Add the actors to the renderer, set the background and size.
     ren.AddActor(Sphere1);
     ren.AddActor(Sphere2);
     ren.AddActor(Sphere3);
     ren.AddActor(Sphere4);
     ren.AddActor(Sphere5);
     ren.AddActor(Sphere6);
     ren.AddActor(Sphere7);
     ren.AddActor(Sphere8);
     ren.SetBackground(Bgcolor);

     renWin.SetSize(640, 480);
     
     // Set up the lighting.
     vtkLight Light = new vtkLight();
     Light.SetFocalPoint(1.875, 0.6125, 0);
     Light.SetPosition(0.875, 1.6125, 1);
     ren.AddLight(Light);
     
     // We want to eliminate perspective effects on the apparent lighting.
     // Parallel camera projection will be used. To zoom in parallel projection
     // mode, the ParallelScale is set.
     
     ren.GetActiveCamera().SetFocalPoint(0, 0, 0);
     ren.GetActiveCamera().SetPosition(0, 0, 1);
     ren.GetActiveCamera().SetViewUp(0, 1, 0);
     ren.GetActiveCamera().ParallelProjectionOn();
     ren.ResetCamera();
     ren.GetActiveCamera().SetParallelScale(1.5);
     
     renWin.Render();

     iren.Initialize();
     iren.Start();
     
  }
}
