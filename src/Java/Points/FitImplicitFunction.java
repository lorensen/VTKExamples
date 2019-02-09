import vtk.vtkNativeLibrary;
import vtk.vtkMath;
import vtk.vtkNamedColors;
import vtk.vtkBoundedPointSource;
import vtk.vtkSphere;
import vtk.vtkFitImplicitFunction;
import vtk.vtkSphereSource;
import vtk.vtkGlyph3D;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;

   
public class FitImplicitFunction 
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
    
    //For Renderer Background Color
    double glyph3DActorcolor[] = new double[4];
    
    //For Renderer Background Color
    double Bgcolor[] = new double[4];

    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Gray",Bgcolor);
    
    //Change Color Name to Use your own Color for Actor
    Color.GetColor("Yellow",glyph3DActorcolor);
    
    vtkMath RS = new vtkMath();
    RS.RandomSeed(4355412);
    double radius = 1.0;
    
    vtkBoundedPointSource points = new vtkBoundedPointSource();
    points.SetNumberOfPoints(1000000);
    points.SetBounds(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    
    vtkSphere sphere = new vtkSphere();
    sphere.SetRadius(radius);

    vtkFitImplicitFunction fit = new vtkFitImplicitFunction();
    fit.SetInputConnection(points.GetOutputPort());
    fit.SetImplicitFunction(sphere);
    fit.SetThreshold(.01);
    fit.Update();
    System.out.println(fit.GetOutput().GetNumberOfPoints() + " " + "out of" + " " + points.GetNumberOfPoints() + " " + "points are within" + " " + fit.GetThreshold() + " " + "of the implicit function");  

    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetRadius(radius * .05);
    
    vtkGlyph3D glyph3D = new vtkGlyph3D();
    glyph3D.SetInputConnection(fit.GetOutputPort());
    glyph3D.SetSourceConnection(sphereSource.GetOutputPort());
    glyph3D.ScalingOff();
    glyph3D.Update();
 
    vtkPolyDataMapper glyph3DMapper = new vtkPolyDataMapper();
    glyph3DMapper.SetInputConnection(glyph3D.GetOutputPort());

    vtkActor glyph3DActor = new vtkActor();
    glyph3DActor.SetMapper(glyph3DMapper);
    glyph3DActor.GetProperty().SetColor(glyph3DActorcolor);
    
    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(glyph3DActor);
    
    ren.ResetCamera();
    ren.GetActiveCamera().Azimuth(120);
    ren.GetActiveCamera().Elevation(30);
    ren.GetActiveCamera().Dolly(1.0);
    ren.ResetCameraClippingRange();
    
    ren.SetBackground(Bgcolor);
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
