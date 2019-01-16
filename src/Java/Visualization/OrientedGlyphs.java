import vtk.vtkActor;
import vtk.vtkSphereSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkArrowSource;
import vtk.vtkGlyph3D;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkNamedColors;

public class OrientedGlyphs
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
    
    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Teal", actorColor);
    colors.GetColor("Khaki", Bgcolor);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();
    Sphere.Update();

    //Create a Mapper and Actor
    vtkPolyData Input = new vtkPolyData();
    Input.ShallowCopy(Sphere.GetOutput());

    vtkArrowSource ArrowSource = new vtkArrowSource();

    vtkGlyph3D Glyph3D = new vtkGlyph3D();
    Glyph3D.SetSourceConnection(ArrowSource.GetOutputPort());
    Glyph3D.SetInputData(Input);
    Glyph3D.SetScaleFactor(0.2);
    Glyph3D.Update();

    // Visualize
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(Glyph3D.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(actorColor);

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.Render();
    iren.Start();

  }		  
}
