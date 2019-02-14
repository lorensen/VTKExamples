import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkRectilinearGrid;
import vtk.vtkDoubleArray;
import vtk.vtkDataSetMapper;
import vtk.vtkActor;

public class RectilinearGrid
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
    double Bgcolor[] = new double[] {0.3, 0.6, 0.3}; 
    colors.SetColor("Bgcolor", Bgcolor);
    
    //Create a grid
    vtkRectilinearGrid grid = new vtkRectilinearGrid();

    grid.SetDimensions(2,3,1);

    vtkDoubleArray xArray = new vtkDoubleArray();
    xArray.InsertNextValue(0.0);
    xArray.InsertNextValue(2.0);
    
    vtkDoubleArray yArray = new vtkDoubleArray();
    yArray.InsertNextValue(0.0);
    yArray.InsertNextValue(1.0);
    yArray.InsertNextValue(2.0);

    vtkDoubleArray zArray = new vtkDoubleArray();
    zArray.InsertNextValue(0.0);

    grid.SetXCoordinates(xArray);
    grid.SetYCoordinates(yArray);
    grid.SetZCoordinates(zArray);
    
    System.out.println("There are" + " " + grid.GetNumberOfPoints() + " " +  "points."); 
    System.out.println("There are" + " " + grid.GetNumberOfCells() + " " + "cells.");
    
    for(int id = 0; id < grid.GetNumberOfPoints(); id++)
    {
      double p[] = new double[3];
      grid.GetPoint(id, p);
      System.out.println("Point " + " " +  id + " " +  " : (" + " " +  p[0] + " " +  " , " + " " + p[1] + " " +  " , " + " " +  p[2] + " " + ")" );
    }
    
    //Create a mapper and actor
    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputData(grid);

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(actor);
    ren.SetBackground(Bgcolor); // Background color green
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
