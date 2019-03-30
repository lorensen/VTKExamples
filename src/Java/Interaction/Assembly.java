import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkCubeSource;
import vtk.vtkAssembly;
import vtk.vtkTransform;
import vtk.vtkPropCollection;


public class Assembly 
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

    //For sphereActor Color
    double sphereActorColor[] = new double[4];
    //For cubeActor Color
    double cubeActorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Banana", sphereActorColor);
    colors.GetColor("Tomato", cubeActorColor);
    colors.GetColor("SlateGray", Bgcolor);
    
    // Create a sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.Update();

    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInputConnection(sphereSource.GetOutputPort());
    
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper(sphereMapper);
    sphereActor.GetProperty().SetColor(sphereActorColor);
    
    // Create a cube
    vtkCubeSource cubeSource = new vtkCubeSource();
    cubeSource.SetCenter(5.0, 0.0, 0.0);
    cubeSource.Update();

    vtkPolyDataMapper cubeMapper = new vtkPolyDataMapper();
    cubeMapper.SetInputConnection(cubeSource.GetOutputPort());
    
    vtkActor cubeActor = new vtkActor();
    cubeActor.SetMapper(cubeMapper);
    cubeActor.GetProperty().SetColor(cubeActorColor);
    
    // Combine the sphere and cube into an assembly
    vtkAssembly assembly = new vtkAssembly();
    assembly.AddPart(sphereActor);
    assembly.AddPart(cubeActor);
    
    // Apply a transform to the whole assembly
    vtkTransform transform = new vtkTransform();
    transform.PostMultiply(); //this is the key line
    transform.Translate(5.0, 0, 0);

    assembly.SetUserTransform(transform);

    // Extract each actor from the assembly and change its opacity
    vtkPropCollection collection = new vtkPropCollection();
	
    assembly.GetActors(collection);
    collection.InitTraversal();
    cubeActor.GetProperty().SetOpacity(0.5);
    sphereActor.GetProperty().SetOpacity(0.5);
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.AddActor(assembly);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
