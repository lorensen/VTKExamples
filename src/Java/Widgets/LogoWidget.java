import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkPolyDataMapper;
import vtk.vtkActor;
import vtk.vtkImageCanvasSource2D;
import vtk.vtkLogoRepresentation;
import vtk.vtkLogoWidget;  
     
public class LogoWidget
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
  
    vtkNamedColors colors = new vtkNamedColors(); 

    //Renderer Background Color
    double Bgcolor[] = new double[] {0.2, 0.3, 0.4}; 

    //A sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0);
    sphereSource.SetRadius(4.0);
    sphereSource.SetPhiResolution(4);
    sphereSource.SetThetaResolution(8);
    sphereSource.Update();

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

    //Create an image
    vtkImageCanvasSource2D drawing = new vtkImageCanvasSource2D();
    drawing.SetScalarTypeToUnsignedChar();
    drawing.SetNumberOfScalarComponents(3);
    drawing.SetExtent(0,200,0,200,0,0);

    //Clear the image
    // Note: SetDrawColour() uses double values of the rgb colors in the
    //       range [0 ... 255]
    //       So SetDrawColour(255, 255, 255) is white.
    drawing.SetDrawColor(255, 127, 100);
    drawing.FillBox(0,200,0,200);
    drawing.SetDrawColor(0, 0, 0);
    drawing.DrawCircle(100, 100, 50);
    drawing.Update();

    vtkLogoRepresentation logoRepresentation = new vtkLogoRepresentation();
    logoRepresentation.SetImage(drawing.GetOutput());
    logoRepresentation.SetPosition(0,0);
    logoRepresentation.SetPosition2(.4, .4);
    logoRepresentation.GetImageProperty().SetOpacity(.7);

    vtkLogoWidget logoWidget = new vtkLogoWidget();
    logoWidget.SetInteractor(iren);
    logoWidget.SetRepresentation(logoRepresentation);
    logoWidget.On();

    ren.SetBackground(Bgcolor);
    ren.AddActor(actor);
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
