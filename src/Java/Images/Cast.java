import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageMandelbrotSource;
import vtk.vtkImageCast;
import vtk.vtkImageActor;
import vtk.vtkInteractorStyleImage;

public class Cast
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
    //Create a float image
    vtkImageMandelbrotSource source = new vtkImageMandelbrotSource();
    source.Update();

    System.out.println(source.GetOutput().GetScalarTypeAsString());

    vtkImageCast castFilter = new vtkImageCast();
    castFilter.SetInputConnection(source.GetOutputPort());
    castFilter.SetOutputScalarTypeToUnsignedChar();
    castFilter.Update();

    //Create an actor
    vtkImageActor actor = new vtkImageActor();
    actor.GetMapper().SetInputConnection(castFilter.GetOutputPort());

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    ren.AddActor(actor);
    ren.ResetCamera();

    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);

    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    vtkInteractorStyleImage style = new vtkInteractorStyleImage();
    iren.SetInteractorStyle(style);
    iren.SetRenderWindow(renWin);
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
