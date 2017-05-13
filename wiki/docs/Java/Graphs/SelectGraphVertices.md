[VTKExamples](/home/)/[Java](/Java)/Graphs/SelectGraphVertices

**SelectGraphVertices.java**
```java
import vtk.*;
/*
 * Java language example to select edges and vertices from a generated Graph.
 */
public class SelectGraphVertices {

	/**
	 * All Java programs require a host class. in addition, 
	 * these two instance variables provide access to the 
	 * callback data used in this example. 
	 */
	vtkGraphLayoutView view;
	vtkAnnotationLink link; 
	/*
	 * The following static calls will load the respective 
	 * vtkJava interface libraries on first reference to this
	 * class. 
	 */
	static {
		System.loadLibrary("vtkCommonJava");
		System.loadLibrary("vtkFilteringJava");
		System.loadLibrary("vtkViewsJava");
		System.loadLibrary("vtkImagingJava");
		System.loadLibrary("vtkInfovisJava");
		System.loadLibrary("vtkGraphicsJava");
		System.loadLibrary("vtkRenderingJava");

	}
	/*
	 * primary test driver, creates an instance of this class 
	 * and then runs the example function. 
	 */
	public static void main(String[] args) {

		SelectGraphVertices me = new SelectGraphVertices();
		me.doit();
	}
	/*
	 * doit creates local objects and instantiates instance variables
	 */
	public void doit() {
		vtkRandomGraphSource source = new vtkRandomGraphSource();
		source.Update();

		view =  new vtkGraphLayoutView();
		view.AddRepresentationFromInputConnection(source.GetOutputPort());
		/*
		 * This was described as vtkRenderedGraphRepresentation in the python example, 
		 * but the java type returns it as vtkDataRepresentation. 
		 */
		vtkDataRepresentation rep = view.GetRepresentation(0);

		/*
		* The vtkDataRepresentation should already have a vtkAnnotationLink,
		* so we just want to grab it and add an observer with our callback function attached
		* Note that Java callbacks use the this "pointer" to anchor vtk objects used by the callback 
		* to establish references to required vtkobjects. 
		*/
		link = rep.GetAnnotationLink();
		link.AddObserver("AnnotationChangedEvent", this,  "selectionCallback");

		view.GetRenderWindow().SetSize(600, 600);
		view.ResetCamera();
		view.Render();
		view.GetInteractor().Start();

	}
	/*
	 * The Java callback signature has no parameters. This complicates some
	 * vtk processes by eliminating the eventid and user data normally available
	 * to C++ logic.
	 */
	public void  selectionCallback() {
		// In C++ there is some extra data passed to the callback, but in Python
		// the callback data is lost...
		
		// There can be two selection nodes, but which one is vertices and which is edges
		// does not seem to be guaranteed...
		System.out.println("in selection callback");
		
		vtkSelection sel = link.GetCurrentSelection();
		vtkSelectionNode node0 = sel.GetNode(0);
		int node0_field_type = node0.GetFieldType();
		
		vtkIdTypeArray sel_list0 = (vtkIdTypeArray)(link.GetCurrentSelection().GetNode(0).GetSelectionList());
		
		vtkSelectionNode node1 = sel.GetNode(1);
		int node1_field_type = node1.GetFieldType();
	
		vtkIdTypeArray sel_list1 = (vtkIdTypeArray)(link.GetCurrentSelection().GetNode(1).GetSelectionList());
		
		if (sel_list0.GetNumberOfTuples() > 0) {
			printFieldType(node0_field_type);
			for (int ii = 0; ii < sel_list0.GetNumberOfTuples(); ii++){
				System.out.print( "\t" + sel_list0.GetValue(ii));
			}
			System.out.println(" - on list 0." );
		}
		if (sel_list1.GetNumberOfTuples() > 0) {
			printFieldType(node1_field_type);
			for (int ii = 0; ii < sel_list1.GetNumberOfTuples(); ii++){
				System.out.print( "\t" + sel_list1.GetValue(ii));
					}
			System.out.println(" - on list 1." );
		}
		System.out.println( "- - -");
	
}
		
	public void printFieldType(int field_type) {
		if (field_type == 3) 
			System.out.print("Vertices Selected:");
		else if (field_type == 4)
			System.out.print ("Edges Selected:");
		else
			System.out.print ("Unknown type:");
			}

}
```
