import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPolyDataMapper;
import vtk.vtkRenderWindow;
import vtk.vtkRenderWindowInteractor;
import vtk.vtkRenderer;
import vtk.vtkCone;
import vtk.vtkPlane;
import vtk.vtkSphere;
import vtk.vtkImplicitBoolean;
import vtk.vtkSampleFunction;
import vtk.vtkContourFilter;


public class IceCream 
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
        
    // This example demonstrates how to use boolean combinations of implicit 
    //functions to create a model of an ice cream cone.
    
    // Create implicit function primitives. These have been carefully placed to
    // give the effect that we want. We are going to use various combinations of
    // these functions to create the shape we want; for example, we use planes
    // intersected with a cone (which is infinite in extent) to get a finite cone.
    
    vtkNamedColors colors = new vtkNamedColors();
    
    //For coneActor Color
    double coneActorColor[] = new double[4];
    //For creamActor Color
    double creamActorColor[] = new double[4];
    //Renderer Background Color
    double Bgcolor[] = new double[4];

    colors.GetColor("chocolate", coneActorColor);
    colors.GetColor("mint", creamActorColor);
    colors.GetColor("SlateGray", Bgcolor);
    
    vtkCone cone = new vtkCone();
    cone.SetAngle(20);
    
    vtkPlane vertPlane = new vtkPlane();
    vertPlane.SetOrigin(.1, 0, 0);
    vertPlane.SetNormal(-1, 0, 0);

    vtkPlane basePlane = new vtkPlane();
    basePlane.SetOrigin(1.2, 0, 0);
    basePlane.SetNormal(1, 0, 0);

    vtkSphere iceCream = new vtkSphere();
    iceCream.SetCenter(1.333, 0, 0);
    iceCream.SetRadius(0.5);

    vtkSphere bite = new vtkSphere();
    bite.SetCenter(1.5, 0, 0.5);
    bite.SetRadius(0.25);
    
    // Combine primitives to build ice-cream cone. Clip the cone with planes.
    vtkImplicitBoolean theCone = new vtkImplicitBoolean();
    theCone.SetOperationTypeToIntersection();
    theCone.AddFunction(cone);
    theCone.AddFunction(vertPlane);
    theCone.AddFunction(basePlane);
    
    // Take a bite out of the ice cream.
    vtkImplicitBoolean theCream = new vtkImplicitBoolean();
    theCream.SetOperationTypeToDifference();
    theCream.AddFunction(iceCream);
    theCream.AddFunction(bite);
    
    // The sample function generates a distance function from the
    // implicit function (which in this case is the cone). 
    // This is then contoured to get a polygonal surface.
    
    vtkSampleFunction theConeSample = new vtkSampleFunction();
    theConeSample.SetImplicitFunction(theCone);
    theConeSample.SetModelBounds(-1, 1.5, -1.25, 1.25, -1.25, 1.25);
    theConeSample.SetSampleDimensions(128, 128, 128);
    theConeSample.ComputeNormalsOff();
    
    vtkContourFilter theConeSurface = new vtkContourFilter();
    theConeSurface.SetInputConnection(theConeSample.GetOutputPort());
    theConeSurface.SetValue(0, 0.0);
    
    vtkPolyDataMapper coneMapper = new vtkPolyDataMapper();
    coneMapper.SetInputConnection(theConeSurface.GetOutputPort());
    coneMapper.ScalarVisibilityOff();
    
    vtkActor coneActor = new vtkActor();
    coneActor.SetMapper(coneMapper);
    coneActor.GetProperty().SetColor(coneActorColor);
    
    //The same here for the ice cream.
    
    vtkSampleFunction theCreamSample = new vtkSampleFunction();
    theCreamSample.SetImplicitFunction(theCream);
    theCreamSample.SetModelBounds(0, 2.5, -1.25, 1.25, -1.25, 1.25);
    theCreamSample.SetSampleDimensions(128, 128, 128);
    theCreamSample.ComputeNormalsOff();
    
    vtkContourFilter theCreamSurface = new vtkContourFilter();
    theCreamSurface.SetInputConnection(theCreamSample.GetOutputPort());
    theCreamSurface.SetValue(0, 0.0);
    
    vtkPolyDataMapper creamMapper = new vtkPolyDataMapper();
    creamMapper.SetInputConnection(theCreamSurface.GetOutputPort());
    creamMapper.ScalarVisibilityOff();
    
    vtkActor creamActor = new vtkActor();
    creamActor.SetMapper(creamMapper);
    creamActor.GetProperty().SetDiffuseColor(creamActorColor);
    creamActor.GetProperty().SetSpecular(.6);
    creamActor.GetProperty().SetSpecularPower(50);
	
    // Create the renderer, render window and interactor.
    vtkRenderer ren = new vtkRenderer();
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer(ren);
    vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
    iren.SetRenderWindow(renWin);
    
    // Visualize
    ren.AddActor(coneActor);
    ren.AddActor(creamActor);
    ren.SetBackground(Bgcolor);
    ren.ResetCamera();
    ren.GetActiveCamera().Roll(90);
    ren.GetActiveCamera().Dolly(1.25);
    ren.ResetCameraClippingRange();
    
    renWin.SetSize(300, 300);
    renWin.Render();

    iren.Initialize();
    iren.Start();
  }
}
