import vtk.vtkActor;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;
import vtk.vtkCursor3D;

public class Cursor3D
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

    //For Actor Color
    double actorColor[] = new double[4];
    //For Cursor Actor Color
    double CursorActorColor[] = new double[4];
    //Renderer Background Color
     double Bgcolor[] = new double[4];

    colors.GetColor("LightPink", actorColor);
    colors.GetColor("Brown", CursorActorColor);
    colors.GetColor("MediumSpringGreen", Bgcolor);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.SetCenter(0.0,0.0,0.0);
    Sphere.SetRadius(5.0);
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the actor
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    vtkCursor3D Cursor = new vtkCursor3D();
    Cursor.SetModelBounds(-10, 10, -10, 10, -10, 10);
    Cursor.AllOn();
    Cursor.OutlineOff();
    Cursor.Update();

    vtkPolyDataMapper CursorMapper = new vtkPolyDataMapper();
    CursorMapper.SetInputConnection(Cursor.GetOutputPort());
    vtkActor CursorActor = new vtkActor();
    CursorActor.SetMapper(CursorMapper);
    CursorActor.GetProperty().SetColor(CursorActorColor);
    ren.AddActor(CursorActor);

    ren.ResetCamera();
    iren.Start();		
  }		  
}
