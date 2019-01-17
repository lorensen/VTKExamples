import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkSphereSource;
import vtk.vtkTransform;
import vtk.vtkTransformPolyDataFilter;


public class TransformPolyData 
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

    //For OriginalActor Color
    double OriginalActorColor[] = new double[4];
    
    //Renderer Background Color
    double Bgcolor[] = new double[4];
    
    //TransformedActor color
    double TransformedActorColor[] = new double[4];

    colors.GetColor("LightSeaGreen", OriginalActorColor);
    colors.GetColor("Sienna", Bgcolor);
    colors.GetColor("DeepSkyBlue", TransformedActorColor);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper OriginalMapper = new vtkPolyDataMapper();
    OriginalMapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor OriginalActor = new vtkActor();
    OriginalActor.SetMapper(OriginalMapper);
    OriginalActor.GetProperty().SetColor(OriginalActorColor);


    //Set up the transform filter
    vtkTransform Translation = new vtkTransform();
    Translation.Translate(1.0, 2.0, 3.0);

    vtkTransformPolyDataFilter TransformFilter = new vtkTransformPolyDataFilter();
    TransformFilter.SetInputConnection(Sphere.GetOutputPort());
    TransformFilter.SetTransform(Translation);
    TransformFilter.Update();

    //Set up the actor to display the transformed polydata
    vtkPolyDataMapper TransformedMapper = new vtkPolyDataMapper();
    TransformedMapper.SetInputConnection(TransformFilter.GetOutputPort());

    vtkActor TransformedActor = new vtkActor();
    TransformedActor.SetMapper(TransformedMapper);
    TransformedActor.GetProperty().SetColor(TransformedActorColor);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualize the Actor
    ren.AddActor(OriginalActor);
    ren.AddActor(TransformedActor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
