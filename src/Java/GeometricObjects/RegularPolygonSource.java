import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import vtk.vtkActor;
import vtk.vtkNamedColors;
import vtk.vtkNativeLibrary;
import vtk.vtkPanel;
import vtk.vtkRegularPolygonSource;
import vtk.vtkShrinkPolyData;
import vtk.vtkPolyDataMapper;
import vtk.vtkProperty;



public class RegularPolygonSource extends JPanel implements ActionListener {
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
	  
	  
  public RegularPolygonSource() {
    super(new BorderLayout());
	    
    vtkNamedColors Color = new vtkNamedColors();
		  
    //For Actor Color
    double ActorColor[] = new double[4];
    //Renderer Background Color
    double BgColor[] = new double[4];
    //BackFace color 
    double BackColor[] = new double[4];
			  
				   
    //Change Color Name to Use your own Color for Change Actor Color
    Color.GetColor("DarkMagenta",ActorColor);
    //Change Color Name to Use your own Color for Renderer Background
    Color.GetColor("White",BgColor);
    //Change Color Name to Use your own Color for BackFace Color
    Color.GetColor("Yellow",BackColor);
	   
	    
  
    vtkRegularPolygonSource PolygonSource = new vtkRegularPolygonSource();
    PolygonSource.SetNumberOfSides(5);
    PolygonSource.SetRadius(5);
    PolygonSource.SetCenter(0,0,0);
	  
    //shrink cells composing an arbitrary data set
    vtkShrinkPolyData shrink = new vtkShrinkPolyData();
    shrink.SetInputConnection(PolygonSource.GetOutputPort());
    shrink.SetShrinkFactor(.9);

	 
    //Create a Mapper and Actor
    vtkPolyDataMapper Mapper = new vtkPolyDataMapper();
    Mapper.SetInputConnection(shrink.GetOutputPort());
	  
    vtkProperty Back = new vtkProperty();
    Back.SetColor(BackColor);
	  
	  
    vtkActor Actor = new vtkActor();
    Actor.SetMapper(Mapper);
    Actor.GetProperty().EdgeVisibilityOn();
    Actor.GetProperty().SetLineWidth(5);
    Actor.GetProperty().SetColor(ActorColor); 
    Actor.SetBackfaceProperty(Back);

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
          JFrame frame = new JFrame("Regular Polygon Source");
          frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
          frame.getContentPane().setLayout(new BorderLayout());
          frame.getContentPane().add(new RegularPolygonSource(), BorderLayout.CENTER);
          frame.setSize(400, 400);
          frame.setLocationRelativeTo(null);
          frame.setVisible(true);
        }
      });
  }
}  
