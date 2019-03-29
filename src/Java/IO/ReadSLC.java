import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSLCReader;
import vtk.vtkContourFilter;
import vtk.vtkOutlineFilter;
import vtk.vtkExtractVOI;


public class  ReadSLC 
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
      System.err.println("Usage: java -classpath ... Filename(.slc) e.g vw_knee.slc");
      return;
    }
    String inputFilename = args[0];
    
    double isoValue = 72.0;
    if (args.length != 2)
    {
      isoValue = 72.0;
    }
    else
    {
      isoValue = Integer.valueOf(args[1]);
    }
    
    vtkNamedColors colors = new vtkNamedColors();

    //For Actor Color
    double actorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Ivory", actorColor);
    colors.GetColor("SlateGray", Bgcolor);
    
    //Using vtkSLCReader to read Volumetric file format(<filename.slc>)
    vtkSLCReader reader = new vtkSLCReader();
    reader.SetFileName(inputFilename);
    reader.Update();

    // Implementing Marching Cubes Algorithm to create the surface using vtkContourFilter object 
    vtkContourFilter cFilter = new vtkContourFilter();
    cFilter.SetInputConnection(reader.GetOutputPort());
    
    // Change the range(2nd and 3rd Paramater) based on your
    // requirement. recomended value for 1st parameter is above 1
    // cFilter.GenerateValues(5, 80.0, 100.0); 
    cFilter.SetValue(0, isoValue);
    cFilter.Update();

    //Adding the outliner using vtkOutlineFilter object
    vtkOutlineFilter outliner = new vtkOutlineFilter();
    outliner.SetInputConnection(reader.GetOutputPort());
    outliner.Update();

    // Visualize
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(cFilter.GetOutputPort());
    mapper.SetScalarVisibility(0);
    
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);
    actor.GetProperty().SetDiffuse(.8);
    actor.GetProperty().SetDiffuseColor(actorColor);
    actor.GetProperty().SetSpecular(.8);
    actor.GetProperty().SetSpecularPower(120.0);
    
    //extractVOI is used to fix the problem of subsampling of data and reduce slow interaction and increase loading speed
    vtkExtractVOI extractVOI = new vtkExtractVOI();
    extractVOI.SetInputConnection(reader.GetOutputPort());
    extractVOI.SetSampleRate(2, 2, 2);
    extractVOI.Update();
	
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualise
    ren.AddActor(actor);
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(640, 512);
    renWin.Render();
    
    iren.Initialize();
    iren.Start();
  }
}
