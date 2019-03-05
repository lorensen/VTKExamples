import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkStructuredGrid;
import vtk.vtkPoints;
import vtk.vtkStructuredGridOutlineFilter;
import vtk.vtkActor;
import vtk.vtkPolyDataMapper;

public class StructuredGridOutline 
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
  
    //  Create a grid
    vtkStructuredGrid structuredGrid = new vtkStructuredGrid();
    
    vtkPoints points = new vtkPoints();
    int numi = 2;
    int numj = 3;
    int numk = 2;
    
    for(int k = 0; k < numk; k++)
    {
      for(int j = 0; j < numj; j++)
      {
        for(int i = 0; i < numi; i++)
        {
          points.InsertNextPoint(i, j, k);
        }
      }
    }
    
    //specify the dimensions of the grid
    structuredGrid.SetDimensions(numi, numj, numk);
    structuredGrid.SetPoints(points);
    
    System.out.println("There are " + " " + structuredGrid.GetNumberOfPoints() + " " + "points.");
    System.out.println("There are " + " " + structuredGrid.GetNumberOfCells() + " " + "cells.");
  
    vtkStructuredGridOutlineFilter outlineFilter = new vtkStructuredGridOutlineFilter();
    outlineFilter.SetInputData(structuredGrid);
    outlineFilter.Update();
    
    // Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(outlineFilter.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(actor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
