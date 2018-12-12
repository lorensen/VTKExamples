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
import vtk.vtkVertex;
import vtk.vtkCellArray;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkNamedColors;

public class Vertex extends JPanel implements ActionListener {
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
	  
	  
	  public Vertex() {
	    super(new BorderLayout());

	  
	  vtkNamedColors Color = new vtkNamedColors();
	  
	  //For Actor Color
	  double ActorColor[] = new double[4];
	  //Renderer Background Color
	  double BgColor[] = new double[4];
	  
		   
	  //Change Color Name to Use your own Color for Change Actor Color
	  Color.GetColor("OrangeRed",ActorColor);
	  //Change Color Name to Use your own Color for Renderer Background
	  Color.GetColor("DarkSlateGray",BgColor);

	  
	  //Create a 3D Point
	  vtkPoints Points = new vtkPoints();
	  Points.InsertNextPoint(0.0,0.0,0.0);
	  
	  //Create A Vertex Which in turn represents a 3D point
	  vtkVertex Vertex = new vtkVertex();
	  Vertex.GetPointIds().SetId(0, 0);
	  
	  //Create a Cell Array -  a raw integer list that explicitly represents cell connectivity
	  vtkCellArray Vertices = new vtkCellArray();
	  Vertices.InsertNextCell(Vertex);
	  
	  //Create a PolyData  which represents a geometric structure 
	  //consisting of vertices, lines, polygons, and/or triangle strips
	  vtkPolyData PolyData = new vtkPolyData();
	  PolyData.SetPoints(Points);
	  PolyData.SetVerts(Vertices);
	  
	  //Create a Mapper and Actor
	  vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
	  Mapper.SetInputData(PolyData);
	  
	  vtkActor Actor = new vtkActor();
	  Actor.SetMapper(Mapper);
	  Actor.GetProperty().SetPointSize(15);
	  Actor.GetProperty().SetColor(ActorColor);

	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(Actor);
	  renWin.resetCamera();
	  renWin.GetRenderer().SetBackground(BgColor);
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
	        JFrame frame = new JFrame("Vertex");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new Vertex(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	}  
