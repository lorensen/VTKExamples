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
import vtk.vtkPoints;
import vtk.vtkCellArray;
import vtk.vtkPolyData;
import vtk.vtkTriangle;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;


//Author: Bharatesh Chakravarthi
//Affiliation: VE Lab, Chung Ang University, Seoul, South Korea. 


public class Triangle extends JPanel implements ActionListener {
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
	  
	  
	  public Triangle() {
	    super(new BorderLayout());
	    
	  double MyColor[] = new double[4];
	  vtkNamedColors Color = new vtkNamedColors();
	  Color.GetColor("Gold",MyColor);
	  
	  // Create a triangle
	  vtkPoints Points = new vtkPoints();
	  Points.InsertNextPoint(1.0,0.0,0.0);
	  Points.InsertNextPoint(0.0,0.0,0.0);
	  Points.InsertNextPoint(0.0,1.0,0.0);
	  
	  vtkTriangle Triangle = new vtkTriangle();
	  Triangle.GetPointIds().SetId(0, 0);
	  Triangle.GetPointIds().SetId(1, 1);
	  Triangle.GetPointIds().SetId(2, 2);
	  
	  vtkCellArray CellArray = new vtkCellArray();
	  CellArray.InsertNextCell(Triangle);
	  
	  
	// Create a polydata object
	  vtkPolyData TrianglePolyData = new vtkPolyData();
	  // Add the geometry and topology to the polydata
	  TrianglePolyData.SetPoints(Points);
	  TrianglePolyData.SetPolys(CellArray);
	  
	  //Create a Mapper and Actor
	  vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
	  Mapper.SetInputData(TrianglePolyData);

	  vtkActor Actor = new vtkActor();
	  Actor.SetMapper(Mapper);
	  Actor.GetProperty().EdgeVisibilityOn();
	  Actor.GetProperty().SetColor(MyColor); 

	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(Actor);
	  renWin.resetCamera();
	  renWin.GetRenderer().SetBackground(0.208,0.32,0.144);
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
	        JFrame frame = new JFrame("Triangle");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new Triangle(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	}  
