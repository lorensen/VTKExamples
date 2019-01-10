import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkLineSource;
import vtk.vtkTubeFilter;
import vtk.vtkWarpTo;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;

public class WarpTo 
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
    double actorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Silver", actorColor);
    colors.GetColor("MidnightBlue", Bgcolor);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    //Create a line
    vtkLineSource LineSource = new vtkLineSource();
    LineSource.SetPoint1(0, 0, 0);
    LineSource.SetPoint2(0, 1, 0);
    LineSource.SetResolution(20);
    LineSource.Update();

    //Create a tube (cylinder) around the line
    vtkTubeFilter TubeFilter = new vtkTubeFilter();
    TubeFilter.SetInputConnection(LineSource.GetOutputPort());
    TubeFilter.SetRadius(0.01);
    TubeFilter.SetNumberOfSides(50);
    TubeFilter.Update();

    vtkWarpTo WarpTo = new vtkWarpTo();
    WarpTo.SetInputConnection(TubeFilter.GetOutputPort());
    WarpTo.SetPosition(10, 1, 0);
    WarpTo.SetScaleFactor(5);
    WarpTo.AbsoluteOn();

    //Create a Mapper and Actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(WarpTo.GetOutputPort());
    mapper.ScalarVisibilityOff();

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetColor(actorColor);

    ren.AddActor(actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
