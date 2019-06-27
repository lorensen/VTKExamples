import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkImageData;
import vtk.vtkCellCenters;
import vtk.vtkDataSetMapper;


public class CellCenters 
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
    // Create an image data
    vtkImageData imageData = new vtkImageData();

    // Specify the size of the image data
    imageData.SetDimensions(3,3,2);
    imageData.SetSpacing(1.0, 1.0, 1.0);
    imageData.SetOrigin(0.0, 0.0, 0.0);

    vtkCellCenters cellCentersFilter = new vtkCellCenters();
    cellCentersFilter.SetInputData(imageData);
    cellCentersFilter.VertexCellsOn();
    cellCentersFilter.Update();
    
    // Access the cell centers
    for(int i = 0; i < cellCentersFilter.GetOutput().GetNumberOfPoints(); i++)
    {
      double p[] = new double[3];
      cellCentersFilter.GetOutput().GetPoint(i, p);
      System.out.print("Point " + " " + i + " : " + " " +  p[0] + " , " + p[1] + " , " + p[2] + "\n"); 
    }
    
    // Display the cell centers
    vtkDataSetMapper centerMapper = new vtkDataSetMapper();
    centerMapper.SetInputConnection(cellCentersFilter.GetOutputPort());
    
    vtkActor centerActor = new vtkActor();
    centerActor.SetMapper(centerMapper);

    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputData(imageData);

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetRepresentationToWireframe();

    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.AddActor(actor);
    ren.AddActor(centerActor);
	    
    renWin.SetSize(300, 300);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();
  }
}
