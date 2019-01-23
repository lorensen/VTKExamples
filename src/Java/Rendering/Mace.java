import vtk.vtkActor;
import vtk.vtkConeSource;
import vtk.vtkGlyph3D;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
    

public class Mace 
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
    double Bgcolor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("DarkSeaGreen",Bgcolor);

    //Create a Sphere
    vtkSphereSource Sphere = new vtkSphereSource();

    Sphere.SetPhiResolution(8);
    Sphere.SetThetaResolution(8);

    //Create a Mapper and Actor for Sphere
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(Sphere.GetOutputPort());

    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);

    //create a Cone
    vtkConeSource Cone = new vtkConeSource();
    Cone.SetResolution(6);

    vtkGlyph3D Glyph = new vtkGlyph3D();
    Glyph.SetInputConnection(Sphere.GetOutputPort());
    Glyph.SetSourceConnection(Cone.GetOutputPort());

    Glyph.SetVectorModeToUseNormal();
    Glyph.SetScaleModeToScaleByVector();
    Glyph.SetScaleFactor(0.25);

    vtkPolyDataMapper spikeMapper = new vtkPolyDataMapper();
    spikeMapper.SetInputConnection(Glyph.GetOutputPort());

    vtkActor spikeActor = new vtkActor();
    spikeActor.SetMapper(spikeMapper);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    ren.AddActor(spikeActor);
    ren.AddActor(sphereActor);

    ren.SetBackground(Bgcolor);
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
