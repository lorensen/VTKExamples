[VTKExamples](Home)/[Java](Java)/Interaction/SphereInteractionPanel

**SphereInteractionPanel.java**
```java
import java.awt.BorderLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;

import vtk.*;

public class SphereInteractorPanel extends vtkCanvas {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	/**
	 * @param args
	 */
	/*
	 * Switch style interactor
	 */
	vtkInteractorStyleSwitch cstyle = new vtkInteractorStyleSwitch();
	/*
	 * Interactor state for addObserver callback reference.
	 */
	vtkActor lineActor = new vtkActor();
	vtkActor sphereActor = new vtkActor();
	vtkActor sphActor = new vtkActor();

	public SphereInteractorPanel() {
		super();
		vtkSphereSource sphere = new vtkSphereSource();
		sphere.SetRadius(1.0);
		sphere.SetPhiResolution(12);
		sphere.SetThetaResolution(12);
		vtkSphereSource sph = new vtkSphereSource();
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
		points.InsertNextPoint(4, 4, 4);

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

		// Create a mapper for each object.

		vtkPolyDataMapper sphereMapper = new vtkPolyDataMapper();
		sphereMapper.SetInput(sphere.GetOutput());
		vtkPolyDataMapper sphMapper = new vtkPolyDataMapper();
		sphMapper.SetInput(sph.GetOutput());
		vtkPolyDataMapper lineMapper = new vtkPolyDataMapper();
		lineMapper.SetInput(tubes.GetOutput());
		// 
		// Create an actor for each object
		// this allows us to act on each actor independently when
		// manipulate each object independently when in actor interaction mode.
		//
		sphereActor.SetMapper(sphereMapper);
		sphActor.SetMapper(sphMapper);
		lineActor.SetMapper(lineMapper);

		// Add the actors to the renderer

		ren.AddActor(sphereActor);
		ren.AddActor(sphActor);
		ren.AddActor(lineActor);

		ren.SetBackground(0.1, 0.2, 0.4);

		rw.AddRenderer(ren);

		rw.SetSize(600, 600);
		ren.SetRenderWindow(rw);

		// The vtkRenderWindowInteractor class watches for events (e.g.,
		// keypress,
		// mouse) in the vtkRenderWindow. These events are translated into
		// event invocations that VTK understands (see VTK/Common/vtkCommand.h
		// for all events that VTK processes). Then observers of these VTK
		// events can process them as appropriate.

		// By default the vtkRenderWindowInteractor instantiates an instance
		// of vtkInteractorStyle. vtkInteractorStyle translates a set of events
		// it observes into operations on the camera, actors, and/or properties
		// in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
		// Here we specify a particular interactor style.
		iren.SetInteractorStyle(cstyle);
		// add observer for key event:
		iren.AddObserver("CharEvent", this, "myCharEvent");
		// Start the event loop.
		ren.ResetCamera();

	}

	/*
	 * Main routine to invoke example.
	 */
	public static void main(String[] args) {
		SphereInteractorPanel me = new SphereInteractorPanel();
		JFrame frame = new JFrame("Toggle Camera Actor Interaction");
		frame.getContentPane().setLayout(new BorderLayout());
		frame.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		frame.getContentPane().add(me, BorderLayout.CENTER);
		frame.pack();
		frame.setBounds(100, 100, 500, 500);
		frame.setVisible(true);

	}

	/*
	 * myCharEvent is a callback set on the renderWindowInteractor for the
	 * CharEvent using AddObserver. based in the character entered it performs
	 * an interaction request.
	 */
	void myCharEvent() {
		char code = Character.toLowerCase(iren.GetKeyCode());
		if (code == 'e' | code == 'q') {
			System.exit(0);
		}
	}

}
```
