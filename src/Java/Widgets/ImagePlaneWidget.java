import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkActor;
import vtk.vtkPolyDataMapper;
import vtk.vtkInteractorStyleTrackballCamera;
import vtk.vtkImagePlaneWidget;

public class ImagePlaneWidget
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
    
    vtkInteractorStyleTrackballCamera style = new vtkInteractorStyleTrackballCamera();
    iren.SetInteractorStyle( style );

    vtkImagePlaneWidget planeWidget = new vtkImagePlaneWidget();
    planeWidget.SetInteractor(iren);
    planeWidget.TextureVisibilityOff();

    double origin[] = new double[]{0, 1, 0};
    planeWidget.SetOrigin(origin);
    planeWidget.UpdatePlacement();

    ren.AddActor(actor);
    
    renWin.SetSize(300,300);
    renWin.Render();
    planeWidget.On();

    iren.Initialize();
    iren.Start();
  }
}
