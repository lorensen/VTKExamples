import vtk.*;

public class Animation
{

  static
  {
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
    System.loadLibrary("vtkImagingJava");
    System.loadLibrary("vtkGraphicsJava");
    System.loadLibrary("vtkRenderingJava");
  }

  static class vtkTimerCallback
  {
    void Execute()
    {
      ++this.TimerCount;
      System.out.println(this.TimerCount);
      actor.SetPosition(this.TimerCount, this.TimerCount,0);
      iren.GetRenderWindow().Render();
    }

    private int TimerCount = 0;
    public vtkActor actor;
    public vtkRenderWindowInteractor iren;
  }

  public static void main(String[] args)
  {
    //Create a sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0);
    sphereSource.SetRadius(5.0);
    sphereSource.Update();

    //Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(sphereSource.GetOutputPort());
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    //Create a renderer, render window, and interactor
    vtkRenderer renderer = new vtkRenderer();
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);
    vtkRenderWindowInteractor renderWindowInteractor = new vtkRenderWindowInteractor();
    renderWindowInteractor.SetRenderWindow(renderWindow);

    //Add the actor to the scene
    renderer.AddActor(actor);
    renderer.SetBackground(1,1,1); // Background color white

    //Render and interact
    renderWindow.Render();

    // Initialize must be called prior to creating timer events.
    renderWindowInteractor.Initialize();

    // Sign up to receive TimerEvent
    vtkTimerCallback cb = new vtkTimerCallback();
    cb.actor = actor;
    cb.iren = renderWindowInteractor;
    renderWindowInteractor.AddObserver("TimerEvent", cb, "Execute");

    int timerId = renderWindowInteractor.CreateRepeatingTimer(100);
    System.out.println("timerId: " + timerId);

    //start the interaction and timer
    renderWindowInteractor.Start();
  }
}
