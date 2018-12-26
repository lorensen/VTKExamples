import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkCellArray;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPoints;
import vtk.vtkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkPolygon;
import vtk.vtkNamedColors;




//Author: Bharatesh Chakravarthi
//Affiliation: VE Lab, Chung Ang University, Seoul, South Korea. 


public class Polygon extends JPanel implements ActionListener {
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
	  
	  
  public Polygon() {
    super(new BorderLayout());

    vtkPoints Points = new vtkPoints();
    Points.InsertNextPoint(0.0,0.0,0.0);
    Points.InsertNextPoint(1.0,0.0,0.0);
    Points.InsertNextPoint(1.0,1.0,0.0);
    Points.InsertNextPoint(0.0,1.0,0.0);
	  
			  
    vtkPolygon Polygon = new vtkPolygon();
    Polygon.GetPointIds().SetNumberOfIds(4);
    Polygon.GetPointIds().SetId(0, 0);
    Polygon.GetPointIds().SetId(1, 1);
    Polygon.GetPointIds().SetId(2, 2);
    Polygon.GetPointIds().SetId(3, 3);
	  
		  
    vtkCellArray Polygons = new vtkCellArray();
    Polygons.InsertNextCell(Polygon);
	  

    vtkPolyData PolygonPolyData = new vtkPolyData();
    PolygonPolyData.SetPoints(Points);
    PolygonPolyData.SetPolys(Polygons);
	  
	  
    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputData(PolygonPolyData);
	

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().SetColor(1.0, 0.0, 0.1); 
    Actor.GetProperty().SetLineWidth(5);
	   
    renWin = new vtkPanel();
	 
    renWin.GetRenderer().AddActor(Actor);
    renWin.resetCamera();
    renWin.GetRenderer().SetBackground(1.0, 1.0, 1.0);

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
          JFrame frame = new JFrame("Polygon");
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.getContentPane().setLayout(new BorderLayout());
          frame.getContentPane().add(new Polygon(), BorderLayout.CENTER);
          frame.setSize(400, 400);
          frame.setLocationRelativeTo(null);
          frame.setVisible(true);
        }
      });
  }
} 
