import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkPoints;
import vtk.vtkCellArray;
import vtk.vtkPolyData;
import vtk.vtkRotationalExtrusionFilter;
import vtk.vtkPolyDataNormals;



public class Spring
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
    vtkNamedColors Color = new vtkNamedColors(); 

    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("PowderBlue",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Burlywood",BgColor);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    //create spring profile (a circle)
    
    vtkPoints points = new vtkPoints();
    points.InsertPoint(0, 1.0, 0.0, 0.0);
    points.InsertPoint(1, 1.0732, 0.0, -0.1768);
    points.InsertPoint(2, 1.25, 0.0, -0.25);
    points.InsertPoint(3, 1.4268, 0.0, -0.1768);
    points.InsertPoint(4, 1.5, 0.0, 0.00);
    points.InsertPoint(5, 1.4268, 0.0, 0.1768);
    points.InsertPoint(6, 1.25, 0.0, 0.25);
    points.InsertPoint(7, 1.0732, 0.0, 0.1768);

    vtkCellArray poly = new vtkCellArray();
    poly.InsertNextCell(8);//number of points
    poly.InsertCellPoint(0);
    poly.InsertCellPoint(1);
    poly.InsertCellPoint(2);
    poly.InsertCellPoint(3);
    poly.InsertCellPoint(4);
    poly.InsertCellPoint(5);
    poly.InsertCellPoint(6);
    poly.InsertCellPoint(7);

    vtkPolyData profile = new vtkPolyData();
    profile.SetPoints(points);
    profile.SetPolys(poly);
    
    //extrude profile to make spring
    vtkRotationalExtrusionFilter extrude = new vtkRotationalExtrusionFilter();
    extrude.SetInputData(profile);
    extrude.SetResolution(360);
    extrude.SetTranslation(6);
    extrude.SetDeltaRadius(1.0);
    extrude.SetAngle(2160.0);//six revolutions

    vtkPolyDataNormals normals = new vtkPolyDataNormals();
    normals.SetInputConnection(extrude.GetOutputPort());
    normals.SetFeatureAngle(60);

    vtkPolyDataMapper map = new vtkPolyDataMapper();
    map.SetInputConnection(normals.GetOutputPort());

    vtkActor spring = new vtkActor();
    spring.SetMapper(map);
    spring.GetProperty().SetColor(ActorColor);
    spring.GetProperty().SetDiffuse(0.7);
    spring.GetProperty().SetSpecular(0.4);
    spring.GetProperty().SetSpecularPower(20);
    spring.GetProperty().BackfaceCullingOn();
  
    ren.AddActor(spring);
    ren.SetBackground(BgColor);
    
    ren.ResetCamera();
    ren.GetActiveCamera().Azimuth(90);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
