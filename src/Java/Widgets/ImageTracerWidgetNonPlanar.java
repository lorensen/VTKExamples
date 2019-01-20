import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkNamedColors;
import vtk.vtkRenderWindow;
import vtk.vtkRenderer;
import vtk.vtkPolyDataMapper;
import vtk.vtkActor;
import vtk.vtkImageTracerWidget;
import vtk.vtkInteractorStyleTrackball;
import vtk.vtkSphereSource;

public class ImageTracerWidgetNonPlanar 
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

    //For Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("LightCoral",BgColor);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    ren.AddActor(Actor);

    // An interactor
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    vtkInteractorStyleTrackball Style = new vtkInteractorStyleTrackball();
    iren.SetInteractorStyle(Style);  

    vtkImageTracerWidget TracerWidget = new vtkImageTracerWidget();
    TracerWidget.SetInteractor(iren);
    TracerWidget.SetViewProp(Actor);
    TracerWidget.On();

    ren.SetBackground(BgColor);
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Start();
    iren.Initialize();

  }
}
