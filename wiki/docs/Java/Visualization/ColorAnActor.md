[VTKExamples](/index/)/[Java](/Java)/Visualization/ColorAnActor

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestColorAnActor.png?raw=true" width="256" />

### Description
This example creates a red sphere.

**ColorAnActor.java**
```java
import vtk.*;

public class ColorAnActor {

  static
  {
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
    System.loadLibrary("vtkImagingJava");
    System.loadLibrary("vtkGraphicsJava");
    System.loadLibrary("vtkRenderingJava");
  }

  public static void main(String[] args)
  {
    //Create a sphere
    vtkSphereSource sphereSource = 
      new vtkSphereSource();
    sphereSource.Update();

    //Create a mapper and actor
    vtkPolyDataMapper mapper = 
      new vtkPolyDataMapper();
    mapper.SetInputConnection(sphereSource.GetOutputPort());
    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    //Set the color of the sphere
    actor.GetProperty().SetColor(1.0, 0.0, 0.0); //(R,G,B)
    
    //Create a renderer, render window, and interactor
    vtkRenderer renderer = 
      new vtkRenderer();
    vtkRenderWindow renderWindow = 
      new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);
    vtkRenderWindowInteractor renderWindowInteractor = 
      new vtkRenderWindowInteractor();
    renderWindowInteractor.SetRenderWindow(renderWindow);

    //Add the actor to the scene
    renderer.AddActor(actor);
    renderer.SetBackground(1,1,1); // Background color white

    //Render and interact
    renderWindow.Render();
    renderWindowInteractor.Start();
  }
}
```
