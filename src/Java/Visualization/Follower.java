import vtk.*;

public class Follower
{

  static
  {
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
    System.loadLibrary("vtkImagingJava");
    System.loadLibrary("vtkGraphicsJava");
    System.loadLibrary("vtkRenderingJava");
    System.loadLibrary("vtkHybridJava");
  }

  public static void main(String[] args)
  {
    //Create some text
    vtkVectorText textSource = new vtkVectorText();
    textSource.SetText( "Hello" );

    //Create a mapper
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection( textSource.GetOutputPort() );

    //Create a subclass of vtkActor: a vtkFollower that remains facing the camera
    vtkFollower follower = new vtkFollower();
    follower.SetMapper( mapper );
    follower.GetProperty().SetColor( 1, 0, 0 ); // red 

    //Create a transparent cube that does not move around to face the camera
    vtkCubeSource cubeSource = new vtkCubeSource();
    vtkPolyDataMapper cubeMapper = new vtkPolyDataMapper();
    cubeMapper.SetInputConnection( cubeSource.GetOutputPort() );
    vtkActor cubeActor = new vtkActor();
    cubeActor.SetMapper( cubeMapper );
    cubeActor.GetProperty().SetColor( 0, 0, 1 ); // blue
    cubeActor.GetProperty().SetOpacity( 0.3 );

    //Create a renderer, render window, and interactor
    vtkRenderer renderer = new vtkRenderer();
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.AddRenderer( renderer );
    vtkRenderWindowInteractor renderWindowInteractor = new vtkRenderWindowInteractor();
    ((vtkInteractorStyle)renderWindowInteractor.GetInteractorStyle()).AutoAdjustCameraClippingRangeOn();
    renderWindowInteractor.SetRenderWindow( renderWindow );

    //Add the actor to the scene
    renderer.AddActor( follower );
    renderer.AddActor( cubeActor );
    renderer.SetBackground( 1, 1, 1 ); // Background color white
    follower.SetCamera( renderer.GetActiveCamera() );

    //Render and interact
    renderWindow.Render();
    renderer.ResetCamera();
    renderWindow.Render();
    renderWindowInteractor.Start();
  }
}
