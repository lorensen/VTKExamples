[VTKExamples](Home)/[Java](Java)/Visualization/AnimDataCone

**AnimDataCone.java**
```java
// First we import the VTK package that will make available all
// of the VTK commands to Java.
import vtk.*;

public class animDataCone {

	/**
	 * @param args
	 */
	// load the necessary interface libraries on first reference to the
	// class.
	static {
		System.loadLibrary("vtkCommonJava");
		System.loadLibrary("vtkFilteringJava");
		System.loadLibrary("vtkIOJava");
		System.loadLibrary("vtkGeovisJava");
		System.loadLibrary("vtkImagingJava");
		System.loadLibrary("vtkGraphicsJava");
		System.loadLibrary("vtkRenderingJava");
		System.loadLibrary("vtkWidgetsJava");
	}
	// declare the interactor as an instance variable so we can refer to it
	// in the timer callback. we will pass the instance pointer to this
	// class for the callback to be invoked on.
	vtkRenderWindowInteractor iren = null;
	// create an instance polydata object to hold the animated polydata
	vtkAppendPolyData pd = null;
	// create the Transform as an instance variable so we can interact
	// with it from the interaction call back.
	vtkTransform Transform = null;
	// animState is how we manage the transform choices.
	// each animState is a frame of animation. in this case
	// a selected scale transform in the array of scale settings
	// in the moves array.
	int animState = 0;

	// this is an array of transforms to apply to the vtkPolyData.
	static double moves[][] = { { 1.11, 1., 1. }, // expand on x
			{ 1.11, 1., 1. }, // expand on x
			{ 1.11, 1., 1. }, // expand on x
			{ .9009, 1., 1. }, // contract on x
			{ .9009, 1., 1. }, // contract on x
			{ .9009, 1., 1. }, // contract on x
			{ 1., 1.11, 1. }, // expand on y
			{ 1., 1.11, 1. }, // expand on y
			{ 1., 1.11, 1. }, // expand on y
			{ 1., .9009, 1. }, // contract on y
			{ 1., .9009, 1. }, // contract on y
			{ 1., .9009, 1. }, // contract on y
			{ 1., 1., 1.11 }, // expand on z
			{ 1., 1., 1.11 }, // expand on z
			{ 1., 1., 1.11 }, // expand on z
			{ 1., 1., .9009 }, // contract on z
			{ 1., 1., .9009 }, // contract on z
			{ 1., 1., .9009 } // contract on z
	};

	public static void main(String[] args) {
		// We will start by creating an instance of our animDataCone example
		// This example uses callbacks, and for Java that requires an instance
		// object to own the callback logic.

		animDataCone myCone = new animDataCone();
		myCone.doit();
	}
/*
 * The TimerEvent is specified as the TimerEvent callback 
 * to the RenderWindowInteractor. The polydata modification 
 * is done here as well as the call to the renderWindow to 
 * render the updated scene. 
 */
	void StartRender() {

		vtkPolyData mpd = pd.GetPolyDataInput(0);
		vtkPoints pts = mpd.GetPoints();
		int ptct = pts.GetNumberOfPoints();
		Transform.Identity();
		Transform.Scale(animDataCone.moves[animState]);
		// this would probably be better done with a property or assembly,
		// but this clearly illustrates the modification of point data
		for (int i = 0; i < ptct; i++) {
			double[] xpt = pts.GetPoint(i);
			xpt = Transform.TransformDoublePoint(xpt);
			pts.SetPoint(i, xpt);
		}
		// cycle through the animation frames
		animState = (++animState) % 18;
		// Actually, marking the polydata as modified
		// is the key to the animation.
		// Comment the following pd.modified() and nothing
		// will appear to happen, inspite of all the preceding.
		// the pipeline UpdateExtent() only processes data that
		// a modification time stamp more recent than the last render.
		pd.Modified();
		// Uncomment the following to get a log of time in milliseconds 
		// for each rendered frame. 
//		System.out.println("Render:" + System.currentTimeMillis());
	}

	/*
	 * The doit() function is simply the instance function to perform the
	 * construction of the vtk pipeline for this example.
	 */
	void doit() {

		// This example illustrates animation via the startrender callback/
		//
		Transform = new vtkTransform();
		// Next we create an instance of vtkConeSource and set some of its
		// properties. The instance of vtkConeSource "cone" is part of a
		// visualization pipeline (it is a source process object); it produces
		// data (output type is vtkPolyData) which other filters may process.
		vtkConeSource cone = new vtkConeSource();
		cone.SetHeight(3.0);
		cone.SetRadius(1.0);
		cone.SetResolution(10);

		pd = new vtkAppendPolyData();

		pd.SetInput(cone.GetOutput());
		// In this example we terminate the pipeline with a mapper process
		// object.
		// (Intermediate filters such as vtkShrinkPolyData could be inserted in
		// between the source and the mapper.) We create an instance of
		// vtkPolyDataMapper to map the polygonal data into graphics primitives.
		// We connect the output of the cone source to the input of this mapper.
		vtkPolyDataMapper coneMapper = new vtkPolyDataMapper();
		coneMapper.SetInput(pd.GetOutput());

		// Create an actor to represent the cone. The actor orchestrates
		// rendering of
		// the mapper's graphics primitives. An actor also refers to properties
		// via a
		// vtkProperty instance, and includes an internal transformation matrix.
		// We
		// set this actor's mapper to be coneMapper which we created above.
		vtkActor coneActor = new vtkActor();
		coneActor.SetMapper(coneMapper);

		// Create the Renderer and assign actors to it. A renderer is like a
		// viewport. It is part or all of a window on the screen and it is
		// responsible for drawing the actors it has. We also set the
		// background color here.
		vtkRenderer ren1 = new vtkRenderer();
		ren1.AddActor(coneActor);
		ren1.SetBackground(0.1, 0.2, 0.4);

		// Finally we create the render window which will show up on the screen
		// We put our renderer into the render window using AddRenderer. We
		// also set the size to be 300 pixels by 300.
		vtkRenderWindow renWin = new vtkRenderWindow();
		renWin.AddRenderer(ren1);
		renWin.SetSize(600, 600);

		// The vtkRenderWindowInteractor class watches for events (e.g.,
		// keypress,
		// mouse) in the vtkRenderWindow. These events are translated into
		// event invocations that VTK understands (see VTK/Common/vtkCommand.h
		// for all events that VTK processes). Then observers of these VTK
		// events can process them as appropriate.
		iren = new vtkRenderWindowInteractor();
		iren.SetRenderWindow(renWin);

		// By default the vtkRenderWindowInteractor instantiates an instance
		// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
		// it observes into operations on the camera, actors, and/or properties
		// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
		// Here we specify a particular interactor style.
		vtkInteractorStyleTrackballCamera style = new vtkInteractorStyleTrackballCamera();
		iren.SetInteractorStyle(style);

		// Start the event loop.
		iren.Initialize();
		// Now for every window render we call our callback function to update
		// the model
		// resulting in another render.
		ren1.AddObserver("StartEvent", this, "StartRender");
		iren.CreateRepeatingTimer(50);

		iren.Start();

		// There is no explicit need to free any objects at this point.
		// Once Python exits, memory is automatically freed.

	}

}
```
