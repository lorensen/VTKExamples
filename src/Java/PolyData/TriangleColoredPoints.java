import vtk.vtkRenderWindow;
import vtk.vtkActor;
import vtk.vtkPoints;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderer;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkPolyData;
import vtk.vtkTriangle;
import vtk.vtkUnsignedCharArray;
import vtk.vtkCellArray;
import vtk.vtkNamedColors;

public class TriangleColoredPoints 
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

    colors.GetColor("Black", Bgcolor);

    // Setup points
    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0.0, 0.0, 0.0);
    Points.InsertNextPoint(1.0, 0.0, 0.0);
    Points.InsertNextPoint(0.0, 1.0, 0.0);

    //Setup the colors array
    vtkUnsignedCharArray Colors = new vtkUnsignedCharArray();
    Colors.SetNumberOfComponents(3);
    Colors.SetName("Colors");
   
   //Add the three colors we have created to the array
    Colors.InsertNextTuple3(255,0, 0);
    Colors.InsertNextTuple3(0, 255, 0);
    Colors.InsertNextTuple3(0, 0, 255);

    //Create a triangle
    vtkCellArray Triangles = new vtkCellArray();
    vtkTriangle Triangle = new vtkTriangle();
    Triangle.GetPointIds().SetId(0, 0);
    Triangle.GetPointIds().SetId(1, 1);
    Triangle.GetPointIds().SetId(2, 2);
    Triangles.InsertNextCell(Triangle);

    //Create a polydata object and add everything to it
    vtkPolyData PolyData = new vtkPolyData();
    PolyData.SetPoints(Points);
    PolyData.SetPolys(Triangles);
    PolyData.GetPointData().SetScalars(Colors);

    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(PolyData);

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);

    // Visualize the actor
    ren.AddActor(Actor);
    ren.SetBackground(Bgcolor);

    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
