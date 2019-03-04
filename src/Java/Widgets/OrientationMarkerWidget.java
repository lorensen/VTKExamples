import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkXMLPolyDataReader;
import vtk.vtkDataSetMapper;
import vtk.vtkOrientationMarkerWidget;
import vtk.vtkSuperquadricSource;


public class OrientationMarkerWidget 
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
    if (args.length != 1) 
    {
      System.err.println("Usage: java -classpath ... Filename(.vtp) e.g Bunny.vtp");
      return;
    }
    
    vtkNamedColors Color = new vtkNamedColors(); 

    //For icon Actor Color
    double iconActorColor[] = new double[4];
    //For superquadricActor Color
    double superquadricActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
         
    //Change Color Name to Use your own Color for Change icon Actor Color
    Color.GetColor("Silver",iconActorColor);
    //Change Color Name to Use your own Color for Change icon superquadricActorColor
    Color.GetColor("Carrot",superquadricActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("SlateGray",BgColor);
    
    //Read the polydata for the icon
    vtkXMLPolyDataReader reader =  new vtkXMLPolyDataReader();
    reader.SetFileName(args[0]);

    vtkDataSetMapper iconMapper = new vtkDataSetMapper();
    iconMapper.SetInputConnection(reader.GetOutputPort());

    vtkActor iconActor = new vtkActor();
    iconActor.SetMapper(iconMapper);
    iconActor.GetProperty().SetColor(iconActorColor);

    //Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    //Set up the widget
    vtkOrientationMarkerWidget widget = new vtkOrientationMarkerWidget();
    widget.SetOrientationMarker( iconActor );
    widget.SetInteractor( iren );
    widget.SetViewport( 0.0, 0.0, 0.2, 0.2 );
    widget.SetEnabled( 1 );
    widget.InteractiveOn();

    //Create a superquadric
    vtkSuperquadricSource superquadricSource = new vtkSuperquadricSource();
    superquadricSource.SetPhiRoundness(0.2);
    superquadricSource.SetThetaRoundness(0.8);

    //Create a mapper and actor
    vtkPolyDataMapper superquadricMapper = new vtkPolyDataMapper();
    superquadricMapper.SetInputConnection(superquadricSource.GetOutputPort());

    vtkActor superquadricActor = new vtkActor();
    superquadricActor.SetMapper(superquadricMapper);
    superquadricActor.GetProperty().SetInterpolationToFlat();
    superquadricActor.GetProperty().SetDiffuseColor(superquadricActorColor);
    superquadricActor.GetProperty().SetSpecularColor(1.0, 1.0, 1.0);
    superquadricActor.GetProperty().SetDiffuse(.6);
    superquadricActor.GetProperty().SetSpecular(.5);
    superquadricActor.GetProperty().SetSpecularPower(5.0);

    ren.AddActor(superquadricActor);
    ren.SetBackground(BgColor);
    ren.ResetCamera();
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
