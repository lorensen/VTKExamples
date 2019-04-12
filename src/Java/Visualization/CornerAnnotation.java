import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkSphereSource;
import vtk.vtkCornerAnnotation;

public class CornerAnnotation 
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

    //For Annotation Color
    double AnnotationColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("Tomato", AnnotationColor);
    colors.GetColor("White", Bgcolor);
    
    // Create a sphere
    vtkSphereSource sphereSource = new vtkSphereSource();
    sphereSource.SetCenter(0.0, 0.0, 0.0 );
    sphereSource.SetRadius(5.0 );
    sphereSource.Update();
    
    // Create a mapper
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputData (sphereSource.GetOutput());
    
    vtkActor actor = new vtkActor();
    actor.SetMapper ( mapper );
	    
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Annotate the image with window/level and mouse over pixel information
    vtkCornerAnnotation cornerAnnotation = new vtkCornerAnnotation();
    cornerAnnotation.SetLinearFontScaleFactor(2);
    cornerAnnotation.SetNonlinearFontScaleFactor(1);
    cornerAnnotation.SetMaximumFontSize(20);
    cornerAnnotation.SetText(0, "Lower left");
    cornerAnnotation.SetText(1, "Lower right");
    cornerAnnotation.SetText(2, "Upper left");
    cornerAnnotation.SetText(3, "Upper right");
    cornerAnnotation.GetTextProperty().SetColor(AnnotationColor);
    
    // Visualise
    ren.AddViewProp( cornerAnnotation );
    ren.AddActor( actor );
	
    ren.SetBackground(Bgcolor);
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
