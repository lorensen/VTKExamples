import vtk.vtkActor;
import vtk.vtkLight;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderer;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkSphereSource;

public class AmbientSpheres {
  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
  static {
    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
        if (!lib.IsLoaded()) {
          System.out.println(lib.GetLibraryName() + " not loaded");
        }
      }
    }
    vtkNativeLibrary.DisableOutputWindow(null);
  }
  // -----------------------------------------------------------------

  public static void main(String s[]) {

    vtkNamedColors colors = new vtkNamedColors();

    double bkg[] = new double[]{0.1, 0.2, 0.4, 1.0};

    double spheresColor[] = new double[4];
    colors.GetColor("Red", spheresColor);

    // The following lines create a sphere represented by polygons.
    //
    vtkSphereSource SphereSource = new vtkSphereSource();
    SphereSource.SetThetaResolution(100);
    SphereSource.SetPhiResolution(50);

    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes
    // are defined.
    //
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(SphereSource.GetOutputPort());

    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // In this example we create eight different spheres (two rows of four
    // spheres) and set the specular lighting coefficients. A little ambient
    // is turned on so the sphere is not completely black on the back side.

    // Since we are using the same sphere source and mapper for all eight spheres
    // we will use an array.
    //
    double ambient = 0.125;
    double diffuse = 0.0;
    double specular = 0.0;
    double position[] = new double[]{0.0, 0.0, 0.0};
    vtkActor[] Sphere = new vtkActor[8];
    for (int i = 0; i < 8; ++i) {
      Sphere[i] = new vtkActor();
      Sphere[i].SetMapper(sphereMapper);
      Sphere[i].GetProperty().SetColor(spheresColor);
      Sphere[i].GetProperty().SetAmbient(ambient);
      Sphere[i].GetProperty().SetDiffuse(diffuse);
      Sphere[i].GetProperty().SetSpecular(specular);
      Sphere[i].AddPosition(position);
      ambient += 0.125;
      position[0] += 1.25;
      if (i == 3) {
        position[0] = 0;
        position[1] = 1.25;
      }
    }

    //  Create the graphics structure. The renderer renders into the
    //  render window. The render window interactor captures mouse events
    //  and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    //
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    //  Add the actors to the renderer, set the background and size.
    for (int i = 0; i < 8; ++i) {
      ren.AddActor(Sphere[i]);
    }
    ren.SetBackground(bkg);
    renWin.SetSize(640, 480);

    // Set up the lighting.
    vtkLight Light = new vtkLight();
    Light.SetFocalPoint(1.875, 0.6125, 0);
    Light.SetPosition(0.875, 1.6125, 1);
    ren.AddLight(Light);

    // We want to eliminate perspective effects on the apparent lighting.
    // Parallel camera projection will be used. To zoom in parallel projection
    // mode, the ParallelScale is set.
    //
    ren.GetActiveCamera().SetFocalPoint(0, 0, 0);
    ren.GetActiveCamera().SetPosition(0, 0, 1);
    ren.GetActiveCamera().SetViewUp(0, 1, 0);
    ren.GetActiveCamera().ParallelProjectionOn();
    ren.ResetCamera();
    ren.GetActiveCamera().SetParallelScale(2.0);

    iren.Initialize();
    renWin.Render();
    iren.Start();

  }
}
