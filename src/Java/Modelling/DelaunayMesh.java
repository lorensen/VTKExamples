import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkPoints;
import vtk.vtkMinimalStandardRandomSequence;
import vtk.vtkPolyData;
import vtk.vtkDelaunay2D;
import vtk.vtkExtractEdges;
import vtk.vtkTubeFilter;
import vtk.vtkGlyph3D;
import vtk.vtkSphereSource;

public class DelaunayMesh 
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

    //For mesh Actor Color
    double meshActorColor[] = new double[4];
    //For edge Actor Color
    double edgeActorColor[] = new double[4];
    //For ball Actor Color
    double ballActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
         
    //Change Color Name to Use your own Color for Change mesh Actor Color
    Color.GetColor("MidnightBlue",meshActorColor);
    //Change Color Name to Use your own Color for Change edge Actor Color
    Color.GetColor("Peacock",edgeActorColor);
    //Change Color Name to Use your own Color for Change ball Actor Color
    Color.GetColor("hot_pink",ballActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("AliceBlue",BgColor);
    
    //Generate some "random" points.
    vtkPoints points = new vtkPoints();
    vtkMinimalStandardRandomSequence randomSequence = new vtkMinimalStandardRandomSequence();
    randomSequence.SetSeed(1);
    double p1;
    double p2;
    for (int i = 0; i < 50; ++i)
    {
      p1 = randomSequence.GetValue();
      randomSequence.Next();
      p2 = randomSequence.GetValue();
      randomSequence.Next();
      points.InsertPoint(i, p1, p2, 0.0);
    }
    
    //Create a polydata with the points we just created.
    vtkPolyData profile = new vtkPolyData();
    profile.SetPoints(points);

    //Perform a 2D Delaunay triangulation on them.
    vtkDelaunay2D delny = new vtkDelaunay2D();
    delny.SetInputData(profile);
    delny.SetTolerance(0.001);
    vtkPolyDataMapper mapMesh = new vtkPolyDataMapper();
    mapMesh.SetInputConnection(delny.GetOutputPort());
    
    vtkActor meshActor = new vtkActor();
    meshActor.SetMapper(mapMesh);
    meshActor.GetProperty().SetColor(meshActorColor);
    
    // We will now create a nice looking mesh by wrapping the edges in tubes,
    // and putting fat spheres at the points.
    vtkExtractEdges extract = new vtkExtractEdges();
    extract.SetInputConnection(delny.GetOutputPort());
    
    vtkTubeFilter tubes = new vtkTubeFilter();
    tubes.SetInputConnection(extract.GetOutputPort());
    tubes.SetRadius(0.01);
    tubes.SetNumberOfSides(6);
    
    vtkPolyDataMapper mapEdges = new vtkPolyDataMapper();
    mapEdges.SetInputConnection(tubes.GetOutputPort());
    
    vtkActor edgeActor = new vtkActor();
    edgeActor.SetMapper(mapEdges);
    edgeActor.GetProperty().SetColor(edgeActorColor);
    edgeActor.GetProperty().SetSpecularColor(1, 1, 1);
    edgeActor.GetProperty().SetSpecular(0.3);
    edgeActor.GetProperty().SetSpecularPower(20);
    edgeActor.GetProperty().SetAmbient(0.2);
    edgeActor.GetProperty().SetDiffuse(0.8);
    
    vtkSphereSource ball = new vtkSphereSource();
    ball.SetRadius(0.025);
    ball.SetThetaResolution(12);
    ball.SetPhiResolution(12);
    
    vtkGlyph3D balls = new vtkGlyph3D();
    balls.SetInputConnection(delny.GetOutputPort());
    balls.SetSourceConnection(ball.GetOutputPort());
    
    vtkPolyDataMapper mapBalls = new vtkPolyDataMapper();
    mapBalls.SetInputConnection(balls.GetOutputPort());
    
    vtkActor ballActor = new vtkActor();
    ballActor.SetMapper(mapBalls);
    ballActor.GetProperty().SetColor(ballActorColor);
    ballActor.GetProperty().SetSpecularColor(1, 1, 1);
    ballActor.GetProperty().SetSpecular(0.3);
    ballActor.GetProperty().SetSpecularPower(20);
    ballActor.GetProperty().SetAmbient(0.2);
    ballActor.GetProperty().SetDiffuse(0.8);
  
    //  Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(ballActor);
    ren.AddActor(edgeActor);
    
    ren.ResetCamera();
    ren.GetActiveCamera().Zoom(1.3);
    ren.SetBackground(BgColor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
