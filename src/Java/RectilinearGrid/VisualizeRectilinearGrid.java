import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkRectilinearGrid;
import vtk.vtkDoubleArray;
import vtk.vtkShrinkFilter;
import vtk.vtkDataSetMapper;

public class VisualizeRectilinearGrid 
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
    // Create a grid
    vtkRectilinearGrid grid = new vtkRectilinearGrid();

    grid.SetDimensions(2,3,2);

    vtkDoubleArray xArray = new vtkDoubleArray();
    xArray.InsertNextValue(0.0);
    xArray.InsertNextValue(2.0);

    vtkDoubleArray yArray = new vtkDoubleArray();
    yArray.InsertNextValue(0.0);
    yArray.InsertNextValue(1.0);
    yArray.InsertNextValue(2.0);

    vtkDoubleArray zArray = new vtkDoubleArray();
    zArray.InsertNextValue(0.0);
    zArray.InsertNextValue(5.0);

    grid.SetXCoordinates(xArray);
    grid.SetYCoordinates(yArray);
    grid.SetZCoordinates(zArray);

    vtkShrinkFilter shrinkFilter = new vtkShrinkFilter();
    shrinkFilter.SetInputData(grid);
    shrinkFilter.SetShrinkFactor(.8);

    // Create a mapper and actor
    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputConnection(shrinkFilter.GetOutputPort());

    vtkActor actor = new vtkActor();
    
    actor.SetMapper(mapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.AddActor(actor);
	
    renWin.SetSize(300, 300);
    renWin.Render();
	
    iren.Initialize();
    iren.Start();
  }
}
