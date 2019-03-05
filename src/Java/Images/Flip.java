import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;
import vtk.vtkImageMandelbrotSource;
import vtk.vtkImageCast;
import vtk.vtkImageFlip;
import vtk.vtkImageActor;
import vtk.vtkInteractorStyleImage;


public class Flip 
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

    //For inputRenderer Color
    double inputRendererColor[] = new double[] {.4, .5, .9, 1};
    //For xActor Color
    double xActorColor[] = new double [] {.4, .5, .6, 1};
    //For yActor Color
    double yActorColor[] = new double[] {.4, .5, .7, 1};
    //For zActor Color
    double zActorColor[] = new double[] {.4, .5, .8, 1};
    
        
    //Change Color Name to Use your own Color for Change inputRenderer Color
    Color.SetColor("inputRendererColor",inputRendererColor);
    //Change Color Name to Use your own Color for Change xActorColor Color
    Color.SetColor("xActorColor",xActorColor);
    //Change Color Name to Use your own Color for Change yActorColor Color
    Color.SetColor("yActorColor",yActorColor);
    //Change Color Name to Use your own Color for Change zActorColor Color
    Color.SetColor("zActorColor",zActorColor);

    
    //Create an image
    vtkImageMandelbrotSource source = new vtkImageMandelbrotSource();
    source.Update();

    vtkImageCast castSource = new vtkImageCast();
    castSource.SetOutputScalarTypeToUnsignedChar();
    castSource.SetInputConnection(source.GetOutputPort());
    castSource.Update();
    
    vtkImageFlip flipXFilter = new vtkImageFlip();
    flipXFilter.SetFilteredAxis(0); // flip x axis
    flipXFilter.SetInputConnection(source.GetOutputPort());
    flipXFilter.Update();

    vtkImageCast castXFilter = new vtkImageCast();
    castXFilter.SetOutputScalarTypeToUnsignedChar();
    castXFilter.SetInputConnection(flipXFilter.GetOutputPort());
    castXFilter.Update();
    
    vtkImageFlip flipYFilter = new vtkImageFlip();
    flipYFilter.SetFilteredAxis(1); // flip y axis
    flipYFilter.SetInputConnection(source.GetOutputPort());
    flipYFilter.Update();

    vtkImageCast castYFilter = new vtkImageCast();
    castYFilter.SetOutputScalarTypeToUnsignedChar();
    castYFilter.SetInputConnection(flipYFilter.GetOutputPort());
    castYFilter.Update();
    
    vtkImageFlip flipZFilter = new vtkImageFlip();
    flipZFilter.SetFilteredAxis(2); // flip z axis
    flipZFilter.SetInputConnection(source.GetOutputPort());
    flipZFilter.Update();

    vtkImageCast castZFilter = new vtkImageCast();
    castZFilter.SetOutputScalarTypeToUnsignedChar();
    castZFilter.SetInputConnection(flipZFilter.GetOutputPort());
    castZFilter.Update();
    
    //Create actors
    vtkImageActor inputActor = new vtkImageActor();
    inputActor.GetMapper().SetInputConnection(castSource.GetOutputPort());

    vtkImageActor xActor = new vtkImageActor();
    xActor.GetMapper().SetInputConnection(castXFilter.GetOutputPort());

    vtkImageActor yActor = new vtkImageActor();
    yActor.GetMapper().SetInputConnection(castYFilter.GetOutputPort());

    vtkImageActor zActor = new vtkImageActor();
    zActor.GetMapper().SetInputConnection(castZFilter.GetOutputPort());
    
    //Define viewport ranges
    //(xmin, ymin, xmax, ymax)
    double inputViewport[] = new double[] {0.0, 0.0, 0.25, 1.0};
    double xViewport[] = new double[] {0.25, 0.0, 0.5, 1.0};
    double yViewport[] = new double[] {0.5, 0.0, 0.75, 1.0};
    double zViewport[] = new double[] {0.75, 0.0, 1.0, 1.0};
    
    // Setup renderers
    vtkRenderer inputRenderer = new vtkRenderer();
    inputRenderer.SetViewport(inputViewport);
    inputRenderer.AddActor(inputActor);
    inputRenderer.ResetCamera();
    inputRenderer.SetBackground(inputRendererColor);

    vtkRenderer xRenderer = new vtkRenderer();
    xRenderer.SetViewport(xViewport);
    xRenderer.AddActor(xActor);
    xRenderer.ResetCamera();
    xRenderer.SetBackground(xActorColor);

    vtkRenderer yRenderer = new vtkRenderer();
    yRenderer.SetViewport(yViewport);
    yRenderer.AddActor(yActor);
    yRenderer.ResetCamera();
    yRenderer.SetBackground(yActorColor);

    vtkRenderer zRenderer = new vtkRenderer();
    zRenderer.SetViewport(zViewport);
    zRenderer.AddActor(zActor);
    zRenderer.ResetCamera();
    zRenderer.SetBackground(zActorColor);
    
    
    // Setup render window
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.SetSize(1000, 250);
    renderWindow.AddRenderer(inputRenderer);
    renderWindow.AddRenderer(xRenderer);
    renderWindow.AddRenderer(yRenderer);
    renderWindow.AddRenderer(zRenderer);

    // Setup render window interactor
    vtkRenderWindowInteractor renderWindowInteractor = new vtkRenderWindowInteractor();
    vtkInteractorStyleImage style = new vtkInteractorStyleImage();

    renderWindowInteractor.SetInteractorStyle(style);

    // Render and start interaction
    renderWindowInteractor.SetRenderWindow(renderWindow);
    renderWindow.Render();
    renderWindowInteractor.Initialize();

    renderWindowInteractor.Start();

  }
}
