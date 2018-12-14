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
import vtk.vtkPoints;
import vtk.vtkPyramid;
import vtk.vtkUnstructuredGrid;
import vtk.vtkCellArray;
import vtk.vtkNamedColors;


public class Pyramid extends JPanel implements ActionListener {
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
	  
	  
	   public Pyramid() {
	    super(new BorderLayout());
	   
	   
	   vtkNamedColors Color = new vtkNamedColors(); 
	   //For Actor Color
	   double ActorColor[] = new double[4];
	   //Renderer Background Color
	   double BgColor[] = new double[4];
	   
	   
	   //Change Color Name to Use your own Color for Change Actor Color
	   Color.GetColor("Sienna",ActorColor);
	   //Change Color Name to Use your own Color for Renderer Background
	   Color.GetColor("Ivory",BgColor);
	   
	   

	  vtkPoints Points = new vtkPoints();
	  
	  double p0[] = new double[] {1.0,1.0,1.0};
	  double p1[] = new double[] {-1.0,1.0,1.0};
	  double p2[] = new double[] {-1.0,-1.0,1.0};
	  double p3[] = new double[] {1.0,-1.0, 1.0};
	  double p4[] = new double[] {0.0,0.0, 0.0};
	  
	  Points.InsertNextPoint(p0);
	  Points.InsertNextPoint(p1);
	  Points.InsertNextPoint(p2);
	  Points.InsertNextPoint(p3);
	  Points.InsertNextPoint(p4);
	  
	  
	  vtkPyramid Pyramid = new vtkPyramid();
	  Pyramid.GetPointIds().SetId(0, 0);
	  Pyramid.GetPointIds().SetId(1, 1);
	  Pyramid.GetPointIds().SetId(2, 2);
	  Pyramid.GetPointIds().SetId(3, 3);
	  Pyramid.GetPointIds().SetId(4, 4);
	  
	  vtkCellArray Cells = new vtkCellArray();
	  Cells.InsertNextCell(Pyramid);
	  
	  vtkUnstructuredGrid UG = new vtkUnstructuredGrid();
	  UG.SetPoints(Points);
	  UG.InsertNextCell(Pyramid.GetCellType(), Pyramid.GetPointIds());
	  
	  vtkDataSetMapper Mapper = new vtkDataSetMapper();
	  Mapper.SetInputData(UG);
	  
	  
	  vtkActor Actor = new vtkActor();
	  Actor.SetMapper(Mapper);
	  Actor.GetProperty().EdgeVisibilityOn();
	  Actor.GetProperty().SetColor(ActorColor);

	  renWin = new vtkPanel();
	  renWin.GetRenderer().AddActor(Actor);
	  renWin.GetRenderer().SetBackground(BgColor);
	  renWin.resetCamera();
	  renWin.GetRenderer().GetActiveCamera().Azimuth(180);
	  renWin.GetRenderer().GetActiveCamera().Elevation(-20);
	  renWin.resetCameraClippingRange();

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
	        JFrame frame = new JFrame("Pyramid");
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        frame.getContentPane().setLayout(new BorderLayout());
	        frame.getContentPane().add(new Pyramid(), BorderLayout.CENTER);
	        frame.setSize(400, 400);
	        frame.setLocationRelativeTo(null);
	        frame.setVisible(true);
	      }
	    });
	  }
	} 
