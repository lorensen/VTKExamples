import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkDataSetMapper;
import vtk.vtkCubeSource;
import vtk.vtkShrinkFilter;
import vtk.vtkProperty;
import vtk.vtkNamedColors;


//Author: Bharatesh Chakravarthi
//Affiliation: VE Lab, Chung Ang University, Seoul, South Korea. 


public class Cube extends JPanel implements ActionListener {
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
	  
	  
	  public Cube() {
	    super(new BorderLayout());
	   
	   double MyColor[] = new double[4];
	   vtkNamedColors Color = new vtkNamedColors();
	   Color.GetColor("SpringGreen",MyColor);
	 
	  // Create a cube.
	  vtkCubeSource Cube = new vtkCubeSource();
	 
	  //shrink cells composing an arbitrary data set
	  vtkShrinkFilter shrink = new vtkShrinkFilter();
	  shrink.SetInputConnection(Cube.GetOutputPort());
	  shrink.SetShrinkFactor(.9);
	  
	  //Create a Mapper and Actor
	  vtkDataSetMapper Mapper = new vtkDataSetMapper();
	  Mapper.SetInputConnection(shrink.GetOutputPort());
	  
	  vtkProperty Back = new vtkProperty();
	  Back.SetColor(1.0, 1.0, 0.0);
	  
	  vtkActor Actor = new vtkActor();
	  Actor.SetMapper(Mapper);
	  Actor.GetProperty().EdgeVisibilityOn();
	  Actor.GetProperty().SetColor(MyColor);
	  Actor.SetBackfaceProperty(Back);
	   
	  
	  
	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(Actor);
	  renWin.resetCamera();
	  renWin.GetRenderer().SetBackground(0.5,0.0,0.0);
	  renWin.resetCamera();
	  renWin.resetCameraClippingRange();
	  renWin.GetRenderer().GetActiveCamera().Azimuth(30);
	  renWin.GetRenderer().GetActiveCamera().Elevation(30);

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
	        JFrame frame = new JFrame("Cube");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new Cube(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	} 
