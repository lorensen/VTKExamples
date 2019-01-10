import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkArrowSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkTransform;
import vtk.vtkTransformFilter;


public class TransformFilter 
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

    colors.GetColor("SteelBlue", actorColor);
    colors.GetColor("BurlyWood", Bgcolor);

    //Create an Arrow
    vtkArrowSource arrowSource = new vtkArrowSource();

    vtkTransform Transform = new vtkTransform();
    Transform.Scale(5, 1, 1);

    vtkTransformFilter TransformFilter = new vtkTransformFilter();
    TransformFilter.SetTransform(Transform);
    TransformFilter.SetInputConnection(arrowSource.GetOutputPort());
    TransformFilter.SetTransform(Transform);

    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(TransformFilter.GetOutputPort());
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetColor(actorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualize the actor
    ren.AddActor(actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
