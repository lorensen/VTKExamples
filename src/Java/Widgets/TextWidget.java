import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkTextActor;
import vtk.vtkTextRepresentation;
import vtk.vtkTextWidget;


public class TextWidget 
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
    
    //TextColor 
    double TextColor[] = new double[4];

    colors.GetColor("DimGray", actorColor);
    colors.GetColor("MidnightBlue", Bgcolor);
    colors.GetColor("Yellow", TextColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor);
    
    // Create the text widget
    vtkTextActor TextActor = new vtkTextActor();
    TextActor.SetInput("This is a Sphere");
    TextActor.GetTextProperty().SetColor(TextColor);
    TextActor.GetTextProperty().SetFontFamilyToCourier();

    vtkTextWidget TextWidget = new vtkTextWidget();

    vtkTextRepresentation TextRepresentation = new vtkTextRepresentation();
    TextRepresentation.GetPositionCoordinate().SetValue(0.15, 0.15);
    TextRepresentation.GetPosition2Coordinate().SetValue(0.7, 0.2);
    TextWidget.SetRepresentation(TextRepresentation);
    TextWidget.SetInteractor(iren);
    TextWidget.SetTextActor(TextActor);
    TextWidget.SelectableOff();


    //Visualize the actor
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();
    TextWidget.On();

    iren.Initialize();
    iren.Start();
  }  
}
