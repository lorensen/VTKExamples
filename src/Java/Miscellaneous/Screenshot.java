import vtk.*;

public class Screenshot
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

  public static void main(String[] args)
  {
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0);
    sphereSource.SetRadius(5.0);

    //create a mapper
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(sphereSource.GetOutputPort());

    // create an actor
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    // a renderer and render window
    vtkRenderer renderer = new vtkRenderer();
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);

    // an interactor
    vtkRenderWindowInteractor renderWindowInteractor = new vtkRenderWindowInteractor();
    renderWindowInteractor.SetRenderWindow(renderWindow);

    // add the actors to the scene
    renderer.AddActor(actor);
    renderer.SetBackground(1,1,1); // Background color white

    renderWindow.Render();

    vtkWindowToImageFilter windowToImageFilter = new vtkWindowToImageFilter();
    windowToImageFilter.SetInput(renderWindow);
    windowToImageFilter.SetMagnification(3); //set the resolution of the output image
    windowToImageFilter.Update();

    vtkPNGWriter writer = new vtkPNGWriter();
    writer.SetFileName("screenshot2.png");
    writer.SetInput(windowToImageFilter.GetOutput());
    writer.Write();

    renderWindow.Render();  
    renderer.ResetCamera();
    renderWindow.Render();
    renderWindowInteractor.Start();
  }
}
