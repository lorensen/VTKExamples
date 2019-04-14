import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkPlatonicSolidSource;
import vtk.vtkPolyDataNormals;
import vtk.vtkTextProperty;
import vtk.vtkCubeAxesActor2D;
import vtk.vtkLODActor;
import vtk.vtkOutlineFilter;


public class CubeAxesActor2D 
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
  
  public static void main(String s[]) 
  {
    vtkNamedColors colors = new vtkNamedColors();

    //For icosahedron_actor Color
    double icosahedronActorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Magenta", icosahedronActorColor);
    colors.GetColor("DarkSlateBlue", Bgcolor);
    
    vtkPlatonicSolidSource icosahedron = new vtkPlatonicSolidSource();
    icosahedron.SetSolidTypeToIcosahedron();

    // Create a vtkPolyDataNormals filter to calculate the normals of the data set.
    vtkPolyDataNormals normals = new vtkPolyDataNormals()	;
    normals.SetInputConnection(icosahedron.GetOutputPort());

    // Set up the associated mapper and actor.
    vtkPolyDataMapper icosahedron_mapper = new vtkPolyDataMapper();
    icosahedron_mapper.SetInputConnection(normals.GetOutputPort());
    icosahedron_mapper.ScalarVisibilityOff();

    vtkLODActor icosahedron_actor = new vtkLODActor();
    icosahedron_actor.SetMapper(icosahedron_mapper);
    icosahedron_actor.GetProperty().SetColor(icosahedronActorColor);
    
    // Create a vtkOutlineFilter to draw the bounding box of the data set.
    // Also create the associated mapper and actor.
    vtkOutlineFilter outline = new vtkOutlineFilter();
    outline.SetInputConnection(normals.GetOutputPort());

    vtkPolyDataMapper map_outline = new vtkPolyDataMapper();
    map_outline.SetInputConnection(outline.GetOutputPort());

    vtkActor outline_actor = new vtkActor();
    outline_actor.SetMapper(map_outline);
    outline_actor.GetProperty().SetColor(0., 0., 0.);

    // Create the Renderers.  Assign them the appropriate viewport
    // coordinates, active camera, and light.

    vtkRenderer ren = new vtkRenderer();
    ren.SetViewport(0, 0, 0.5, 1.0);
    
    vtkRenderer ren2 = new vtkRenderer();
    ren2.SetViewport(0.5, 0,1.0, 1.0);;
    ren2.SetActiveCamera(ren.GetActiveCamera());    
    
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    renWin.AddRenderer(ren2);
    renWin.SetWindowName("VTK - Cube Axes");
    renWin.SetSize(600, 300);
    
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddViewProp(icosahedron_actor);
    ren.AddViewProp(outline_actor);
    ren2.AddViewProp(icosahedron_actor);
    ren2.AddViewProp(outline_actor);
	
    ren.SetBackground(Bgcolor);
    ren2.SetBackground(Bgcolor);
    
    // Create a text property for both cube axes
    vtkTextProperty tprop = new vtkTextProperty();
    tprop.SetColor(1, 1, 1);
    tprop.ShadowOn();
    tprop.SetFontSize(20);
    
    //  Create a vtkCubeAxesActor2D.  Use the outer edges of the bounding box to
    // draw the axes.  Add the actor to the renderer.
    vtkCubeAxesActor2D axes = new vtkCubeAxesActor2D();
    axes.SetInputConnection(normals.GetOutputPort());
    axes.SetCamera(ren.GetActiveCamera());
    axes.SetLabelFormat("%6.4g");
    axes.SetFlyModeToOuterEdges();
    axes.SetAxisTitleTextProperty(tprop);
    axes.SetAxisLabelTextProperty(tprop);
    ren.AddViewProp(axes);
        
    //  Create a vtkCubeAxesActor2D.  Use the closest vertex to the camera to
    // determine where to draw the axes.  Add the actor to the renderer.
    vtkCubeAxesActor2D axes2 = new vtkCubeAxesActor2D();
    axes2.SetViewProp(icosahedron_actor);
    axes2.SetCamera(ren2.GetActiveCamera());
    axes2.SetLabelFormat("%6.4g");
    axes2.SetFlyModeToClosestTriad();
    axes2.ScalingOff();
    axes2.SetAxisTitleTextProperty(tprop);
    axes2.SetAxisLabelTextProperty(tprop);
    ren2.AddViewProp(axes2);
    
    ren.ResetCamera();
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
