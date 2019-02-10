import vtk.vtkNativeLibrary;
import vtk.vtkDiskSource;
import vtk.vtkFeatureEdges;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;

  
public class BoundaryEdges
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
    double Bgcolor[] = new double[4]; 

    colors.GetColor("DarkSeaGreen", Bgcolor);

    vtkDiskSource diskSource = new vtkDiskSource();
    diskSource.Update();
    vtkFeatureEdges featureEdges = new vtkFeatureEdges();
    featureEdges.SetInputConnection(diskSource.GetOutputPort());
    featureEdges.BoundaryEdgesOn();
    featureEdges.FeatureEdgesOff();
    featureEdges.ManifoldEdgesOff();
    featureEdges.NonManifoldEdgesOff();
    featureEdges.Update();

    //Visualize the Actor
    vtkPolyDataMapper edgeMapper = new vtkPolyDataMapper();
    edgeMapper.SetInputConnection(featureEdges.GetOutputPort());
    vtkActor edgeActor = new vtkActor();
    edgeActor.SetMapper(edgeMapper);

    vtkPolyDataMapper diskMapper = new vtkPolyDataMapper();
    diskMapper.SetInputConnection(diskSource.GetOutputPort());
    vtkActor diskActor = new vtkActor();
    diskActor.SetMapper(diskMapper);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    ren.AddActor(diskActor);
    ren.AddActor(edgeActor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  
  }
}
