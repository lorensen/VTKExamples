// First we import the VTK package that will make available all
// of the VTK commands to Java.
import vtk.*;

public class Cone6 {

	/**
	 * @param args
	 */
	// load the necessary interface libraries on first reference to the 
	// class.
	// Loading Native Libraries.
  	// Now it works in eclipse without any issues.
  	static {
	    if (!vtkNativeLibrary.LoadAllNativeLibraries()) {
	      for (vtkNativeLibrary lib : vtkNativeLibrary.values()) {
	        if (!lib.IsLoaded()) {
	          System.out.println(lib.GetLibraryName() + " not loaded");
	        }
	      }
	    }
	    vtkNativeLibrary.DisableOutputWindow(null);
	}
	// create the box widget as an instance variable so we can interact
	// with it from the interaction call back. 
	vtkBoxWidget boxWidget = null;

	public static void main(String[] args) {
		// We will start by creating an instance of our Cone6 example
		// This example uses callbacks, and for Java that requires an instance
		// object to own the callback logic.

		Cone6 myCone = new Cone6();
		myCone.doit();
	}

	// Similar to Step2/Java/Cone2.java, we define a callback for
	// interaction. In this case we will apply the box transform to the its prop3D. 
	// Java callbacks do not have parameters. 
	void myCallback() {
		vtkTransform t = new vtkTransform();
		boxWidget.GetTransform(t);
		boxWidget.GetProp3D().SetUserTransform(t);
	} 

	/*
	 * The doit() function is simply the instance function to perform the
	 * construction of the vtk pipeline for this example.
	 */
	void doit() {

		// This example introduces 3D widgets. 3D widgets take advantage of the
		// event/observer design pattern introduced previously. They typically
		// have a particular representation in the scene which can be
		// interactively
		// selected and manipulated using the mouse and keyboard. As the widgets
		// are manipulated, they in turn invoke events such as
		// StartInteractionEvent,
		// InteractionEvent, and EndInteractionEvent which can be used to
		// manipulate
		// the scene that the widget is embedded in. 3D widgets work in the
		// context
		// of the event loop which was set up in the previous example.
		//

		// Next we create an instance of vtkConeSource and set some of its
		// properties. The instance of vtkConeSource "cone" is part of a
		// visualization pipeline (it is a source process object); it produces
		// data (output type is vtkPolyData) which other filters may process.
		vtkConeSource cone = new vtkConeSource();
		cone.SetHeight(3.0);
		cone.SetRadius(1.0);
		cone.SetResolution(10);

		// In this example we terminate the pipeline with a mapper process
		// object.
		// (Intermediate filters such as vtkShrinkPolyData could be inserted in
		// between the source and the mapper.) We create an instance of
		// vtkPolyDataMapper to map the polygonal data into graphics primitives.
		// We
		// connect the output of the cone souece to the input of this mapper.
		vtkPolyDataMapper coneMapper = new vtkPolyDataMapper();
		coneMapper.SetInput(cone.GetOutput());

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
		renWin.SetSize(300, 300);

		// The vtkRenderWindowInteractor class watches for events (e.g.,
		// keypress,
		// mouse) in the vtkRenderWindow. These events are translated into
		// event invocations that VTK understands (see VTK/Common/vtkCommand.h
		// for all events that VTK processes). Then observers of these VTK
		// events can process them as appropriate.
		vtkRenderWindowInteractor iren = new vtkRenderWindowInteractor();
		iren.SetRenderWindow(renWin);

		// By default the vtkRenderWindowInteractor instantiates an instance
		// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
		// it observes into operations on the camera, actors, and/or properties
		// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
		// Here we specify a particular interactor style.
		vtkInteractorStyleTrackballCamera style = new vtkInteractorStyleTrackballCamera();
		iren.SetInteractorStyle(style);

		// Here we use a vtkBoxWidget to transform the underlying coneActor (by
		// manipulating its transformation matrix). Many other types of widgets
		// are available for use, see the documentation for more details.
		//
		// The SetInteractor method is how 3D widgets are associated with the
		// render
		// window interactor. Internally, SetInteractor sets up a bunch of
		// callbacks
		// using the Command/Observer mechanism (AddObserver()). The place
		// factor
		// controls the initial size of the widget with respect to the bounding
		// box
		// of the input to the widget.
		boxWidget = new vtkBoxWidget();
		boxWidget.SetInteractor(iren);
		boxWidget.SetPlaceFactor(1.25);

		// Place the interactor initially. The input to a 3D widget is used to
		// initially position and scale the widget. The EndInteractionEvent is
		// observed which invokes the SelectPolygons callback.
		boxWidget.SetProp3D(coneActor);
		boxWidget.PlaceWidget();

		// Now for every interaction event that is generated by the boxWidget,
		// call our callback function.
		boxWidget.AddObserver("InteractionEvent", this, "myCallback");

		// Normally the user presses the "i" key to bring a 3D widget to
		// life. Here we will manually enable it so it appears with the cone.
		boxWidget.On();

		// Start the event loop.
		iren.Initialize();
		iren.Start();

		// There is no explicit need to free any objects at this point.
		// Once Java exits, memory is automatically freed.

	}


}
