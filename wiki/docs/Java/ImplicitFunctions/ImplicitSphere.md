[VTKExamples](/home/)/[Java](/Java)/ImplicitFunctions/ImplicitSphere

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/ImplicitFunctions/TestImplicitSphere.png?raw=true" width="256" />

### Description
This example creates a polygonal model of two spheres and 3 tubes, and then renders it to
the screen. It will rotate the scene 360 degrees and then exit. The basic
setup of source -> mapper -> actor -> renderer -> renderwindow is 
typical of most VTK programs.

**ImplicitSphere.java**
```java
//
// This example creates a polygonal model of two spheres and 3 tubes, and then renders it to
// the screen. It will rotate the scene 360 degrees and then exit. The basic
// setup of source -> mapper -> actor -> renderer -> renderwindow is 
// typical of most VTK programs.
//

// We import the vtk wrapped classes first.
import vtk.*;

// Then we define our class.
public class Sphere {

  // In the static contructor we load in the native code.
  // The libraries must be in your path to work.
  static { 
	  System.out.println("load vtkCommonJava");
	  System.loadLibrary("vtkCommonJava");
	  System.out.println("load vtkChartsJava");
	  System.loadLibrary("vtkChartsJava");
	  System.loadLibrary("vtkFilteringJava");
 	  System.loadLibrary("vtkGenericFilteringJava");
	  System.loadLibrary("vtkGeovisJava");
	  System.loadLibrary("vtkGraphicsJava");
	  System.loadLibrary("vtkHybridJava");
	  System.loadLibrary("vtkImagingJava");
	  System.loadLibrary("vtkInfovisJava");
	  System.loadLibrary("vtkIOJava");
	  System.loadLibrary("vtkRenderingJava");
	  System.loadLibrary("vtkViewsJava");
	  System.loadLibrary("vtkVolumeRenderingJava");
	  System.loadLibrary("vtkWidgetsJava");
      System.out.println("LoadLibrary complete for vtkjava");
    
  }

  // Now the main program
  public static void main (String []args) {
    // 
    // Next we create an instance of vtkSphereSource and set some of its
    // properties. The instance of vtkSphereSource "sphere" is part of a
    // visualization pipeline (it is a source process object); it produces data
    // (output type is vtkPolyData) which other filters may process.
    //
    vtkSphereSource sphere = new vtkSphereSource();
    sphere.SetRadius( 1.0 );
    sphere.SetPhiResolution(12);
    sphere.SetThetaResolution( 12 );
    
    vtkSphereSource sph = new vtkSphereSource();
    vtkAppendPolyData apf = new vtkAppendPolyData();
    vtkPolyData pd = new vtkPolyData(); 
    vtkTubeFilter tubes = new vtkTubeFilter();
    vtkCellArray polys = new vtkCellArray(); 
    vtkPoints points = new vtkPoints();
    points.Allocate(10, 10);
    polys.Allocate(10, 10);
    pd.Allocate(10, 10);
    sph.SetCenter(3, 0, 2);
    sph.SetRadius(2);
    sph.SetThetaResolution(25);
    sph.SetPhiResolution(25);
    sph.Update(); 
    points.InsertNextPoint(3, 0, 2);
    points.InsertNextPoint(3, 3, 3);
    points.InsertNextPoint(5, 3, 3);
    points.InsertNextPoint(2, 4, 2);
    points.InsertNextPoint(4,4,4);
    
    polys.InsertNextCell(2);
     polys.InsertCellPoint(0);
     polys.InsertCellPoint(1);
    polys.InsertNextCell(2);
     polys.InsertCellPoint(1);
     polys.InsertCellPoint(2);
    polys.InsertNextCell(2);
     polys.InsertCellPoint(2);
     polys.InsertCellPoint(3);
    polys.InsertNextCell(2);
     polys.InsertCellPoint(3);
     polys.InsertCellPoint(1);
    pd.SetLines(polys);
    pd.SetPoints(points);
    tubes.AddInput(pd);
    tubes.SetRadius(.25);
    tubes.SetNumberOfSides(9);
    tubes.Update();

    apf.AddInput(tubes.GetOutput());
    apf.AddInput(sphere.GetOutput());
    apf.AddInput(sph.GetOutput());
    // 
    // In this example we terminate the pipeline with a mapper process object.
    // (Intermediate filters such as vtkShrinkPolyData could be inserted in
    // between the source and the mapper.)  We create an instance of
    // vtkPolyDataMapper to map the polygonal data into graphics primitives. We
    // connect the output of the sphere souece to the input of this mapper.
    //
    vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
    sphereMapper.SetInput( apf.GetOutput() );
    // 
    // Create an actor to represent the sphere. The actor orchestrates rendering
    // of the mapper's graphics primitives. An actor also refers to properties
    // via a vtkProperty instance, and includes an internal transformation
    // matrix. We set this actor's mapper to be sphereMapper which we created
    // above.
    //
    vtkActor sphereActor = new vtkActor();
    sphereActor.SetMapper( sphereMapper );

    //
    // Create the Renderer and assign actors to it. A renderer is like a
    // viewport. It is part or all of a window on the screen and it is
    // responsible for drawing the actors it has.  We also set the background
    // color here
    //
    vtkRenderer ren1 = new vtkRenderer();
    ren1.AddActor( sphereActor );
    ren1.SetBackground( 0.1, 0.2, 0.4 );

    //
    // Finally we create the render window which will show up on the screen
    // We put our renderer into the render window using AddRenderer. We also
    // set the size to be 300 pixels by 300
    //
    vtkRenderWindow renWin = new vtkRenderWindow();
    renWin.AddRenderer( ren1 );
    renWin.SetSize( 300, 300 );
    
    //
    // Now we loop over 360 degrees and render the sphere each time
    //
    int i;
    for (i = 0; i < 360; ++i)
      {
      // render the image
      renWin.Render();
      try {
		Thread.sleep(100);
	} catch (Throwable e) {
		e.printStackTrace();
	}
      // rotate the active camera by one degree
      ren1.GetActiveCamera().Azimuth( 1 );
      }
    
    try {
		Thread.sleep(1000);
	} catch (Throwable e1) {
		e1.printStackTrace();
	}
  
    } 
}
```
