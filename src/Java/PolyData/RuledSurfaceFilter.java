import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPoints;
import vtk.vtkLine;
import vtk.vtkCellArray;
import vtk.vtkRuledSurfaceFilter;
import vtk.vtkPolyData;

public class RuledSurfaceFilter 
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
   //For Actor Color
   double actorColor[] = new double[4];
   //Renderer Background Color
   double Bgcolor[] = new double[4];

   colors.GetColor("Khaki", actorColor);
   colors.GetColor("LightSlateGray", Bgcolor);
   // Create first line.
   vtkPoints points = new vtkPoints();
   points.InsertPoint(0, 0, 0, 1);
   points.InsertPoint(1, 1, 0, 0);
   points.InsertPoint(2, 0, 1, 0);
   points.InsertPoint(3, 1, 1, 1);
   
   vtkLine line1 = new vtkLine();
   line1.GetPointIds().SetId(0, 0);
   line1.GetPointIds().SetId(1, 1);
   
   vtkLine line2 = new vtkLine();
   line2.GetPointIds().SetId(0, 2);
   line2.GetPointIds().SetId(1, 3);
   
   vtkCellArray lines = new vtkCellArray();
   lines.InsertNextCell(line1);
   lines.InsertNextCell(line2);
   
   vtkPolyData polydata = new vtkPolyData();
   polydata.SetPoints(points);
   polydata.SetLines(lines);
   
   vtkRuledSurfaceFilter ruledSurfaceFilter = new vtkRuledSurfaceFilter();
   ruledSurfaceFilter.SetInputData(polydata);
   ruledSurfaceFilter.SetResolution(21, 21);
   ruledSurfaceFilter.SetRuledModeToResample();
   
   // Create the renderer, render window and interactor.
   vtkRenderer ren = new vtkRenderer();
   vtkRenderWindow renWin = new vtkRenderWindow();
   renWin.AddRenderer(ren);
   vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
   iren.SetRenderWindow(renWin);
   
   vtkPolyDataMapper mapper = new vtkPolyDataMapper();
   mapper.SetInputConnection(ruledSurfaceFilter.GetOutputPort());
   
   vtkActor actor = new vtkActor();
   actor.SetMapper(mapper);
   actor.GetProperty().SetColor(actorColor);
   
   // Add the actors to the renderer, set the background and size
   ren.AddActor(actor);
   
   ren.ResetCamera();
   ren.GetActiveCamera().Azimuth(60);
   ren.GetActiveCamera().Elevation(60);
   ren.GetActiveCamera().Dolly(1.2);
   ren.ResetCameraClippingRange();
	
   ren.SetBackground(Bgcolor);
    
   renWin.SetSize(400, 400);
   renWin.Render();

   iren.Initialize();
   iren.Start();
  }
}
