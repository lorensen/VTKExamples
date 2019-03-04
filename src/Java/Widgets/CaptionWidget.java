import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkSphereSource;
import vtk.vtkCaptionRepresentation;
import vtk.vtkCaptionWidget;

public class CaptionWidget 
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

  public static void main(String args[]) 
  {
    vtkNamedColors Color = new vtkNamedColors(); 

    //Renderer Background Color
    double BgColor[] = new double[4];
         
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("red",BgColor);
    
    //Sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.Update();
    
    //Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(sphereSource.GetOutputPort());
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    //Create the widget and its representation
    vtkCaptionRepresentation captionRepresentation = new vtkCaptionRepresentation();
    captionRepresentation.GetCaptionActor2D().SetCaption("Test Caption");
    captionRepresentation.GetCaptionActor2D().GetTextActor().GetTextProperty().SetFontSize(100);

    double pos[] = new double[] {0.5, 0, 0};
    captionRepresentation.SetAnchorPosition(pos);

    vtkCaptionWidget captionWidget = new vtkCaptionWidget();
    captionWidget.SetInteractor(iren);
    captionWidget.SetRepresentation(captionRepresentation);
        
    ren.AddActor(actor);
    ren.SetBackground(BgColor);
    
    renWin.SetSize(300,300);
    renWin.Render();
    captionWidget.On();

    iren.Initialize();
    iren.Start();
  }
}
