import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkVertexGlyphFilter;
import vtk.vtkUnsignedCharArray;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;

public class ColoredPoints 
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
  // ----------------------------------------------------------------

  public static void main(String s[]) 
  {

    vtkNamedColors colors = new vtkNamedColors();
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Snow", Bgcolor);


    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0.0, 0.0, 0.0);
    Points.InsertNextPoint(1.0, 0.0, 0.0);
    Points.InsertNextPoint(0.0, 1.0, 0.0);


    vtkPolyData PointsPolydata = new vtkPolyData();
    PointsPolydata.SetPoints(Points);

    vtkVertexGlyphFilter VertexFilter = new vtkVertexGlyphFilter();
    VertexFilter.SetInputData(PointsPolydata);
    VertexFilter.Update();

    vtkPolyData Polydata = new vtkPolyData();
    Polydata.ShallowCopy(VertexFilter.GetOutput());

    vtkUnsignedCharArray Colors = new vtkUnsignedCharArray();
    Colors.SetNumberOfComponents(3);
    Colors.SetName("Colors");
    Colors.InsertNextTuple3(0,139,0);
    Colors.InsertNextTuple3(139,0, 0);
    Colors.InsertNextTuple3(0, 0,139);

    Polydata.GetPointData().SetScalars(Colors);

    //Visualize
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(Polydata);

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetPointSize(15);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualise the Actor
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
