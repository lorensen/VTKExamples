import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPoints;
import vtk.vtkCellArray;
import vtk.vtkPolyData;
import vtk.vtkRotationalExtrusionFilter;
import vtk.vtkPolyDataMapper;
import vtk.vtkActor;
import vtk.vtkStripper;
import vtk.vtkTubeFilter;

    
public class Bottle
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

  //Bottle Actor Color
  double Bottlecolor[] = new double[4]; 
  colors.GetColor("Mint", Bottlecolor);
  //ProfileActor Color
  double ProfileActorcolor[] = new double[4]; 
  colors.GetColor("Tomato", ProfileActorcolor);
  //Renderer Background Color
  double Bgcolor[] = new double[4]; 
  colors.GetColor("Burlywood", Bgcolor);

  //Create the renderer, render window and interactor.
  vtkRenderer ren = new vtkRenderer();
  vtkRenderWindow renWin = new vtkRenderWindow();
  renWin.AddRenderer(ren);
  vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
  iren.SetRenderWindow(renWin);

  //create bottle profile

  vtkPoints points = new vtkPoints();
  points.InsertPoint(0, 0.01, 0.0, 0.0);
  points.InsertPoint(1, 1.5, 0.0, 0.0);
  points.InsertPoint(2, 1.5, 0.0, 3.5);
  points.InsertPoint(3, 1.25, 0.0, 3.75);
  points.InsertPoint(4, 0.75, 0.0, 4.00);
  points.InsertPoint(5, 0.6, 0.0, 4.35);
  points.InsertPoint(6, 0.7, 0.0, 4.65);
  points.InsertPoint(7, 1.0, 0.0, 4.75);
  points.InsertPoint(8, 1.0, 0.0, 5.0);
  points.InsertPoint(9, 0.2, 0.0, 5.0);

  vtkCellArray lines = new vtkCellArray();
  lines.InsertNextCell(10);//number of points
  lines.InsertCellPoint(0);
  lines.InsertCellPoint(1);
  lines.InsertCellPoint(2);
  lines.InsertCellPoint(3);
  lines.InsertCellPoint(4);
  lines.InsertCellPoint(5);
  lines.InsertCellPoint(6);
  lines.InsertCellPoint(7);
  lines.InsertCellPoint(8);
  lines.InsertCellPoint(9);

  vtkPolyData profile = new vtkPolyData();
  profile.SetPoints(points);
  profile.SetLines(lines);

  //extrude profile to make bottle

  vtkRotationalExtrusionFilter extrude = new vtkRotationalExtrusionFilter();
  extrude.SetInputData(profile);
  extrude.SetResolution(60);

  vtkPolyDataMapper map = new vtkPolyDataMapper();
  map.SetInputConnection(extrude.GetOutputPort());

  vtkActor bottle = new vtkActor();
  bottle.SetMapper(map);
  bottle.GetProperty().SetColor(Bottlecolor);

  //display the profile
  vtkStripper stripper = new vtkStripper();
  stripper.SetInputData(profile);

  vtkTubeFilter tubes = new vtkTubeFilter();
  tubes.SetInputConnection(stripper.GetOutputPort());
  tubes.SetNumberOfSides(11);
  tubes.SetRadius(.05);

  vtkPolyDataMapper profileMapper = new vtkPolyDataMapper();
  profileMapper.SetInputConnection(tubes.GetOutputPort());

  vtkActor profileActor = new vtkActor();
  profileActor.SetMapper(profileMapper);
  profileActor.GetProperty().SetColor(ProfileActorcolor);

  //Add the actors to the renderer, set the background and size
  ren.AddActor(bottle);
  ren.AddActor(profileActor);
  ren.SetBackground(Bgcolor);

  renWin.SetSize(640,480);
  renWin.Render();

  ren.GetActiveCamera().SetPosition(1, 0, 0);
  ren.GetActiveCamera().SetFocalPoint(0, 0, 0);
  ren.GetActiveCamera().SetViewUp(0, 0, 1);
  ren.ResetCamera();
  ren.GetActiveCamera().Azimuth(30);
  ren.GetActiveCamera().Elevation(30);

  iren.Initialize();
  iren.Start();

 }
}
