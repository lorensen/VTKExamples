import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkConeSource;
import vtk.vtkXMLPolyDataWriter;
import vtk.vtkTransformPolyDataFilter;
import vtk.vtkTransform;
import vtk.vtkXMLPolyDataReader;

public class RotationAroundLine 
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
    if (args.length != 2) 
    {
      System.err.println("Usage: java -classpath ... Filename(.vtp) Filename(.vtp) e.g original.vtp transformed.vtp");
      return;
    }
    String inputFilename = args[0];
    String outputFilename = args[1];
    
    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double leftViewport[] = new double[] {0.0, 0.0, 0.5, 1.0};
    double rightViewport[] = new double[] {0.5, 0.0, 1.0, 1.0};
    
    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Tomato", actorColor);
    colors.GetColor("Turquoise", Bgcolor);
    
    //Create a cone
    vtkConeSource coneSource = new vtkConeSource();

    {
     vtkXMLPolyDataWriter writer = new vtkXMLPolyDataWriter();
     writer.SetInputConnection(coneSource.GetOutputPort());
     writer.SetFileName(inputFilename);
     writer.Write();
    }
    
    vtkTransform transform = new vtkTransform();
    //transform.RotateWXYZ(double angle, double x, double y, double z);
    transform.RotateWXYZ(10, 0, 1, 0);

    vtkTransformPolyDataFilter transformFilter = new vtkTransformPolyDataFilter();
	
    transformFilter.SetTransform(transform);
    transformFilter.SetInputConnection(coneSource.GetOutputPort());
    transformFilter.Update();

    {
     vtkXMLPolyDataWriter writer = new vtkXMLPolyDataWriter();
     writer.SetInputConnection(transformFilter.GetOutputPort());
     writer.SetFileName(outputFilename);
     writer.Write();
    }
    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Original Actor
    vtkXMLPolyDataReader original_reader = new vtkXMLPolyDataReader();
    original_reader.SetFileName(inputFilename);
    original_reader.Update();
    
    vtkPolyDataMapper original_mapper = new vtkPolyDataMapper();
    original_mapper.SetInputConnection(original_reader.GetOutputPort());

    vtkActor original_actor = new vtkActor();
    original_actor.SetMapper(original_mapper);
    
    // Transformed Actor
    vtkXMLPolyDataReader Transformed_reader = new vtkXMLPolyDataReader();
    Transformed_reader.SetFileName(outputFilename);
    Transformed_reader.Update();
    
    vtkPolyDataMapper Transformed_mapper = new vtkPolyDataMapper();
    Transformed_mapper.SetInputConnection(Transformed_reader.GetOutputPort());

    vtkActor Transformed_actor = new vtkActor();
    Transformed_actor.SetMapper(Transformed_mapper);
        
    // Setup both renderers
    vtkRenderer leftRenderer = new vtkRenderer();
    renWin.AddRenderer(leftRenderer);
    leftRenderer.SetViewport(leftViewport);
    leftRenderer.SetBackground(Bgcolor);  

    vtkRenderer rightRenderer = new vtkRenderer();
    renWin.AddRenderer(rightRenderer);
    rightRenderer.SetViewport(rightViewport);
    rightRenderer.SetBackground(Bgcolor);
		
    leftRenderer.AddActor(original_actor);
    rightRenderer.AddActor(Transformed_actor);
    
    leftRenderer.ResetCamera();
    rightRenderer.ResetCamera();
    
    renWin.SetSize(600, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
