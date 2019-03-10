import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageCanvasSource2D;
import vtk.vtkTIFFWriter;
import vtk.vtkTIFFReader;
import vtk.vtkImageActor;
import vtk.vtkInteractorStyleImage;

public class WriteTIFF
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

    //parse command line arguments
    if (args.length != 1) 
    {
      System.err.println("Usage: java -classpath ... Filename(.tif) e.g OutputFile.tif");
      return;
    }
    String Filename = args[0];
     
    vtkImageCanvasSource2D imageSource = new vtkImageCanvasSource2D();
    imageSource.SetScalarTypeToUnsignedChar();
    imageSource.SetExtent(0,9,0,9,0,0);
    imageSource.SetNumberOfScalarComponents(3);
    imageSource.SetDrawColor(0, 0, 0, 0);
    imageSource.FillBox(0,9,0,9);
    imageSource.SetDrawColor(255, 0, 0, 0);
    imageSource.FillBox(5,7,5,7);
    imageSource.Update();
    
    vtkTIFFWriter tiffWriter = new vtkTIFFWriter();
    tiffWriter.SetFileName(Filename);
    tiffWriter.SetInputConnection(imageSource.GetOutputPort());
    tiffWriter.Write();
    
    //Read and display for verification
    vtkTIFFReader reader = new vtkTIFFReader();
    reader.SetFileName(Filename);
    reader.Update();
    
    vtkImageActor actor = new vtkImageActor();
    actor.GetMapper().SetInputConnection(reader.GetOutputPort());

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    vtkInteractorStyleImage style = new vtkInteractorStyleImage();
    iren.SetInteractorStyle(style);

    ren.AddActor(actor);

    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
