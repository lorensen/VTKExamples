import vtk.*;

public class Cutter
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
    vtkCubeSource cube = new vtkCubeSource();
    cube.SetXLength(40);
    cube.SetYLength(30);
    cube.SetZLength(20);
    vtkPolyDataMapper cubeMapper = new vtkPolyDataMapper();
    cubeMapper.SetInputConnection(cube.GetOutputPort());

    //create a plane to cut,here it cuts in the XZ direction (xz normal=(1,0,0);XY =(0,0,1),YZ =(0,1,0)
    vtkPlane plane = new vtkPlane();
    plane.SetOrigin(10,0,0);
    plane.SetNormal(1,0,0);

    //create cutter
    vtkCutter cutter = new vtkCutter();
    cutter.SetCutFunction(plane);
    cutter.SetInput(cubeMapper.GetInput());
    cutter.Update();

    vtkPolyDataMapper cutterMapper = new vtkPolyDataMapper();
    cutterMapper.SetInputConnection( cutter.GetOutputPort());

    //create plane actor
    vtkActor planeActor = new vtkActor();
    planeActor.GetProperty().SetColor(1.0,1,0);
    planeActor.GetProperty().SetLineWidth(2);
    planeActor.SetMapper(cutterMapper);

    //create cube actor
    vtkActor cubeActor = new vtkActor();
    cubeActor.GetProperty().SetColor(0.5,1,0.5);
    cubeActor.GetProperty().SetOpacity(0.5);
    cubeActor.SetMapper(cubeMapper);

    //create renderers and add actors of plane and cube
    vtkRenderer ren = new vtkRenderer();
    ren.AddActor(planeActor);
    ren.AddActor(cubeActor);

    //Add renderer to renderwindow and render
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.SetSize(600, 600);

    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    ren.SetBackground(0,0,0);
    renWin.Render();

    iren.Start();
  }
}
