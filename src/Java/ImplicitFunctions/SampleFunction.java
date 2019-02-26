import vtk.vtkNativeLibrary;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkPolyDataMapper;
import vtk.vtkSuperquadric;
import vtk.vtkSampleFunction;
import vtk.vtkContourFilter;
import vtk.vtkOutlineFilter;


public class SampleFunction
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

    //For Outline Actor Color
    double OutlineActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];

    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("Black",OutlineActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Tan",BgColor);
    
    vtkSuperquadric implicitFunction = new vtkSuperquadric();
    implicitFunction.SetPhiRoundness(2.5);
    implicitFunction.SetThetaRoundness(.5);
    
    //Sample the function
    vtkSampleFunction sample = new vtkSampleFunction();
    sample.SetSampleDimensions(50,50,50);
    sample.SetImplicitFunction(implicitFunction);
    double value = 2.0;
    double xmin = -value, xmax = value, ymin = -value, ymax = value, zmin = -value, zmax = value;
    sample.SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
    
    //Create the 0 isosurface
    vtkContourFilter contours = new vtkContourFilter();
    contours.SetInputConnection(sample.GetOutputPort());
    contours.GenerateValues(1, 2.0, 2.0);

    //Map the contours to graphical primitives
    vtkPolyDataMapper contourMapper = new vtkPolyDataMapper();
    contourMapper.SetInputConnection(contours.GetOutputPort());
    contourMapper.SetScalarRange(0.0, 1.2);

    //Create an actor for the contours
    vtkActor contourActor = new vtkActor();
    contourActor.SetMapper(contourMapper);

    //create a box around the function to indicate the sampling volume --

    //Create outline
    vtkOutlineFilter outline = new vtkOutlineFilter();
    outline.SetInputConnection(sample.GetOutputPort());

    // Map it to graphics primitives
    vtkPolyDataMapper outlineMapper = new vtkPolyDataMapper();
    outlineMapper.SetInputConnection(outline.GetOutputPort());

    // Create an actor for it
    vtkActor outlineActor = new vtkActor();
    outlineActor.SetMapper(outlineMapper);
    outlineActor.GetProperty().SetColor(OutlineActorColor);
        
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    ren.AddActor(contourActor);
    ren.AddActor(outlineActor);
    ren.SetBackground(BgColor);
    
    renWin.SetSize(300,300);
    renWin.Render();

    iren.Initialize();
    iren.Start();

  }
}
