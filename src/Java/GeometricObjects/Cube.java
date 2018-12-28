import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkDataSetMapper;
import vtk.vtkCubeSource;
import vtk.vtkShrinkFilter;
import vtk.vtkProperty;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;


public class Cube 
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

    vtkNamedColors Color = new vtkNamedColors(); 
    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
    //BackFace color 
    double BackColor[] = new double[4];

    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("SpringGreen",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Red",BgColor);
    //Change Color Name to Use your own Color for BackFace Color
    Color.GetColor("Yellow",BackColor);


    // Create a cube.
    vtkCubeSource Cube = new vtkCubeSource();

    //shrink cells composing an arbitrary data set
    vtkShrinkFilter shrink = new vtkShrinkFilter();
    shrink.SetInputConnection(Cube.GetOutputPort());
    shrink.SetShrinkFactor(.9);

    //Create a Mapper and Actor
    vtkDataSetMapper Mapper = new vtkDataSetMapper();
    Mapper.SetInputConnection(shrink.GetOutputPort());

    vtkProperty Back = new vtkProperty();
    Back.SetColor(BackColor);

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().EdgeVisibilityOn();
    Actor.GetProperty().SetColor(ActorColor);
    Actor.SetBackfaceProperty(Back);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the arrow
    ren.AddActor(Actor);
    ren.SetBackground(BgColor);


    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();   
  }
} 
