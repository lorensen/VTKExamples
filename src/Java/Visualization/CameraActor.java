import vtk.vtkActor;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkCamera;
import vtk.vtkCameraActor;
import vtk.vtkRenderWindow;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;

public class CameraActor
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
    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    //For Camera Actor Color
    double CamActorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("DeepSkyBlue", actorColor);
    colors.GetColor("Black", CamActorColor);
    colors.GetColor("Coral", Bgcolor);


    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.SetRadius(4);
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor);

    //Setting up Camera
    vtkCamera Camera = new vtkCamera();

    //Camera Actor
    vtkCameraActor CameraActor = new vtkCameraActor();
    CameraActor.SetCamera(Camera);
    CameraActor.GetProperty().SetColor(CamActorColor);
    double bounds[] = new double[6];
    CameraActor.GetBounds(bounds);


    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualize the Camera Actor
    ren.AddActor(Actor);
    ren.ResetCamera();
    Camera.DeepCopy(ren.GetActiveCamera());
    ren.AddActor(CameraActor);

    //Setting up Camera

    //ren.GetActiveCamera().SetPosition(0, 0, 1);
    //ren.GetActiveCamera().SetFocalPoint(0, 0, 0);
    ren.GetActiveCamera().SetViewUp(1, 0, 0);
    ren.GetActiveCamera().Azimuth(130);
    ren.GetActiveCamera().Elevation(130);
    //ren.GetActiveCamera().Zoom(1);

    //Setting up the Renderer Background Color.
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
