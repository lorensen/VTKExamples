import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPoints;
import vtk.vtkTetra;
import vtk.vtkCellArray;
import vtk.vtkUnstructuredGrid;
import vtk.vtkXMLUnstructuredGridWriter;
import vtk.vtkXMLUnstructuredGridReader;
import vtk.vtkDataSetMapper;

public class  WriteVTU
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
      System.err.println("Usage: java -classpath ... Filename(.vtu) e.g tetra_test.vtu");
      return;
    }
    String Filename = args[0];
    int VTK_TETRA = 10;
    
    vtkNamedColors colors = new vtkNamedColors();

    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Seagreen", Bgcolor);
    
    vtkPoints points = new vtkPoints();
    points.InsertNextPoint(0, 0, 0);
    points.InsertNextPoint(1, 0, 0);
    points.InsertNextPoint(1, 1, 0);
    points.InsertNextPoint(0, 1, 1);
    
    vtkTetra tetra = new vtkTetra();
    
    tetra.GetPointIds().SetId(0, 0);
    tetra.GetPointIds().SetId(1, 1);
    tetra.GetPointIds().SetId(2, 2);
    tetra.GetPointIds().SetId(3, 3);
    
    vtkCellArray cellArray = new vtkCellArray();
    cellArray.InsertNextCell(tetra);
    
    vtkUnstructuredGrid unstructuredGrid = new vtkUnstructuredGrid();
    unstructuredGrid.SetPoints(points);
    unstructuredGrid.SetCells(VTK_TETRA, cellArray);
    
    // Write file
    vtkXMLUnstructuredGridWriter writer = new vtkXMLUnstructuredGridWriter();
    writer.SetFileName(Filename);
    writer.SetInputData(unstructuredGrid);
    writer.Write();

    // Read and display file for verification that it was written correclty
    vtkXMLUnstructuredGridReader reader = new vtkXMLUnstructuredGridReader();
    reader.SetFileName(Filename);
    reader.Update();

    vtkDataSetMapper mapper = new vtkDataSetMapper();
    mapper.SetInputConnection(reader.GetOutputPort()); 
        
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
 
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(actor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();
  }
}
