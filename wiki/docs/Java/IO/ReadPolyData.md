[VTKExamples](/home/)/[Java](/Java)/IO/ReadPolyData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestReadPolyData.png?raw=true" width="256" />

### Description
This example reads a polygonal data (.vtp) file.
An example data set can be found at [Torso.vtp](https://gitlab.kitware.com/lorensen/VTKExamples/raw/master/Testing/Data/Torso.vtp)

**ReadPolyData.java**
```java
import vtk.*;

public class ReadPolyData
{

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
    //parse command line arguments
    if(args.length != 1)
      {
      System.err.println("Usage: java -classpath ... ReadPolyData Filename(.vtp)");
      return;
      }

    String filename = args[0];

    //read all the data from the file
    vtkXMLPolyDataReader reader = new vtkXMLPolyDataReader();
    reader.SetFileName(filename);
    reader.Update();

    //Create a mapper and actor
    vtkPolyDataMapper mapper = new vtkPolyDataMapper();
    mapper.SetInputConnection(reader.GetOutputPort());

    vtkActor actor = new vtkActor();
    actor.SetMapper(mapper);

    //Create a renderer, render window, and interactor
    vtkRenderer renderer = new vtkRenderer();
    vtkRenderWindow renderWindow = new vtkRenderWindow();
    renderWindow.AddRenderer(renderer);
    vtkRenderWindowInteractor renderWindowInteractor = 
      new vtkRenderWindowInteractor();
    renderWindowInteractor.SetRenderWindow(renderWindow);

    //Add the actor to the scene
    renderer.AddActor(actor);
    renderer.SetBackground(.3, .6, .3); // Background color green

    //Render and interact
    renderWindow.Render();
    renderWindowInteractor.Start();
  }
}
```
