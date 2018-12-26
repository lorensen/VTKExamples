import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkRegularPolygonSource;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkPolyDataMapper;


//Author: Bharatesh Chakravarthi
//Affiliation: VE Lab, Chung Ang University, Seoul, South Korea. 


public class Circle extends JPanel implements ActionListener {
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
	  
	  
  public Circle() {
    super(new BorderLayout());

	

    vtkRegularPolygonSource PolygoneSource = new vtkRegularPolygonSource();
    PolygoneSource.SetNumberOfSides(100);
    PolygoneSource.SetRadius(5);
    PolygoneSource.SetCenter(0,0,0);
    //Uncomment below line to Visualize outline of circle
    PolygoneSource.GeneratePolygonOff();
    PolygoneSource.Update();
	  
	  
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(PolygoneSource.GetOutputPort());

    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
	  
    renWin = new vtkPanel();
    renWin.GetRenderer().AddActor(Actor);
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
          JFrame frame = new JFrame("Circle");
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.getContentPane().setLayout(new BorderLayout());
          frame.getContentPane().add(new Circle(), BorderLayout.CENTER);
          frame.setSize(400, 400);
          frame.setLocationRelativeTo(null);
          frame.setVisible(true);
        }
      });
  }
} 
