import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkRegularPolygonSource;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;

public class Circle 
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
    //Renderer Background Color
    double Bgcolor[] = new double[4];


    colors.GetColor("White", actorColor);
    colors.GetColor("DarkSeaGreen", Bgcolor);

    vtkRegularPolygonSource PolygoneSource = new vtkRegularPolygonSource();
    PolygoneSource.SetNumberOfSides(100);
    PolygoneSource.SetRadius(5);
    PolygoneSource.SetCenter(0,0,0);
    //Uncomment below line to Visualize outline of circle
    PolygoneSource.GeneratePolygonOff();
    PolygoneSource.Update();


    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(PolygoneSource.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor);


    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
