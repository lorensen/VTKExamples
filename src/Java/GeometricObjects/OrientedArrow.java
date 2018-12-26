import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;


import vtk.vtkActor;
import vtk.vtkArrowSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPolyDataMapper;
import vtk.vtkMinimalStandardRandomSequence;
import vtk.vtkNamedColors;
import vtk.vtkMath;
import vtk.vtkMatrix4x4;
import vtk.vtkTransform;
import vtk.vtkTransformPolyDataFilter;
import vtk.vtkSphereSource;


//Author: Bharatesh Chakravarthi
//Affiliation: VE Lab, Chung Ang University, Seoul, South Korea. 


public class OrientedArrow extends JPanel implements ActionListener {
  private static final long serialVersionUID = 1L;
  private vtkPanel renWin;
  private JButton exitButton;

  // -----------------------------------------------------------------
  // Load VTK library and print which library was not properly loaded
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
  // -----------------------------------------------------------------
	  
	  
  public OrientedArrow() {
    super(new BorderLayout());
	    
    vtkNamedColors Color = new vtkNamedColors();
		  
    //For Actor Color
    double StartActorColor[] = new double[4];
    double ArrowActorColor[] = new double[4];
    double EndActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
			  
				   
    //Change Color Name to Use your own Color for Change StartActor Color
    Color.GetColor("GreenYellow",StartActorColor);
    //Change Color Name to Use your own Color for Change StartActor Color
    Color.GetColor("Tomato",ArrowActorColor);
    //Change Color Name to Use your own Color for Change StartActor Color
    Color.GetColor("Yellow",EndActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("SlateGray",BgColor);
	    	    
    //Create a Arrow 
    vtkArrowSource ArrowSource = new vtkArrowSource();

    double sp[] = new double[3];
    double ep[] = new double[3];
	  
    // Generate a random start and end point
    vtkMinimalStandardRandomSequence RandomNumbers = new vtkMinimalStandardRandomSequence();
    RandomNumbers.SetSeed(8775070);
    for(int i=0;i<3;++i) {
      RandomNumbers.Next();
      sp[i]=RandomNumbers.GetRangeValue(-10, 10);
      RandomNumbers.Next();
      ep[i]=RandomNumbers.GetRangeValue(-10, 10);
    }
	  
    // Compute a basis
    double normalizedX[] = new double[3];
    double normalizedY[] = new double[3];
    double normalizedZ[] = new double[3];
	  
    // The X axis is a vector from start to end
    vtkMath ss = new vtkMath();
    ss.Subtract(ep, sp, normalizedX);
    double length;
    length=ss.Norm(normalizedX);
    ss.Normalize(normalizedX);
	  
    // The Z axis is an arbitrary vector cross X
    double arbitary[] = new double[3];
    for(int i=0;i<3;++i) {
      RandomNumbers.Next();
      arbitary[i]=RandomNumbers.GetRangeValue(-10, 10);
    }
    ss.Cross(normalizedX, arbitary, normalizedZ);
    ss.Normalize(normalizedZ);
    // The Y axis is Z cross X  
    ss.Cross(normalizedZ, normalizedX, normalizedY);
    vtkMatrix4x4 Matrix = new vtkMatrix4x4();
	  
    // Create the direction cosine matrix
    Matrix.Identity();
    for(int i=0;i<3;i++) {
      Matrix.SetElement(i, 0, normalizedX[i]);
      Matrix.SetElement(i, 1, normalizedY[i]);
      Matrix.SetElement(i, 2, normalizedZ[i]);
    } 
	  
	  
    //Apply the transforms
    vtkTransform Transform = new vtkTransform();
    Transform.Translate(sp);
    Transform.Concatenate(Matrix);
    Transform.Scale(length, length, length);
	  
    // Transform the polydata
    vtkTransformPolyDataFilter TransformPD = new vtkTransformPolyDataFilter();
    TransformPD.SetTransform(Transform);
    TransformPD.SetInputConnection(ArrowSource.GetOutputPort());
	  
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    vtkActor Actor = new vtkActor();
    Mapper.SetInputConnection(ArrowSource.GetOutputPort());

	
    Actor.SetMapper(Mapper);
    Actor.SetUserMatrix(Transform.GetMatrix());
    Actor.GetProperty().SetColor(ArrowActorColor);
	  
    //Create spheres for start and end point
    vtkSphereSource SphereStartSource = new vtkSphereSource();
    SphereStartSource.SetCenter(sp);
    SphereStartSource.SetRadius(0.8);
	  
    vtkPolyDataMapper SphereStartMapper = new vtkPolyDataMapper();
    SphereStartMapper.SetInputConnection(SphereStartSource.GetOutputPort());
	  
    vtkActor SphereStartActor = new vtkActor();
    SphereStartActor.SetMapper(SphereStartMapper);
    SphereStartActor.GetProperty().SetColor(StartActorColor);
	  
	  
    vtkSphereSource SphereEndSource = new vtkSphereSource();
    SphereEndSource.SetCenter(ep);
    SphereEndSource.SetRadius(0.8);
	  
    vtkPolyDataMapper SphereEndMapper = new vtkPolyDataMapper();
    SphereEndMapper.SetInputConnection(SphereEndSource.GetOutputPort());
	  
    vtkActor SphereEndActor = new vtkActor();
    SphereEndActor.SetMapper(SphereEndMapper);
    SphereEndActor.GetProperty().SetColor(EndActorColor);

	   
    renWin = new vtkPanel();
    renWin.GetRenderer().AddActor(Actor);
    renWin.GetRenderer().AddActor(SphereStartActor);
    renWin.GetRenderer().AddActor(SphereEndActor);
    renWin.GetRenderer().SetBackground(BgColor);;
    renWin.resetCamera();
	  

    // Add Java UI components
    exitButton = new JButton("Exit");
    exitButton.addActionListener(this);

    add(renWin, BorderLayout.CENTER);
    add(exitButton, BorderLayout.SOUTH);
  }

  /** An ActionListener that listens to the button. */
  public void actionPerformed(ActionEvent e) {
    if (e.getSource().equals(exitButton)) {
      System.exit(0);
    }
  }

  public static void main(String s[]) {
    SwingUtilities.invokeLater(new Runnable() {
        public void run() {
          JFrame frame = new JFrame("Oriented Arrow");
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.getContentPane().setLayout(new BorderLayout());
          frame.getContentPane().add(new OrientedArrow(), BorderLayout.CENTER);
          frame.setSize(400, 400);
          frame.setLocationRelativeTo(null);
          frame.setVisible(true);
        }
      });
  }
}
