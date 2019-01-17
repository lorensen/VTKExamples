import vtk.vtkRenderWindow;
import vtk.vtkNativeLibrary;
import vtk.vtkNamedColors;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkDistanceWidget;


public class DistanceWidget 
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

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("DimGray", Bgcolor);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    vtkDistanceWidget DistanceWidget = new vtkDistanceWidget();
    DistanceWidget.SetInteractor(iren);
    DistanceWidget.CreateDefaultRepresentation();

    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();
    DistanceWidget.On();
    iren.Initialize();
    iren.Start();
    
  }
}
