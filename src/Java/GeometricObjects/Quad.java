import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkCellArray;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkQuad;





public class Quad extends JPanel implements ActionListener {
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
	  
	  
  public Quad() {
    super(new BorderLayout());
	  
	    
    vtkNamedColors Color = new vtkNamedColors();
		  
    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
		  
			   
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("DarkMagenta",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("Coral",BgColor);

    //Create four points (must be in counter clockwise order)
    double p0[] = new double[] {0.0, 0.0, 0.0};
    double p1[] = new double[] {1.0, 0.0, 0.0};
    double p2[] = new double[] {1.0, 1.0, 0.0};
    double p3[] = new double[] {0.0, 1.0, 0.0};
	    
	  
	  
    //// Add the points to a vtkPoints object
    vtkPoints Points = new vtkPoints(); 
    Points.InsertNextPoint(p0);
    Points.InsertNextPoint(p1);
    Points.InsertNextPoint(p2);
    Points.InsertNextPoint(p3);
	  
    //Create a quad on the four points	  
    vtkQuad Quad = new vtkQuad();
    Quad.GetPointIds().SetId(0, 0);
    Quad.GetPointIds().SetId(1, 1);
    Quad.GetPointIds().SetId(2, 2);
    Quad.GetPointIds().SetId(3, 3);
	  
    //Create a cell array to store the Quad
    vtkCellArray Quads = new vtkCellArray();
    Quads.InsertNextCell(Quad);
	  
    //Create a polydata to store Points and Quad
    vtkPolyData QuadData = new vtkPolyData();
    //Add the points and Quad to the dataset
    QuadData.SetPoints(Points);
    QuadData.SetPolys(Quads);
	  
    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(QuadData);
	
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(ActorColor); 
    Actor.GetProperty().SetLineWidth(5);
	   
    renWin = new vtkPanel();
	 
    renWin.GetRenderer().AddActor(Actor);
    renWin.resetCamera();
    renWin.GetRenderer().SetBackground(BgColor);

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
          JFrame frame = new JFrame("quad");
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.getContentPane().setLayout(new BorderLayout());
          frame.getContentPane().add(new Quad(), BorderLayout.CENTER);
          frame.setSize(400, 400);
          frame.setLocationRelativeTo(null);
          frame.setVisible(true);
        }
      });
  }
} 
