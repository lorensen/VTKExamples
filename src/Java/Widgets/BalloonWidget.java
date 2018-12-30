import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRegularPolygonSource;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkBalloonRepresentation;
import vtk.vtkBalloonWidget;
import vtk.vtkSphereSource;


public class BalloonWidget 
{
  //-----------------------------------------------------------------
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
    double SphereactorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];
    //PolygonActor color
    double PolygonActorColor[] = new double[4];

    colors.GetColor("OrangeRed", SphereactorColor);
    colors.GetColor("SkyBlue", Bgcolor);
    colors.GetColor("Indigo", PolygonActorColor);


    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.SetCenter(-4.0,0.0,0.0);
    Sphere.SetRadius(4.0);
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor SphereActor = new vtkActor();
    SphereActor.SetMapper(Mapper);
    SphereActor.GetProperty().SetColor(SphereactorColor);

    //Regular Polygon
    vtkRegularPolygonSource RegularPolygon = new vtkRegularPolygonSource();
    RegularPolygon.SetCenter(4, 0, 0);
    RegularPolygon.SetRadius(4);
    RegularPolygon.Update();

    vtkPolyDataMapper PolygonMapper = new vtkPolyDataMapper();
    PolygonMapper.SetInputConnection(RegularPolygon.GetOutputPort());

    vtkActor PolygonActor = new vtkActor();
    PolygonActor.SetMapper(PolygonMapper);
    PolygonActor.GetProperty().SetColor(PolygonActorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    //Create the widget
    vtkBalloonRepresentation BalloonRep = new vtkBalloonRepresentation();
    BalloonRep.SetBalloonLayoutToImageRight();


    vtkBalloonWidget BalloonWidget = new vtkBalloonWidget();
    BalloonWidget.SetInteractor(iren);
    BalloonWidget.SetRepresentation(BalloonRep);
    BalloonWidget.AddBalloon(SphereActor,"Sphere");
    BalloonWidget.AddBalloon(PolygonActor,"Polygon");

    // Visualise the arrow
    ren.AddActor(SphereActor);
    ren.AddActor(PolygonActor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();
    BalloonWidget.EnabledOn();

    iren.Initialize();
    iren.Start();
  }
}
